/***************************************************************************//**
* \file SPILCD_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_SPILCD_H)
#define CY_SCB_PINS_SPILCD_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define SPILCD_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define SPILCD_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define SPILCD_REMOVE_TX_SDA_MISO_PIN      (1u)
#define SPILCD_REMOVE_SCLK_PIN      (1u)
#define SPILCD_REMOVE_SS0_PIN      (1u)
#define SPILCD_REMOVE_SS1_PIN                 (1u)
#define SPILCD_REMOVE_SS2_PIN                 (1u)
#define SPILCD_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define SPILCD_REMOVE_I2C_PINS                (1u)
#define SPILCD_REMOVE_SPI_MASTER_PINS         (0u)
#define SPILCD_REMOVE_SPI_MASTER_SCLK_PIN     (0u)
#define SPILCD_REMOVE_SPI_MASTER_MOSI_PIN     (0u)
#define SPILCD_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define SPILCD_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define SPILCD_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define SPILCD_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define SPILCD_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define SPILCD_REMOVE_SPI_SLAVE_PINS          (1u)
#define SPILCD_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define SPILCD_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define SPILCD_REMOVE_UART_TX_PIN             (1u)
#define SPILCD_REMOVE_UART_RX_TX_PIN          (1u)
#define SPILCD_REMOVE_UART_RX_PIN             (1u)
#define SPILCD_REMOVE_UART_RX_WAKE_PIN        (1u)
#define SPILCD_REMOVE_UART_RTS_PIN            (1u)
#define SPILCD_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define SPILCD_RX_WAKE_SCL_MOSI_PIN (0u == SPILCD_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define SPILCD_RX_SCL_MOSI_PIN     (0u == SPILCD_REMOVE_RX_SCL_MOSI_PIN)
#define SPILCD_TX_SDA_MISO_PIN     (0u == SPILCD_REMOVE_TX_SDA_MISO_PIN)
#define SPILCD_SCLK_PIN     (0u == SPILCD_REMOVE_SCLK_PIN)
#define SPILCD_SS0_PIN     (0u == SPILCD_REMOVE_SS0_PIN)
#define SPILCD_SS1_PIN                (0u == SPILCD_REMOVE_SS1_PIN)
#define SPILCD_SS2_PIN                (0u == SPILCD_REMOVE_SS2_PIN)
#define SPILCD_SS3_PIN                (0u == SPILCD_REMOVE_SS3_PIN)

/* Mode defined pins */
#define SPILCD_I2C_PINS               (0u == SPILCD_REMOVE_I2C_PINS)
#define SPILCD_SPI_MASTER_PINS        (0u == SPILCD_REMOVE_SPI_MASTER_PINS)
#define SPILCD_SPI_MASTER_SCLK_PIN    (0u == SPILCD_REMOVE_SPI_MASTER_SCLK_PIN)
#define SPILCD_SPI_MASTER_MOSI_PIN    (0u == SPILCD_REMOVE_SPI_MASTER_MOSI_PIN)
#define SPILCD_SPI_MASTER_MISO_PIN    (0u == SPILCD_REMOVE_SPI_MASTER_MISO_PIN)
#define SPILCD_SPI_MASTER_SS0_PIN     (0u == SPILCD_REMOVE_SPI_MASTER_SS0_PIN)
#define SPILCD_SPI_MASTER_SS1_PIN     (0u == SPILCD_REMOVE_SPI_MASTER_SS1_PIN)
#define SPILCD_SPI_MASTER_SS2_PIN     (0u == SPILCD_REMOVE_SPI_MASTER_SS2_PIN)
#define SPILCD_SPI_MASTER_SS3_PIN     (0u == SPILCD_REMOVE_SPI_MASTER_SS3_PIN)
#define SPILCD_SPI_SLAVE_PINS         (0u == SPILCD_REMOVE_SPI_SLAVE_PINS)
#define SPILCD_SPI_SLAVE_MOSI_PIN     (0u == SPILCD_REMOVE_SPI_SLAVE_MOSI_PIN)
#define SPILCD_SPI_SLAVE_MISO_PIN     (0u == SPILCD_REMOVE_SPI_SLAVE_MISO_PIN)
#define SPILCD_UART_TX_PIN            (0u == SPILCD_REMOVE_UART_TX_PIN)
#define SPILCD_UART_RX_TX_PIN         (0u == SPILCD_REMOVE_UART_RX_TX_PIN)
#define SPILCD_UART_RX_PIN            (0u == SPILCD_REMOVE_UART_RX_PIN)
#define SPILCD_UART_RX_WAKE_PIN       (0u == SPILCD_REMOVE_UART_RX_WAKE_PIN)
#define SPILCD_UART_RTS_PIN           (0u == SPILCD_REMOVE_UART_RTS_PIN)
#define SPILCD_UART_CTS_PIN           (0u == SPILCD_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (SPILCD_RX_WAKE_SCL_MOSI_PIN)
    #include "SPILCD_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (SPILCD_RX_SCL_MOSI) */

#if (SPILCD_RX_SCL_MOSI_PIN)
    #include "SPILCD_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (SPILCD_RX_SCL_MOSI) */

#if (SPILCD_TX_SDA_MISO_PIN)
    #include "SPILCD_uart_tx_i2c_sda_spi_miso.h"
#endif /* (SPILCD_TX_SDA_MISO) */

#if (SPILCD_SCLK_PIN)
    #include "SPILCD_spi_sclk.h"
#endif /* (SPILCD_SCLK) */

#if (SPILCD_SS0_PIN)
    #include "SPILCD_spi_ss0.h"
#endif /* (SPILCD_SS0_PIN) */

#if (SPILCD_SS1_PIN)
    #include "SPILCD_spi_ss1.h"
#endif /* (SPILCD_SS1_PIN) */

#if (SPILCD_SS2_PIN)
    #include "SPILCD_spi_ss2.h"
#endif /* (SPILCD_SS2_PIN) */

#if (SPILCD_SS3_PIN)
    #include "SPILCD_spi_ss3.h"
