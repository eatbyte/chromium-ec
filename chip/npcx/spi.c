/* Copyright (c) 2014 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* SPI module for Chrome EC */

#include "console.h"
#include "gpio.h"
#include "hooks.h"
#include "clock.h"
#include "clock_chip.h"
#include "registers.h"
#include "spi.h"
#include "task.h"
#include "timer.h"
#include "util.h"

/* Console output macros */
#if !DEBUG_SPI
#define CPUTS(...)
#define CPRINTS(...)
#else
#define CPUTS(outstr) cputs(CC_SPI, outstr)
#define CPRINTS(format, args...) cprints(CC_SPI, format, ## args)
#endif

/* SPI IP as SPI master */
#define SPI_CLK         8000000
/**
 * Clear SPI data buffer.
 *
 * @param none
 * @return none.
 */
static void clear_databuf(void)
{
	volatile uint8_t dummy __attribute__((unused));
	while (IS_BIT_SET(NPCX_SPI_STAT, NPCX_SPI_STAT_RBF))
		dummy = NPCX_SPI_DATA;
}

/**
 * Preset SPI operation clock.
 *
 * @param   none
 * @return  none
 * @notes   changed when initial or HOOK_FREQ_CHANGE command
 */
void spi_freq_changed(void)
{
	uint8_t prescaler_divider    = 0;

	/* Set clock prescaler divider to SPI module*/
	prescaler_divider = (uint8_t)((uint32_t)clock_get_apb2_freq()
			/ 2 / SPI_CLK);
	if (prescaler_divider >= 1)
		prescaler_divider = prescaler_divider - 1;
	if (prescaler_divider > 0x7F)
		prescaler_divider = 0x7F;

	/* Set core clock division factor in order to obtain the SPI clock */
	NPCX_SPI_CTL1 = (NPCX_SPI_CTL1&(~(((1<<7)-1)<<NPCX_SPI_CTL1_SCDV)))
			|(prescaler_divider<<NPCX_SPI_CTL1_SCDV);
}
DECLARE_HOOK(HOOK_FREQ_CHANGE, spi_freq_changed, HOOK_PRIO_DEFAULT);

/**
 * Set SPI enabled.
 *
 * @param   enable enabled flag
 * @return  success
 */
int spi_enable(int enable)
{
	if (enable) {
		/* Enabling spi module for gpio configuration */
		gpio_config_module(MODULE_SPI, 1);
		/* GPIO No SPI Select */
		CLEAR_BIT(NPCX_DEVALT(0), NPCX_DEVALT0_GPIO_NO_SPIP);

		/* Make sure CS# is a GPIO output mode. */
		gpio_set_flags(GPIO_SPI_CS_L, GPIO_OUTPUT);
		/* Make sure CS# is deselected */
		gpio_set_level(GPIO_SPI_CS_L, 1);
		/* Enabling spi module */
		SET_BIT(NPCX_SPI_CTL1, NPCX_SPI_CTL1_SPIEN);
	} else {
		/* Disabling spi module */
		CLEAR_BIT(NPCX_SPI_CTL1, NPCX_SPI_CTL1_SPIEN);
		/* Make sure CS# is deselected */
		gpio_set_level(GPIO_SPI_CS_L, 1);
		gpio_set_flags(GPIO_SPI_CS_L, GPIO_ODR_HIGH);
		/* Disabling spi module for gpio configuration */
		gpio_config_module(MODULE_SPI, 0);
		/* GPIO No SPI Select */
		SET_BIT(NPCX_DEVALT(0), NPCX_DEVALT0_GPIO_NO_SPIP);
	}
	return EC_SUCCESS;
}


/**
 * Flush an SPI transaction and receive data from slave.
 *
 * @param   txdata  transfer data
 * @param   txlen   transfer length
 * @param   rxdata  receive data
 * @param   rxlen   receive length
 * @return  success
 * @notes   set master transaction mode in npcx chip
 */
