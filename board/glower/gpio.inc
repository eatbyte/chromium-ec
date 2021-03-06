/* -*- mode:c -*-
 *
 * Copyright 2015 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Inputs with interrupt handlers are first for efficiency */
GPIO(POWER_BUTTON_L,   PORT(20), 3, GPIO_INT_BOTH,                power_button_interrupt)
GPIO(LID_OPEN,         PORT(16), 0, GPIO_INT_BOTH,                lid_interrupt)
GPIO(AC_PRESENT,       PORT(16), 3, GPIO_INT_BOTH,                extpower_interrupt)
GPIO(PCH_SLP_S3_L,     PORT(20), 4, GPIO_INT_BOTH | GPIO_PULL_UP, power_signal_interrupt) /* SLP_S3# signal from PCH */
GPIO(PCH_SLP_S4_L,     PORT(21), 0, GPIO_INT_BOTH | GPIO_PULL_UP, power_signal_interrupt) /* SLP_S4# signal from PCH */
GPIO(PP1050_PGOOD,     PORT(13), 3, GPIO_INT_BOTH,                power_signal_interrupt) /* Power good on 1.05V */
GPIO(PP3300_PCH_PGOOD, PORT(4),  4, GPIO_INT_BOTH,                power_signal_interrupt) /* Power good on 3.3V (PCH supply) */
GPIO(PP5000_PGOOD,     PORT(3),  0, GPIO_INT_BOTH,                power_signal_interrupt) /* Power good on 5V */
GPIO(S5_PGOOD,         PORT(6),  2, GPIO_INT_BOTH,                power_signal_interrupt) /* Power good on S5 supplies */
GPIO(VCORE_PGOOD,      PORT(5),  7, GPIO_INT_BOTH,                power_signal_interrupt) /* Power good on core VR */
GPIO(WP_L,             PORT(1),  2, GPIO_INT_BOTH,                switch_interrupt)       /* Write protect input */

/* Other inputs */
GPIO(BOARD_VERSION1,   PORT(0),  6, GPIO_INPUT, NULL)
GPIO(BOARD_VERSION2,   PORT(12), 3, GPIO_INPUT, NULL)
GPIO(BOARD_VERSION3,   PORT(12), 7, GPIO_INPUT, NULL)

#ifdef CONFIG_CHIPSET_DEBUG
GPIO(PCH_SLP_SX_L,     PORT(21), 1, GPIO_INPUT | GPIO_PULL_UP, NULL)
GPIO(PCH_SUS_STAT_L,   PORT(20), 1, GPIO_INPUT | GPIO_PULL_UP, NULL)
GPIO(PCH_SUSPWRDNACK,  PORT(4),  6, GPIO_INPUT | GPIO_PULL_UP, NULL)
#endif

GPIO(PP1000_S0IX_PGOOD, PORT(3),  5, GPIO_INPUT, NULL)
GPIO(USB1_OC_L,         PORT(13), 4, GPIO_INPUT, NULL)
GPIO(USB2_OC_L,         PORT(1),  6, GPIO_INPUT, NULL)