#endif /* (SPILCD_SS3_PIN) */

#if (SPILCD_I2C_PINS)
    #include "SPILCD_scl.h"
    #include "SPILCD_sda.h"
#endif /* (SPILCD_I2C_PINS) */

#if (SPILCD_SPI_MASTER_PINS)
#if (SPILCD_SPI_MASTER_SCLK_PIN)
    #include "SPILCD_sclk_m.h"
#endif /* (SPILCD_SPI_MASTER_SCLK_PIN) */

#if (SPILCD_SPI_MASTER_MOSI_PIN)
    #include "SPILCD_mosi_m.h"
#endif /* (SPILCD_SPI_MASTER_MOSI_PIN) */

#if (SPILCD_SPI_MASTER_MISO_PIN)
    #include "SPILCD_miso_m.h"
#endif /*(SPILCD_SPI_MASTER_MISO_PIN) */
#endif /* (SPILCD_SPI_MASTER_PINS) */

#if (SPILCD_SPI_SLAVE_PINS)
    #include "SPILCD_sclk_s.h"
    #include "SPILCD_ss_s.h"

#if (SPILCD_SPI_SLAVE_MOSI_PIN)
    #include "SPILCD_mosi_s.h"
#endif /* (SPILCD_SPI_SLAVE_MOSI_PIN) */

#if (SPILCD_SPI_SLAVE_MISO_PIN)
    #include "SPILCD_miso_s.h"
#endif /*(SPILCD_SPI_SLAVE_MISO_PIN) */
#endif /* (SPILCD_SPI_SLAVE_PINS) */

#if (SPILCD_SPI_MASTER_SS0_PIN)
    #include "SPILCD_ss0_m.h"
#endif /* (SPILCD_SPI_MASTER_SS0_PIN) */

#if (SPILCD_SPI_MASTER_SS1_PIN)
    #include "SPILCD_ss1_m.h"
#endif /* (SPILCD_SPI_MASTER_SS1_PIN) */

#if (SPILCD_SPI_MASTER_SS2_PIN)
    #include "SPILCD_ss2_m.h"
#endif /* (SPILCD_SPI_MASTER_SS2_PIN) */

#if (SPILCD_SPI_MASTER_SS3_PIN)
    #include "SPILCD_ss3_m.h"
#endif /* (SPILCD_SPI_MASTER_SS3_PIN) */

#if (SPILCD_UART_TX_PIN)
    #include "SPILCD_tx.h"
#endif /* (SPILCD_UART_TX_PIN) */

#if (SPILCD_UART_RX_TX_PIN)
    #include "SPILCD_rx_tx.h"
#endif /* (SPILCD_UART_RX_TX_PIN) */

#if (SPILCD_UART_RX_PIN)
    #include "SPILCD_rx.h"
#endif /* (SPILCD_UART_RX_PIN) */

#if (SPILCD_UART_RX_WAKE_PIN)
    #include "SPILCD_rx_wake.h"
#endif /* (SPILCD_UART_RX_WAKE_PIN) */

#if (SPILCD_UART_RTS_PIN)
    #include "SPILCD_rts.h"
#endif /* (SPILCD_UART_RTS_PIN) */

#if (SPILCD_UART_CTS_PIN)
    #include "SPILCD_cts.h"
#endif /* (SPILCD_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (SPILCD_RX_SCL_MOSI_PIN)
    #define SPILCD_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) SPILCD_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define SPILCD_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) SPILCD_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define SPILCD_RX_SCL_MOSI_HSIOM_MASK      (SPILCD_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define SPILCD_RX_SCL_MOSI_HSIOM_POS       (SPILCD_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define SPILCD_RX_SCL_MOSI_HSIOM_SEL_GPIO  (SPILCD_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define SPILCD_RX_SCL_MOSI_HSIOM_SEL_I2C   (SPILCD_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define SPILCD_RX_SCL_MOSI_HSIOM_SEL_SPI   (SPILCD_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define SPILCD_RX_SCL_MOSI_HSIOM_SEL_UART  (SPILCD_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (SPILCD_RX_WAKE_SCL_MOSI_PIN)
    #define SPILCD_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) SPILCD_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define SPILCD_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) SPILCD_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define SPILCD_RX_WAKE_SCL_MOSI_HSIOM_MASK      (SPILCD_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define SPILCD_RX_WAKE_SCL_MOSI_HSIOM_POS       (SPILCD_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define SPILCD_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (SPILCD_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define SPILCD_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (SPILCD_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define SPILCD_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (SPILCD_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define SPILCD_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (SPILCD_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define SPILCD_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) SPILCD_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define SPILCD_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) SPILCD_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define SPILCD_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (SPILCD_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define SPILCD_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) SPILCD_INTCFG_TYPE_MASK << \
                                                                           SPILCD_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins SPILCD_RX_SCL_MOSI_PIN or SPILCD_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (SPILCD_RX_SCL_MOSI_PIN) */

#if (SPILCD_TX_SDA_MISO_PIN)
    #define SPILCD_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) SPILCD_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define SPILCD_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) SPILCD_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define SPILCD_TX_SDA_MISO_HSIOM_MASK      (SPILCD_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define SPILCD_TX_SDA_MISO_HSIOM_POS       (SPILCD_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define SPILCD_TX_SDA_MISO_HSIOM_SEL_GPIO  (SPILCD_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define SPILCD_TX_SDA_MISO_HSIOM_SEL_I2C   (SPILCD_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define SPILCD_TX_SDA_MISO_HSIOM_SEL_SPI   (SPILCD_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define SPILCD_TX_SDA_MISO_HSIOM_SEL_UART  (SPILCD_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (SPILCD_TX_SDA_MISO_PIN) */