int spi_transaction(const uint8_t *txdata, int txlen,
		uint8_t *rxdata, int rxlen)
{
	int i = 0;

	/* Make sure CS# is a GPIO output mode. */
	gpio_set_flags(GPIO_SPI_CS_L, GPIO_OUTPUT);
	/* Make sure CS# is deselected */
	gpio_set_level(GPIO_SPI_CS_L, 1);
	/* Cleaning junk data in the buffer */
	clear_databuf();
	/* Assert CS# to start transaction */
	gpio_set_level(GPIO_SPI_CS_L, 0);
	CPRINTS("NPCX_SPI_DATA=%x", NPCX_SPI_DATA);
	CPRINTS("NPCX_SPI_CTL1=%x", NPCX_SPI_CTL1);
	CPRINTS("NPCX_SPI_STAT=%x", NPCX_SPI_STAT);
	/* Writing the data */
	for (i = 0; i < txlen; ++i) {
		/* Making sure we can write */
		while (IS_BIT_SET(NPCX_SPI_STAT, NPCX_SPI_STAT_BSY))
			;
		/* Write the data */
		NPCX_SPI_DATA =  txdata[i];
		CPRINTS("txdata[i]=%x", txdata[i]);
		/* Waiting till reading is finished */
		while (!IS_BIT_SET(NPCX_SPI_STAT, NPCX_SPI_STAT_RBF))
			;
		/* Reading the (dummy) data */
		clear_databuf();
	}
	CPRINTS("write end");
	/* Reading the data */
	for (i = 0; i < rxlen; ++i) {
		/* Making sure we can write */
		while (IS_BIT_SET(NPCX_SPI_STAT, NPCX_SPI_STAT_BSY))
			;
		/* Write the (dummy) data */
		NPCX_SPI_DATA =  0;
		/* Wait till reading is finished */
		while (!IS_BIT_SET(NPCX_SPI_STAT, NPCX_SPI_STAT_RBF))
			;
		/* Reading the data */
		rxdata[i] = (uint8_t)NPCX_SPI_DATA;
		CPRINTS("rxdata[i]=%x", rxdata[i]);
	}
	/* Deassert CS# (high) to end transaction */
	gpio_set_level(GPIO_SPI_CS_L, 1);

	return EC_SUCCESS;
}

/**
 * SPI initial.
 *
 * @param none
 * @return none
 */
static void spi_init(void)
{
	/* Disabling spi module */
	spi_enable(0);

	/* Disabling spi irq */
	CLEAR_BIT(NPCX_SPI_CTL1, NPCX_SPI_CTL1_EIR);
	CLEAR_BIT(NPCX_SPI_CTL1, NPCX_SPI_CTL1_EIW);

	/* Setting clocking mode to normal mode */
	CLEAR_BIT(NPCX_SPI_CTL1, NPCX_SPI_CTL1_SCM);
	/* Setting 8bit mode transfer */
	CLEAR_BIT(NPCX_SPI_CTL1, NPCX_SPI_CTL1_MOD);
	/* Set core clock division factor in order to obtain the spi clock */
	spi_freq_changed();

	/* We emit zeros in idle (default behaivor) */
	CLEAR_BIT(NPCX_SPI_CTL1, NPCX_SPI_CTL1_SCIDL);

	CPRINTS("nSPI_COMP=%x", IS_BIT_SET(NPCX_STRPST, NPCX_STRPST_SPI_COMP));
	CPRINTS("SPI_SP_SEL=%x", IS_BIT_SET(NPCX_DEV_CTL4,
			NPCX_DEV_CTL4_SPI_SP_SEL));
	/* Cleaning junk data in the buffer */
	clear_databuf();
}
DECLARE_HOOK(HOOK_INIT, spi_init, HOOK_PRIO_DEFAULT);

/*****************************************************************************/
/* Console commands */

static int printrx(const char *desc, const uint8_t *txdata, int txlen,
		int rxlen)
{
	uint8_t rxdata[32];
	int rv;
	int i;

	rv = spi_transaction(txdata, txlen, rxdata, rxlen);
	if (rv)
		return rv;

	CPRINTS("%-12s:", desc);
	for (i = 0; i < rxlen; i++)
		CPRINTS(" 0x%02x", rxdata[i]);
	CPUTS("\n");
	return EC_SUCCESS;
}


static int command_spirom(int argc, char **argv)
{
	uint8_t txmandev[] = {0x90, 0x00, 0x00, 0x00};
	uint8_t txjedec[] = {0x9f};
	uint8_t txunique[] = {0x4b, 0x00, 0x00, 0x00, 0x00};
	uint8_t txsr1[] = {0x05};
	uint8_t txsr2[] = {0x35};

	spi_enable(1);

	printrx("Man/Dev ID", txmandev, sizeof(txmandev), 2);
	printrx("JEDEC ID", txjedec, sizeof(txjedec), 3);
	printrx("Unique ID", txunique, sizeof(txunique), 8);
	printrx("Status reg 1", txsr1, sizeof(txsr1), 1);
	printrx("Status reg 2", txsr2, sizeof(txsr2), 1);

	spi_enable(0);

	return EC_SUCCESS;
}
DECLARE_CONSOLE_COMMAND(spirom, command_spirom,
		NULL,
		"Test reading SPI EEPROM",
		NULL);