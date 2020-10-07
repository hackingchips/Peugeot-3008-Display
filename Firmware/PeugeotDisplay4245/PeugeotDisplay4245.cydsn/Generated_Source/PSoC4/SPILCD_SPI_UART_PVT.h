/***************************************************************************//**
* \file SPILCD_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_SPILCD_H)
#define CY_SCB_SPI_UART_PVT_SPILCD_H

#include "SPILCD_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (SPILCD_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  SPILCD_rxBufferHead;
    extern volatile uint32  SPILCD_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   SPILCD_rxBufferOverflow;
    /** @} globals */
#endif /* (SPILCD_INTERNAL_RX_SW_BUFFER_CONST) */

#if (SPILCD_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  SPILCD_txBufferHead;
    extern volatile uint32  SPILCD_txBufferTail;
#endif /* (SPILCD_INTERNAL_TX_SW_BUFFER_CONST) */

#if (SPILCD_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 SPILCD_rxBufferInternal[SPILCD_INTERNAL_RX_BUFFER_SIZE];
#endif /* (SPILCD_INTERNAL_RX_SW_BUFFER) */

#if (SPILCD_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 SPILCD_txBufferInternal[SPILCD_TX_BUFFER_SIZE];
#endif /* (SPILCD_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void SPILCD_SpiPostEnable(void);
void SPILCD_SpiStop(void);

#if (SPILCD_SCB_MODE_SPI_CONST_CFG)
    void SPILCD_SpiInit(void);
#endif /* (SPILCD_SCB_MODE_SPI_CONST_CFG) */

#if (SPILCD_SPI_WAKE_ENABLE_CONST)
    void SPILCD_SpiSaveConfig(void);
    void SPILCD_SpiRestoreConfig(void);
#endif /* (SPILCD_SPI_WAKE_ENABLE_CONST) */

void SPILCD_UartPostEnable(void);
void SPILCD_UartStop(void);

#if (SPILCD_SCB_MODE_UART_CONST_CFG)
    void SPILCD_UartInit(void);
#endif /* (SPILCD_SCB_MODE_UART_CONST_CFG) */

#if (SPILCD_UART_WAKE_ENABLE_CONST)
    void SPILCD_UartSaveConfig(void);
    void SPILCD_UartRestoreConfig(void);
#endif /* (SPILCD_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in SPILCD_SetPins() */
#define SPILCD_UART_RX_PIN_ENABLE    (SPILCD_UART_RX)
#define SPILCD_UART_TX_PIN_ENABLE    (SPILCD_UART_TX)

/* UART RTS and CTS position to be used in  SPILCD_SetPins() */
#define SPILCD_UART_RTS_PIN_ENABLE    (0x10u)
#define SPILCD_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define SPILCD_SpiUartEnableIntRx(intSourceMask)  SPILCD_SetRxInterruptMode(intSourceMask)
#define SPILCD_SpiUartEnableIntTx(intSourceMask)  SPILCD_SetTxInterruptMode(intSourceMask)
uint32  SPILCD_SpiUartDisableIntRx(void);
uint32  SPILCD_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_SPILCD_H) */


/* [] END OF FILE */