#if (SPILCD_SCLK_PIN)
    #define SPILCD_SCLK_HSIOM_REG   (*(reg32 *) SPILCD_spi_sclk__0__HSIOM)
    #define SPILCD_SCLK_HSIOM_PTR   ( (reg32 *) SPILCD_spi_sclk__0__HSIOM)
    
    #define SPILCD_SCLK_HSIOM_MASK      (SPILCD_spi_sclk__0__HSIOM_MASK)
    #define SPILCD_SCLK_HSIOM_POS       (SPILCD_spi_sclk__0__HSIOM_SHIFT)
    #define SPILCD_SCLK_HSIOM_SEL_GPIO  (SPILCD_spi_sclk__0__HSIOM_GPIO)
    #define SPILCD_SCLK_HSIOM_SEL_I2C   (SPILCD_spi_sclk__0__HSIOM_I2C)
    #define SPILCD_SCLK_HSIOM_SEL_SPI   (SPILCD_spi_sclk__0__HSIOM_SPI)
    #define SPILCD_SCLK_HSIOM_SEL_UART  (SPILCD_spi_sclk__0__HSIOM_UART)
#endif /* (SPILCD_SCLK_PIN) */

#if (SPILCD_SS0_PIN)
    #define SPILCD_SS0_HSIOM_REG   (*(reg32 *) SPILCD_spi_ss0__0__HSIOM)
    #define SPILCD_SS0_HSIOM_PTR   ( (reg32 *) SPILCD_spi_ss0__0__HSIOM)
    
    #define SPILCD_SS0_HSIOM_MASK      (SPILCD_spi_ss0__0__HSIOM_MASK)
    #define SPILCD_SS0_HSIOM_POS       (SPILCD_spi_ss0__0__HSIOM_SHIFT)
    #define SPILCD_SS0_HSIOM_SEL_GPIO  (SPILCD_spi_ss0__0__HSIOM_GPIO)
    #define SPILCD_SS0_HSIOM_SEL_I2C   (SPILCD_spi_ss0__0__HSIOM_I2C)
    #define SPILCD_SS0_HSIOM_SEL_SPI   (SPILCD_spi_ss0__0__HSIOM_SPI)
#if !(SPILCD_CY_SCBIP_V0 || SPILCD_CY_SCBIP_V1)
    #define SPILCD_SS0_HSIOM_SEL_UART  (SPILCD_spi_ss0__0__HSIOM_UART)
#endif /* !(SPILCD_CY_SCBIP_V0 || SPILCD_CY_SCBIP_V1) */
#endif /* (SPILCD_SS0_PIN) */

#if (SPILCD_SS1_PIN)
    #define SPILCD_SS1_HSIOM_REG  (*(reg32 *) SPILCD_spi_ss1__0__HSIOM)
    #define SPILCD_SS1_HSIOM_PTR  ( (reg32 *) SPILCD_spi_ss1__0__HSIOM)
    
    #define SPILCD_SS1_HSIOM_MASK     (SPILCD_spi_ss1__0__HSIOM_MASK)
    #define SPILCD_SS1_HSIOM_POS      (SPILCD_spi_ss1__0__HSIOM_SHIFT)
    #define SPILCD_SS1_HSIOM_SEL_GPIO (SPILCD_spi_ss1__0__HSIOM_GPIO)
    #define SPILCD_SS1_HSIOM_SEL_I2C  (SPILCD_spi_ss1__0__HSIOM_I2C)
    #define SPILCD_SS1_HSIOM_SEL_SPI  (SPILCD_spi_ss1__0__HSIOM_SPI)
#endif /* (SPILCD_SS1_PIN) */

#if (SPILCD_SS2_PIN)
    #define SPILCD_SS2_HSIOM_REG     (*(reg32 *) SPILCD_spi_ss2__0__HSIOM)
    #define SPILCD_SS2_HSIOM_PTR     ( (reg32 *) SPILCD_spi_ss2__0__HSIOM)
    
    #define SPILCD_SS2_HSIOM_MASK     (SPILCD_spi_ss2__0__HSIOM_MASK)
    #define SPILCD_SS2_HSIOM_POS      (SPILCD_spi_ss2__0__HSIOM_SHIFT)
    #define SPILCD_SS2_HSIOM_SEL_GPIO (SPILCD_spi_ss2__0__HSIOM_GPIO)
    #define SPILCD_SS2_HSIOM_SEL_I2C  (SPILCD_spi_ss2__0__HSIOM_I2C)
    #define SPILCD_SS2_HSIOM_SEL_SPI  (SPILCD_spi_ss2__0__HSIOM_SPI)
#endif /* (SPILCD_SS2_PIN) */

#if (SPILCD_SS3_PIN)
    #define SPILCD_SS3_HSIOM_REG     (*(reg32 *) SPILCD_spi_ss3__0__HSIOM)
    #define SPILCD_SS3_HSIOM_PTR     ( (reg32 *) SPILCD_spi_ss3__0__HSIOM)
    
    #define SPILCD_SS3_HSIOM_MASK     (SPILCD_spi_ss3__0__HSIOM_MASK)
    #define SPILCD_SS3_HSIOM_POS      (SPILCD_spi_ss3__0__HSIOM_SHIFT)
    #define SPILCD_SS3_HSIOM_SEL_GPIO (SPILCD_spi_ss3__0__HSIOM_GPIO)
    #define SPILCD_SS3_HSIOM_SEL_I2C  (SPILCD_spi_ss3__0__HSIOM_I2C)
    #define SPILCD_SS3_HSIOM_SEL_SPI  (SPILCD_spi_ss3__0__HSIOM_SPI)
#endif /* (SPILCD_SS3_PIN) */