/* Outputs; all unasserted by default except for reset signals */
GPIO(CPU_PROCHOT,         PORT(14), 5, GPIO_OUT_LOW,  NULL) /* Force CPU to think it's overheated */
GPIO(ENABLE_BACKLIGHT,    PORT(20), 0, GPIO_ODR_HIGH, NULL) /* Enable backlight power */
GPIO(ENABLE_TOUCHPAD,     PORT(6),  4, GPIO_OUT_LOW,  NULL) /* Enable touchpad power */
GPIO(ENTERING_RW,         PORT(3),  3, GPIO_OUT_LOW,  NULL) /* Indicate when EC is entering RW code */
GPIO(LPC_CLKRUN_L,        PORT(1),  4, GPIO_ODR_HIGH, NULL) /* Request that PCH drive LPC clock */
GPIO(PCH_CORE_PWROK,      PORT(12), 2, GPIO_OUT_LOW,  NULL) /* Indicate core well power is stable */
GPIO(PCH_PWRBTN_L,        PORT(13), 0, GPIO_ODR_HIGH, NULL) /* Power button output to PCH */
GPIO(PCH_RCIN_L,          PORT(14), 0, GPIO_ODR_HIGH, NULL) /* Reset line to PCH (for 8042 emulation) */
GPIO(PCH_RSMRST_L,        PORT(14), 3, GPIO_OUT_LOW,  NULL) /* Reset PCH resume power plane logic */
GPIO(PCH_SMI_L,           PORT(5),  5, GPIO_ODR_HIGH, NULL) /* System management interrupt to PCH */
GPIO(PCH_SOC_OVERRIDE_L,  PORT(6),  5, GPIO_OUT_LOW,  NULL) /* SOC override signal to PCH; when high, ME ignores security descriptor */
GPIO(PCH_SYS_PWROK,       PORT(12), 4, GPIO_OUT_LOW,  NULL) /* EC thinks everything is up and ready */
GPIO(PCH_WAKE_L,          PORT(20), 2, GPIO_ODR_HIGH, NULL) /* Wake signal from EC to PCH */
GPIO(PP1350_EN,           PORT(14), 7, GPIO_OUT_LOW,  NULL) /* Enable 1.35V supply */
GPIO(PP3300_DX_EN,        PORT(5),  0, GPIO_OUT_LOW,  NULL) /* Enable power to lots of peripherals */
GPIO(PP3300_LTE_EN,       PORT(1),  1, GPIO_OUT_LOW,  NULL) /* Enable LTE radio */
GPIO(PP3300_WLAN_EN,      PORT(4),  7, GPIO_OUT_LOW,  NULL) /* Enable WiFi power */
GPIO(PP5000_EN,           PORT(2),  7, GPIO_OUT_LOW,  NULL) /* Enable 5V supply */
GPIO(PPSX_EN,             PORT(5),  3, GPIO_INPUT,    NULL) /* Enable PP1350_PCH_SX, PP1000_PCH_SX */
GPIO(SUSP_VR_EN,          PORT(6),  6, GPIO_OUT_LOW,  NULL) /* Enable 1.05V regulator */
GPIO(TOUCHSCREEN_RESET_L, PORT(16), 1, GPIO_OUT_HIGH, NULL) /* Reset touch screen */
GPIO(USB_CTL1,            PORT(15), 7, GPIO_OUT_LOW,  NULL) /* USB control signal 1 to both ports */
GPIO(USB_ILIM_SEL,        PORT(3),  6, GPIO_OUT_LOW,  NULL) /* USB current limit to both ports */
GPIO(USB1_ENABLE,         PORT(1),  5, GPIO_OUT_LOW,  NULL) /* USB port 1 output power enable */
GPIO(USB2_ENABLE,         PORT(1),  7, GPIO_OUT_LOW,  NULL) /* USB port 2 output power enable */
GPIO(VCORE_EN,            PORT(15), 0, GPIO_OUT_LOW,  NULL) /* Enable core power supplies */
GPIO(WLAN_OFF_L,          PORT(5),  2, GPIO_OUT_LOW,  NULL) /* Disable WiFi radio */
GPIO(KBD_IRQ_L,           PORT(6),  7, GPIO_ODR_HIGH, NULL) /* Negative edge triggered irq. */
GPIO(BAT_LED0,            PORT(15), 4, GPIO_ODR_HIGH, NULL)
GPIO(BAT_LED1,            PORT(15), 5, GPIO_ODR_HIGH, NULL)
GPIO(KBD_KSO2,            PORT(10), 1, GPIO_OUT_LOW,  NULL)

GPIO(SYS_RST_L,           PORT(12), 1, GPIO_INPUT,    NULL)
GPIO(EC_HIB,              PORT(3),  4, GPIO_INPUT,    NULL)
GPIO(ICMNT,               PORT(6),  1, GPIO_INPUT,    NULL)
GPIO(PVT_CS0,             PORT(14), 6, GPIO_ODR_HIGH, NULL)

/* Configure VCC_PWRGD as GPIO so that it's internally gated high */
GPIO(TP78,                PORT(6),  3, GPIO_OUT_HIGH, NULL)


ALTERNATE(PORT(16), 0x24, 1, MODULE_UART,          0) /* UART0 */
ALTERNATE(PORT(2),  0x0f, 2, MODULE_I2C,           0) /* I2C1 and I2C2 */
ALTERNATE(PORT(0),  0xfe, 3, MODULE_KEYBOARD_SCAN, GPIO_KB_OUTPUT)
ALTERNATE(PORT(1),  0x03, 3, MODULE_KEYBOARD_SCAN, GPIO_KB_OUTPUT)
ALTERNATE(PORT(3),  0x04, 3, MODULE_KEYBOARD_SCAN, GPIO_KB_INPUT)
ALTERNATE(PORT(4),  0x0d, 3, MODULE_KEYBOARD_SCAN, GPIO_KB_INPUT)
ALTERNATE(PORT(10), 0xd8, 3, MODULE_KEYBOARD_SCAN, GPIO_KB_OUTPUT)
ALTERNATE(PORT(12), 0x60, 2, MODULE_KEYBOARD_SCAN, GPIO_KB_INPUT)
ALTERNATE(PORT(14), 0x14, 3, MODULE_KEYBOARD_SCAN, GPIO_KB_INPUT)
ALTERNATE(PORT(2),  0x40, 2, MODULE_LPC,           0) /* LPC SCI */
ALTERNATE(PORT(15), 0x08, 1, MODULE_SPI,           0)
ALTERNATE(PORT(16), 0x10, 1, MODULE_SPI,           0)
ALTERNATE(PORT(5),  0x10, 1, MODULE_SPI,           0)
