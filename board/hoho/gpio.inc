/* -*- mode:c -*-
 *
 * Copyright (c) 2014 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
GPIO(DP_HPD,           A, 0,  GPIO_INT_BOTH, hpd_event)
GPIO(USB_C_CC1_PD,     A, 1,  GPIO_ANALOG,   NULL)
GPIO(STM_READY,        A, 2,  GPIO_OUT_LOW,  NULL) /* factory test only */
GPIO(MCDP_RESET_L,     A, 3,  GPIO_OUT_HIGH, NULL)
GPIO(PD_DAC_REF,       A, 4,  GPIO_ANALOG,   NULL)

GPIO(MCDP_READY,       A, 7,  GPIO_OUT_LOW,  NULL) /* factory test only */
GPIO(PD_SBU_ENABLE,    A, 8,  GPIO_OUT_LOW,  NULL)
GPIO(USB_DM,           A, 11, GPIO_ANALOG,   NULL)
GPIO(USB_DP,           A, 12, GPIO_ANALOG,   NULL)
GPIO(PD_CC1_TX_EN,     A, 15, GPIO_OUT_LOW,  NULL)

GPIO(MCDP_GPIO1,       B, 0,  GPIO_INPUT,    NULL)
GPIO(MCDP_CONFIG1,     B, 1,  GPIO_INPUT,    NULL)
GPIO(PD_MCDP_SPI_WP_L, B, 2,  GPIO_OUT_LOW,  NULL)
GPIO(PD_CC1_TX_DATA,   B, 4,  GPIO_OUT_LOW,  NULL)
GPIO(PD_MCDP_SPI_CS_L, B, 12, GPIO_INPUT,    NULL)

/* Unimplemented signals which we need to emulate for now */
UNIMPLEMENTED(ENTERING_RW)
UNIMPLEMENTED(WP_L)

ALTERNATE(B, 0x0008, 0, MODULE_USB_PD, 0)            /* SPI1: SCK(PB3) */
ALTERNATE(B, 0x0200, 2, MODULE_USB_PD, 0)            /* TIM17_CH1: PB9 */
ALTERNATE(A, 0x0600, 1, MODULE_UART,   GPIO_PULL_UP) /* USART1: PA9/PA10 */
ALTERNATE(B, 0x0C00, 4, MODULE_UART,   GPIO_PULL_UP) /* USART3: PB10/PB11 */