#if (SPILCD_I2C_PINS)
    #define SPILCD_SCL_HSIOM_REG  (*(reg32 *) SPILCD_scl__0__HSIOM)
    #define SPILCD_SCL_HSIOM_PTR  ( (reg32 *) SPILCD_scl__0__HSIOM)
    
    #define SPILCD_SCL_HSIOM_MASK     (SPILCD_scl__0__HSIOM_MASK)
    #define SPILCD_SCL_HSIOM_POS      (SPILCD_scl__0__HSIOM_SHIFT)
    #define SPILCD_SCL_HSIOM_SEL_GPIO (SPILCD_sda__0__HSIOM_GPIO)
    #define SPILCD_SCL_HSIOM_SEL_I2C  (SPILCD_sda__0__HSIOM_I2C)
    
    #define SPILCD_SDA_HSIOM_REG  (*(reg32 *) SPILCD_sda__0__HSIOM)
    #define SPILCD_SDA_HSIOM_PTR  ( (reg32 *) SPILCD_sda__0__HSIOM)
    
    #define SPILCD_SDA_HSIOM_MASK     (SPILCD_sda__0__HSIOM_MASK)
    #define SPILCD_SDA_HSIOM_POS      (SPILCD_sda__0__HSIOM_SHIFT)
    #define SPILCD_SDA_HSIOM_SEL_GPIO (SPILCD_sda__0__HSIOM_GPIO)
    #define SPILCD_SDA_HSIOM_SEL_I2C  (SPILCD_sda__0__HSIOM_I2C)
#endif /* (SPILCD_I2C_PINS) */

#if (SPILCD_SPI_SLAVE_PINS)
    #define SPILCD_SCLK_S_HSIOM_REG   (*(reg32 *) SPILCD_sclk_s__0__HSIOM)
    #define SPILCD_SCLK_S_HSIOM_PTR   ( (reg32 *) SPILCD_sclk_s__0__HSIOM)
    
    #define SPILCD_SCLK_S_HSIOM_MASK      (SPILCD_sclk_s__0__HSIOM_MASK)
    #define SPILCD_SCLK_S_HSIOM_POS       (SPILCD_sclk_s__0__HSIOM_SHIFT)
    #define SPILCD_SCLK_S_HSIOM_SEL_GPIO  (SPILCD_sclk_s__0__HSIOM_GPIO)
    #define SPILCD_SCLK_S_HSIOM_SEL_SPI   (SPILCD_sclk_s__0__HSIOM_SPI)
    
    #define SPILCD_SS0_S_HSIOM_REG    (*(reg32 *) SPILCD_ss0_s__0__HSIOM)
    #define SPILCD_SS0_S_HSIOM_PTR    ( (reg32 *) SPILCD_ss0_s__0__HSIOM)
    
    #define SPILCD_SS0_S_HSIOM_MASK       (SPILCD_ss0_s__0__HSIOM_MASK)
    #define SPILCD_SS0_S_HSIOM_POS        (SPILCD_ss0_s__0__HSIOM_SHIFT)
    #define SPILCD_SS0_S_HSIOM_SEL_GPIO   (SPILCD_ss0_s__0__HSIOM_GPIO)  
    #define SPILCD_SS0_S_HSIOM_SEL_SPI    (SPILCD_ss0_s__0__HSIOM_SPI)
#endif /* (SPILCD_SPI_SLAVE_PINS) */

#if (SPILCD_SPI_SLAVE_MOSI_PIN)
    #define SPILCD_MOSI_S_HSIOM_REG   (*(reg32 *) SPILCD_mosi_s__0__HSIOM)
    #define SPILCD_MOSI_S_HSIOM_PTR   ( (reg32 *) SPILCD_mosi_s__0__HSIOM)
    
    #define SPILCD_MOSI_S_HSIOM_MASK      (SPILCD_mosi_s__0__HSIOM_MASK)
    #define SPILCD_MOSI_S_HSIOM_POS       (SPILCD_mosi_s__0__HSIOM_SHIFT)
    #define SPILCD_MOSI_S_HSIOM_SEL_GPIO  (SPILCD_mosi_s__0__HSIOM_GPIO)
    #define SPILCD_MOSI_S_HSIOM_SEL_SPI   (SPILCD_mosi_s__0__HSIOM_SPI)
#endif /* (SPILCD_SPI_SLAVE_MOSI_PIN) */

#if (SPILCD_SPI_SLAVE_MISO_PIN)
    #define SPILCD_MISO_S_HSIOM_REG   (*(reg32 *) SPILCD_miso_s__0__HSIOM)
    #define SPILCD_MISO_S_HSIOM_PTR   ( (reg32 *) SPILCD_miso_s__0__HSIOM)
    
    #define SPILCD_MISO_S_HSIOM_MASK      (SPILCD_miso_s__0__HSIOM_MASK)
    #define SPILCD_MISO_S_HSIOM_POS       (SPILCD_miso_s__0__HSIOM_SHIFT)
    #define SPILCD_MISO_S_HSIOM_SEL_GPIO  (SPILCD_miso_s__0__HSIOM_GPIO)
    #define SPILCD_MISO_S_HSIOM_SEL_SPI   (SPILCD_miso_s__0__HSIOM_SPI)
#endif /* (SPILCD_SPI_SLAVE_MISO_PIN) */

#if (SPILCD_SPI_MASTER_MISO_PIN)
    #define SPILCD_MISO_M_HSIOM_REG   (*(reg32 *) SPILCD_miso_m__0__HSIOM)
    #define SPILCD_MISO_M_HSIOM_PTR   ( (reg32 *) SPILCD_miso_m__0__HSIOM)
    
    #define SPILCD_MISO_M_HSIOM_MASK      (SPILCD_miso_m__0__HSIOM_MASK)
    #define SPILCD_MISO_M_HSIOM_POS       (SPILCD_miso_m__0__HSIOM_SHIFT)
    #define SPILCD_MISO_M_HSIOM_SEL_GPIO  (SPILCD_miso_m__0__HSIOM_GPIO)
    #define SPILCD_MISO_M_HSIOM_SEL_SPI   (SPILCD_miso_m__0__HSIOM_SPI)
#endif /* (SPILCD_SPI_MASTER_MISO_PIN) */

