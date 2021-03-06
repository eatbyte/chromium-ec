/* -*- mode:c -*-
 *
 * Copyright 2015 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*GPIO(DP_HPD,            A, 0,  GPIO_INT_BOTH, hpd_event)*/
GPIO(DP_HPD,            A, 0,  GPIO_INPUT, NULL)

/* PD RX/TX */
GPIO(USB_CC1_PD,        A, 1,  GPIO_ANALOG,  NULL)
GPIO(PD_VBUS_P,         A, 5,  GPIO_ANALOG,  NULL)
GPIO(PD_VBUS_N,         A, 6,  GPIO_ANALOG,  NULL)
GPIO(PD_TX_EN,          A, 15, GPIO_OUT_LOW, NULL)
GPIO(PD_TX_DATA,        B, 4,  GPIO_OUT_LOW, NULL)

/* Power and muxes control */
GPIO(PP20000_EN,        A, 8,  GPIO_OUT_LOW,  NULL)
GPIO(PPVAR_VBUS_EN,     B, 12, GPIO_OUT_LOW,  NULL)
GPIO(SS_MUX_OE_L,       B, 13, GPIO_OUT_HIGH, NULL)
GPIO(SS_MUX_SEL,        B, 14, GPIO_OUT_LOW,  NULL)

/* Display Port/HDMI */
GPIO(PD_SBU_ENABLE,     A, 7,  GPIO_OUT_LOW, NULL)

/* Chip Resets */
GPIO(BRIDGE_RESET_L,    B, 0,  GPIO_OUT_HIGH, NULL)
GPIO(SPLITTER_RESET_L,  B, 1,  GPIO_OUT_HIGH, NULL)
GPIO(HUB_RESET_L,       B, 15, GPIO_OUT_HIGH, NULL)


/*
 * I2C pins should be configured as inputs until I2C module is
 * initialized. This will avoid driving the lines unintentionally.
 */
GPIO(MASTER_I2C_SCL,    B, 6,  GPIO_INPUT, NULL)
GPIO(MASTER_I2C_SDA,    B, 7,  GPIO_INPUT, NULL)


/* Test points */
GPIO(TP6,               A, 13, GPIO_OUT_HIGH /*GPIO_ODR_HIGH*/, NULL)
GPIO(TP7,               A, 14, GPIO_OUT_LOW /*GPIO_ODR_HIGH*/, NULL)

/* Unimplemented signals which we need to emulate for now */
UNIMPLEMENTED(ENTERING_RW)
UNIMPLEMENTED(WP_L)

ALTERNATE(B, 0x0018, 0, MODULE_USB_PD, 0)            /* SPI1 SCK/MISO: PB3/PB4 */
ALTERNATE(B, 0x0200, 2, MODULE_USB_PD, 0)            /* TIM17_CH1: PB9 */
ALTERNATE(A, 0x0600, 1, MODULE_UART,   GPIO_PULL_UP) /* USART1: PA9/PA10 */
ALTERNATE(A, 0x000C, 1, MODULE_UART,   GPIO_PULL_UP) /* USART2: PA2/PA3 */
ALTERNATE(B, 0x0C00, 4, MODULE_UART,   GPIO_PULL_UP) /* USART3: PB10/PB11 */
ALTERNATE(B, 0x00C0, 1, MODULE_I2C,    0)            /* I2C MASTER: PB6/PB7 */