#if (SPILCD_SPI_MASTER_MOSI_PIN)
    #define SPILCD_MOSI_M_HSIOM_REG   (*(reg32 *) SPILCD_mosi_m__0__HSIOM)
    #define SPILCD_MOSI_M_HSIOM_PTR   ( (reg32 *) SPILCD_mosi_m__0__HSIOM)
    
    #define SPILCD_MOSI_M_HSIOM_MASK      (SPILCD_mosi_m__0__HSIOM_MASK)
    #define SPILCD_MOSI_M_HSIOM_POS       (SPILCD_mosi_m__0__HSIOM_SHIFT)
    #define SPILCD_MOSI_M_HSIOM_SEL_GPIO  (SPILCD_mosi_m__0__HSIOM_GPIO)
    #define SPILCD_MOSI_M_HSIOM_SEL_SPI   (SPILCD_mosi_m__0__HSIOM_SPI)
#endif /* (SPILCD_SPI_MASTER_MOSI_PIN) */

#if (SPILCD_SPI_MASTER_SCLK_PIN)
    #define SPILCD_SCLK_M_HSIOM_REG   (*(reg32 *) SPILCD_sclk_m__0__HSIOM)
    #define SPILCD_SCLK_M_HSIOM_PTR   ( (reg32 *) SPILCD_sclk_m__0__HSIOM)
    
    #define SPILCD_SCLK_M_HSIOM_MASK      (SPILCD_sclk_m__0__HSIOM_MASK)
    #define SPILCD_SCLK_M_HSIOM_POS       (SPILCD_sclk_m__0__HSIOM_SHIFT)
    #define SPILCD_SCLK_M_HSIOM_SEL_GPIO  (SPILCD_sclk_m__0__HSIOM_GPIO)
    #define SPILCD_SCLK_M_HSIOM_SEL_SPI   (SPILCD_sclk_m__0__HSIOM_SPI)
#endif /* (SPILCD_SPI_MASTER_SCLK_PIN) */

#if (SPILCD_SPI_MASTER_SS0_PIN)
    #define SPILCD_SS0_M_HSIOM_REG    (*(reg32 *) SPILCD_ss0_m__0__HSIOM)
    #define SPILCD_SS0_M_HSIOM_PTR    ( (reg32 *) SPILCD_ss0_m__0__HSIOM)
    
    #define SPILCD_SS0_M_HSIOM_MASK       (SPILCD_ss0_m__0__HSIOM_MASK)
    #define SPILCD_SS0_M_HSIOM_POS        (SPILCD_ss0_m__0__HSIOM_SHIFT)
    #define SPILCD_SS0_M_HSIOM_SEL_GPIO   (SPILCD_ss0_m__0__HSIOM_GPIO)
    #define SPILCD_SS0_M_HSIOM_SEL_SPI    (SPILCD_ss0_m__0__HSIOM_SPI)
#endif /* (SPILCD_SPI_MASTER_SS0_PIN) */

#if (SPILCD_SPI_MASTER_SS1_PIN)
    #define SPILCD_SS1_M_HSIOM_REG    (*(reg32 *) SPILCD_ss1_m__0__HSIOM)
    #define SPILCD_SS1_M_HSIOM_PTR    ( (reg32 *) SPILCD_ss1_m__0__HSIOM)
    
    #define SPILCD_SS1_M_HSIOM_MASK       (SPILCD_ss1_m__0__HSIOM_MASK)
    #define SPILCD_SS1_M_HSIOM_POS        (SPILCD_ss1_m__0__HSIOM_SHIFT)
    #define SPILCD_SS1_M_HSIOM_SEL_GPIO   (SPILCD_ss1_m__0__HSIOM_GPIO)
    #define SPILCD_SS1_M_HSIOM_SEL_SPI    (SPILCD_ss1_m__0__HSIOM_SPI)
#endif /* (SPILCD_SPI_MASTER_SS1_PIN) */

#if (SPILCD_SPI_MASTER_SS2_PIN)
    #define SPILCD_SS2_M_HSIOM_REG    (*(reg32 *) SPILCD_ss2_m__0__HSIOM)
    #define SPILCD_SS2_M_HSIOM_PTR    ( (reg32 *) SPILCD_ss2_m__0__HSIOM)
    
    #define SPILCD_SS2_M_HSIOM_MASK       (SPILCD_ss2_m__0__HSIOM_MASK)
    #define SPILCD_SS2_M_HSIOM_POS        (SPILCD_ss2_m__0__HSIOM_SHIFT)
    #define SPILCD_SS2_M_HSIOM_SEL_GPIO   (SPILCD_ss2_m__0__HSIOM_GPIO)
    #define SPILCD_SS2_M_HSIOM_SEL_SPI    (SPILCD_ss2_m__0__HSIOM_SPI)
#endif /* (SPILCD_SPI_MASTER_SS2_PIN) */

#if (SPILCD_SPI_MASTER_SS3_PIN)
    #define SPILCD_SS3_M_HSIOM_REG    (*(reg32 *) SPILCD_ss3_m__0__HSIOM)
    #define SPILCD_SS3_M_HSIOM_PTR    ( (reg32 *) SPILCD_ss3_m__0__HSIOM)
    
    #define SPILCD_SS3_M_HSIOM_MASK      (SPILCD_ss3_m__0__HSIOM_MASK)
    #define SPILCD_SS3_M_HSIOM_POS       (SPILCD_ss3_m__0__HSIOM_SHIFT)
    #define SPILCD_SS3_M_HSIOM_SEL_GPIO  (SPILCD_ss3_m__0__HSIOM_GPIO)
    #define SPILCD_SS3_M_HSIOM_SEL_SPI   (SPILCD_ss3_m__0__HSIOM_SPI)
#endif /* (SPILCD_SPI_MASTER_SS3_PIN) */

#if (SPILCD_UART_RX_PIN)
    #define SPILCD_RX_HSIOM_REG   (*(reg32 *) SPILCD_rx__0__HSIOM)
    #define SPILCD_RX_HSIOM_PTR   ( (reg32 *) SPILCD_rx__0__HSIOM)
    
    #define SPILCD_RX_HSIOM_MASK      (SPILCD_rx__0__HSIOM_MASK)
    #define SPILCD_RX_HSIOM_POS       (SPILCD_rx__0__HSIOM_SHIFT)
    #define SPILCD_RX_HSIOM_SEL_GPIO  (SPILCD_rx__0__HSIOM_GPIO)
    #define SPILCD_RX_HSIOM_SEL_UART  (SPILCD_rx__0__HSIOM_UART)
#endif /* (SPILCD_UART_RX_PIN) */

#if (SPILCD_UART_RX_WAKE_PIN)
    #define SPILCD_RX_WAKE_HSIOM_REG   (*(reg32 *) SPILCD_rx_wake__0__HSIOM)
    #define SPILCD_RX_WAKE_HSIOM_PTR   ( (reg32 *) SPILCD_rx_wake__0__HSIOM)
    
    #define SPILCD_RX_WAKE_HSIOM_MASK      (SPILCD_rx_wake__0__HSIOM_MASK)
    #define SPILCD_RX_WAKE_HSIOM_POS       (SPILCD_rx_wake__0__HSIOM_SHIFT)
    #define SPILCD_RX_WAKE_HSIOM_SEL_GPIO  (SPILCD_rx_wake__0__HSIOM_GPIO)
    #define SPILCD_RX_WAKE_HSIOM_SEL_UART  (SPILCD_rx_wake__0__HSIOM_UART)
#endif /* (SPILCD_UART_WAKE_RX_PIN) */

#if (SPILCD_UART_CTS_PIN)
    #define SPILCD_CTS_HSIOM_REG   (*(reg32 *) SPILCD_cts__0__HSIOM)
    #define SPILCD_CTS_HSIOM_PTR   ( (reg32 *) SPILCD_cts__0__HSIOM)
    
    #define SPILCD_CTS_HSIOM_MASK      (SPILCD_cts__0__HSIOM_MASK)
    #define SPILCD_CTS_HSIOM_POS       (SPILCD_cts__0__HSIOM_SHIFT)
    #define SPILCD_CTS_HSIOM_SEL_GPIO  (SPILCD_cts__0__HSIOM_GPIO)
    #define SPILCD_CTS_HSIOM_SEL_UART  (SPILCD_cts__0__HSIOM_UART)
#endif /* (SPILCD_UART_CTS_PIN) */

#if (SPILCD_UART_TX_PIN)
    #define SPILCD_TX_HSIOM_REG   (*(reg32 *) SPILCD_tx__0__HSIOM)
    #define SPILCD_TX_HSIOM_PTR   ( (reg32 *) SPILCD_tx__0__HSIOM)
    
    #define SPILCD_TX_HSIOM_MASK      (SPILCD_tx__0__HSIOM_MASK)
    #define SPILCD_TX_HSIOM_POS       (SPILCD_tx__0__HSIOM_SHIFT)
    #define SPILCD_TX_HSIOM_SEL_GPIO  (SPILCD_tx__0__HSIOM_GPIO)
    #define SPILCD_TX_HSIOM_SEL_UART  (SPILCD_tx__0__HSIOM_UART)
#endif /* (SPILCD_UART_TX_PIN) */

#if (SPILCD_UART_RX_TX_PIN)
    #define SPILCD_RX_TX_HSIOM_REG   (*(reg32 *) SPILCD_rx_tx__0__HSIOM)
    #define SPILCD_RX_TX_HSIOM_PTR   ( (reg32 *) SPILCD_rx_tx__0__HSIOM)
    
    #define SPILCD_RX_TX_HSIOM_MASK      (SPILCD_rx_tx__0__HSIOM_MASK)
    #define SPILCD_RX_TX_HSIOM_POS       (SPILCD_rx_tx__0__HSIOM_SHIFT)
    #define SPILCD_RX_TX_HSIOM_SEL_GPIO  (SPILCD_rx_tx__0__HSIOM_GPIO)
    #define SPILCD_RX_TX_HSIOM_SEL_UART  (SPILCD_rx_tx__0__HSIOM_UART)
#endif /* (SPILCD_UART_RX_TX_PIN) */

#if (SPILCD_UART_RTS_PIN)
    #define SPILCD_RTS_HSIOM_REG      (*(reg32 *) SPILCD_rts__0__HSIOM)
    #define SPILCD_RTS_HSIOM_PTR      ( (reg32 *) SPILCD_rts__0__HSIOM)
    
    #define SPILCD_RTS_HSIOM_MASK     (SPILCD_rts__0__HSIOM_MASK)
    #define SPILCD_RTS_HSIOM_POS      (SPILCD_rts__0__HSIOM_SHIFT)    
    #define SPILCD_RTS_HSIOM_SEL_GPIO (SPILCD_rts__0__HSIOM_GPIO)
    #define SPILCD_RTS_HSIOM_SEL_UART (SPILCD_rts__0__HSIOM_UART)    
#endif /* (SPILCD_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define SPILCD_HSIOM_DEF_SEL      (0x00u)
#define SPILCD_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for SPILCD_CY_SCBIP_V0 
* and SPILCD_CY_SCBIP_V1. It is not recommended to use them for 
* SPILCD_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define SPILCD_HSIOM_UART_SEL     (0x09u)
#define SPILCD_HSIOM_I2C_SEL      (0x0Eu)
#define SPILCD_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define SPILCD_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define SPILCD_RX_SCL_MOSI_PIN_INDEX       (0u)
#define SPILCD_TX_SDA_MISO_PIN_INDEX       (1u)
#define SPILCD_SCLK_PIN_INDEX       (2u)
#define SPILCD_SS0_PIN_INDEX       (3u)
#define SPILCD_SS1_PIN_INDEX                  (4u)
#define SPILCD_SS2_PIN_INDEX                  (5u)
#define SPILCD_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define SPILCD_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << SPILCD_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define SPILCD_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << SPILCD_RX_SCL_MOSI_PIN_INDEX)
#define SPILCD_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << SPILCD_TX_SDA_MISO_PIN_INDEX)
#define SPILCD_SCLK_PIN_MASK     ((uint32) 0x01u << SPILCD_SCLK_PIN_INDEX)
#define SPILCD_SS0_PIN_MASK     ((uint32) 0x01u << SPILCD_SS0_PIN_INDEX)
#define SPILCD_SS1_PIN_MASK                ((uint32) 0x01u << SPILCD_SS1_PIN_INDEX)
#define SPILCD_SS2_PIN_MASK                ((uint32) 0x01u << SPILCD_SS2_PIN_INDEX)
#define SPILCD_SS3_PIN_MASK                ((uint32) 0x01u << SPILCD_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define SPILCD_INTCFG_TYPE_MASK           (0x03u)
#define SPILCD_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define SPILCD_PIN_DM_ALG_HIZ  (0u)
#define SPILCD_PIN_DM_DIG_HIZ  (1u)
#define SPILCD_PIN_DM_OD_LO    (4u)
#define SPILCD_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define SPILCD_DM_MASK    (0x7u)
#define SPILCD_DM_SIZE    (3u)
#define SPILCD_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) SPILCD_DM_MASK << (SPILCD_DM_SIZE * (pos)))) >> \
                                                              (SPILCD_DM_SIZE * (pos)) )

#if (SPILCD_TX_SDA_MISO_PIN)
    #define SPILCD_CHECK_TX_SDA_MISO_PIN_USED \
                (SPILCD_PIN_DM_ALG_HIZ != \
                    SPILCD_GET_P4_PIN_DM(SPILCD_uart_tx_i2c_sda_spi_miso_PC, \
                                                   SPILCD_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (SPILCD_TX_SDA_MISO_PIN) */

#if (SPILCD_SS0_PIN)
    #define SPILCD_CHECK_SS0_PIN_USED \
                (SPILCD_PIN_DM_ALG_HIZ != \
                    SPILCD_GET_P4_PIN_DM(SPILCD_spi_ss0_PC, \
                                                   SPILCD_spi_ss0_SHIFT))
#endif /* (SPILCD_SS0_PIN) */

/* Set bits-mask in register */
#define SPILCD_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define SPILCD_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define SPILCD_SET_HSIOM_SEL(reg, mask, pos, sel) SPILCD_SET_REGISTER_BITS(reg, mask, pos, sel)
#define SPILCD_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        SPILCD_SET_REGISTER_BITS(reg, mask, pos, intType)
#define SPILCD_SET_INP_DIS(reg, mask, val) SPILCD_SET_REGISTER_BIT(reg, mask, val)

/* SPILCD_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  SPILCD_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (SPILCD_CY_SCBIP_V0)
#if (SPILCD_I2C_PINS)
    #define SPILCD_SET_I2C_SCL_DR(val) SPILCD_scl_Write(val)

    #define SPILCD_SET_I2C_SCL_HSIOM_SEL(sel) \
                          SPILCD_SET_HSIOM_SEL(SPILCD_SCL_HSIOM_REG,  \
                                                         SPILCD_SCL_HSIOM_MASK, \
                                                         SPILCD_SCL_HSIOM_POS,  \
                                                         (sel))
    #define SPILCD_WAIT_SCL_SET_HIGH  (0u == SPILCD_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (SPILCD_RX_WAKE_SCL_MOSI_PIN)
    #define SPILCD_SET_I2C_SCL_DR(val) \
                            SPILCD_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define SPILCD_SET_I2C_SCL_HSIOM_SEL(sel) \
                    SPILCD_SET_HSIOM_SEL(SPILCD_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   SPILCD_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   SPILCD_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define SPILCD_WAIT_SCL_SET_HIGH  (0u == SPILCD_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (SPILCD_RX_SCL_MOSI_PIN)
    #define SPILCD_SET_I2C_SCL_DR(val) \
                            SPILCD_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define SPILCD_SET_I2C_SCL_HSIOM_SEL(sel) \
                            SPILCD_SET_HSIOM_SEL(SPILCD_RX_SCL_MOSI_HSIOM_REG,  \
                                                           SPILCD_RX_SCL_MOSI_HSIOM_MASK, \
                                                           SPILCD_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define SPILCD_WAIT_SCL_SET_HIGH  (0u == SPILCD_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define SPILCD_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define SPILCD_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define SPILCD_WAIT_SCL_SET_HIGH  (0u)
#endif /* (SPILCD_I2C_PINS) */

/* SCB I2C: sda signal */
#if (SPILCD_I2C_PINS)
    #define SPILCD_WAIT_SDA_SET_HIGH  (0u == SPILCD_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (SPILCD_TX_SDA_MISO_PIN)
    #define SPILCD_WAIT_SDA_SET_HIGH  (0u == SPILCD_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define SPILCD_WAIT_SDA_SET_HIGH  (0u)
#endif /* (SPILCD_MOSI_SCL_RX_PIN) */
#endif /* (SPILCD_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (SPILCD_RX_SCL_MOSI_PIN)
    #define SPILCD_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (SPILCD_RX_WAKE_SCL_MOSI_PIN)
    #define SPILCD_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) SPILCD_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(SPILCD_UART_RX_WAKE_PIN)
    #define SPILCD_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) SPILCD_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (SPILCD_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define SPILCD_REMOVE_MOSI_SCL_RX_WAKE_PIN    SPILCD_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define SPILCD_REMOVE_MOSI_SCL_RX_PIN         SPILCD_REMOVE_RX_SCL_MOSI_PIN
#define SPILCD_REMOVE_MISO_SDA_TX_PIN         SPILCD_REMOVE_TX_SDA_MISO_PIN
#ifndef SPILCD_REMOVE_SCLK_PIN
#define SPILCD_REMOVE_SCLK_PIN                SPILCD_REMOVE_SCLK_PIN
#endif /* SPILCD_REMOVE_SCLK_PIN */
#ifndef SPILCD_REMOVE_SS0_PIN
#define SPILCD_REMOVE_SS0_PIN                 SPILCD_REMOVE_SS0_PIN
#endif /* SPILCD_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define SPILCD_MOSI_SCL_RX_WAKE_PIN   SPILCD_RX_WAKE_SCL_MOSI_PIN
#define SPILCD_MOSI_SCL_RX_PIN        SPILCD_RX_SCL_MOSI_PIN
#define SPILCD_MISO_SDA_TX_PIN        SPILCD_TX_SDA_MISO_PIN
#ifndef SPILCD_SCLK_PIN
#define SPILCD_SCLK_PIN               SPILCD_SCLK_PIN
#endif /* SPILCD_SCLK_PIN */
#ifndef SPILCD_SS0_PIN
#define SPILCD_SS0_PIN                SPILCD_SS0_PIN
#endif /* SPILCD_SS0_PIN */

#if (SPILCD_MOSI_SCL_RX_WAKE_PIN)
    #define SPILCD_MOSI_SCL_RX_WAKE_HSIOM_REG     SPILCD_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPILCD_MOSI_SCL_RX_WAKE_HSIOM_PTR     SPILCD_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPILCD_MOSI_SCL_RX_WAKE_HSIOM_MASK    SPILCD_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPILCD_MOSI_SCL_RX_WAKE_HSIOM_POS     SPILCD_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define SPILCD_MOSI_SCL_RX_WAKE_INTCFG_REG    SPILCD_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPILCD_MOSI_SCL_RX_WAKE_INTCFG_PTR    SPILCD_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define SPILCD_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   SPILCD_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPILCD_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  SPILCD_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (SPILCD_RX_WAKE_SCL_MOSI_PIN) */

#if (SPILCD_MOSI_SCL_RX_PIN)
    #define SPILCD_MOSI_SCL_RX_HSIOM_REG      SPILCD_RX_SCL_MOSI_HSIOM_REG
    #define SPILCD_MOSI_SCL_RX_HSIOM_PTR      SPILCD_RX_SCL_MOSI_HSIOM_PTR
    #define SPILCD_MOSI_SCL_RX_HSIOM_MASK     SPILCD_RX_SCL_MOSI_HSIOM_MASK
    #define SPILCD_MOSI_SCL_RX_HSIOM_POS      SPILCD_RX_SCL_MOSI_HSIOM_POS
#endif /* (SPILCD_MOSI_SCL_RX_PIN) */

#if (SPILCD_MISO_SDA_TX_PIN)
    #define SPILCD_MISO_SDA_TX_HSIOM_REG      SPILCD_TX_SDA_MISO_HSIOM_REG
    #define SPILCD_MISO_SDA_TX_HSIOM_PTR      SPILCD_TX_SDA_MISO_HSIOM_REG
    #define SPILCD_MISO_SDA_TX_HSIOM_MASK     SPILCD_TX_SDA_MISO_HSIOM_REG
    #define SPILCD_MISO_SDA_TX_HSIOM_POS      SPILCD_TX_SDA_MISO_HSIOM_REG
#endif /* (SPILCD_MISO_SDA_TX_PIN_PIN) */

#if (SPILCD_SCLK_PIN)
    #ifndef SPILCD_SCLK_HSIOM_REG
    #define SPILCD_SCLK_HSIOM_REG     SPILCD_SCLK_HSIOM_REG
    #define SPILCD_SCLK_HSIOM_PTR     SPILCD_SCLK_HSIOM_PTR
    #define SPILCD_SCLK_HSIOM_MASK    SPILCD_SCLK_HSIOM_MASK
    #define SPILCD_SCLK_HSIOM_POS     SPILCD_SCLK_HSIOM_POS
    #endif /* SPILCD_SCLK_HSIOM_REG */
#endif /* (SPILCD_SCLK_PIN) */

#if (SPILCD_SS0_PIN)
    #ifndef SPILCD_SS0_HSIOM_REG
    #define SPILCD_SS0_HSIOM_REG      SPILCD_SS0_HSIOM_REG
    #define SPILCD_SS0_HSIOM_PTR      SPILCD_SS0_HSIOM_PTR
    #define SPILCD_SS0_HSIOM_MASK     SPILCD_SS0_HSIOM_MASK
    #define SPILCD_SS0_HSIOM_POS      SPILCD_SS0_HSIOM_POS
    #endif /* SPILCD_SS0_HSIOM_REG */
#endif /* (SPILCD_SS0_PIN) */

#define SPILCD_MOSI_SCL_RX_WAKE_PIN_INDEX SPILCD_RX_WAKE_SCL_MOSI_PIN_INDEX
#define SPILCD_MOSI_SCL_RX_PIN_INDEX      SPILCD_RX_SCL_MOSI_PIN_INDEX
#define SPILCD_MISO_SDA_TX_PIN_INDEX      SPILCD_TX_SDA_MISO_PIN_INDEX
#ifndef SPILCD_SCLK_PIN_INDEX
#define SPILCD_SCLK_PIN_INDEX             SPILCD_SCLK_PIN_INDEX
#endif /* SPILCD_SCLK_PIN_INDEX */
#ifndef SPILCD_SS0_PIN_INDEX
#define SPILCD_SS0_PIN_INDEX              SPILCD_SS0_PIN_INDEX
#endif /* SPILCD_SS0_PIN_INDEX */

#define SPILCD_MOSI_SCL_RX_WAKE_PIN_MASK SPILCD_RX_WAKE_SCL_MOSI_PIN_MASK
#define SPILCD_MOSI_SCL_RX_PIN_MASK      SPILCD_RX_SCL_MOSI_PIN_MASK
#define SPILCD_MISO_SDA_TX_PIN_MASK      SPILCD_TX_SDA_MISO_PIN_MASK
#ifndef SPILCD_SCLK_PIN_MASK
#define SPILCD_SCLK_PIN_MASK             SPILCD_SCLK_PIN_MASK
#endif /* SPILCD_SCLK_PIN_MASK */
#ifndef SPILCD_SS0_PIN_MASK
#define SPILCD_SS0_PIN_MASK              SPILCD_SS0_PIN_MASK
#endif /* SPILCD_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_SPILCD_H) */


/* [] END OF FILE */
