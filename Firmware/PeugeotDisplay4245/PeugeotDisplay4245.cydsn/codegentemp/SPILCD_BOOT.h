/***************************************************************************//**
* \file SPILCD_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_SPILCD_H)
#define CY_SCB_BOOT_SPILCD_H

#include "SPILCD_PVT.h"

#if (SPILCD_SCB_MODE_I2C_INC)
    #include "SPILCD_I2C.h"
#endif /* (SPILCD_SCB_MODE_I2C_INC) */

#if (SPILCD_SCB_MODE_EZI2C_INC)
    #include "SPILCD_EZI2C.h"
#endif /* (SPILCD_SCB_MODE_EZI2C_INC) */

#if (SPILCD_SCB_MODE_SPI_INC || SPILCD_SCB_MODE_UART_INC)
    #include "SPILCD_SPI_UART.h"
#endif /* (SPILCD_SCB_MODE_SPI_INC || SPILCD_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define SPILCD_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPILCD) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (SPILCD_SCB_MODE_I2C_INC)
    #define SPILCD_I2C_BTLDR_COMM_ENABLED     (SPILCD_BTLDR_COMM_ENABLED && \
                                                            (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SPILCD_I2C_SLAVE_CONST))
#else
     #define SPILCD_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (SPILCD_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (SPILCD_SCB_MODE_EZI2C_INC)
    #define SPILCD_EZI2C_BTLDR_COMM_ENABLED   (SPILCD_BTLDR_COMM_ENABLED && \
                                                         SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define SPILCD_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (SPILCD_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (SPILCD_SCB_MODE_SPI_INC)
    #define SPILCD_SPI_BTLDR_COMM_ENABLED     (SPILCD_BTLDR_COMM_ENABLED && \
                                                            (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SPILCD_SPI_SLAVE_CONST))
#else
        #define SPILCD_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (SPILCD_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (SPILCD_SCB_MODE_UART_INC)
       #define SPILCD_UART_BTLDR_COMM_ENABLED    (SPILCD_BTLDR_COMM_ENABLED && \
                                                            (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (SPILCD_UART_RX_DIRECTION && \
                                                              SPILCD_UART_TX_DIRECTION)))
#else
     #define SPILCD_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (SPILCD_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define SPILCD_BTLDR_COMM_MODE_ENABLED    (SPILCD_I2C_BTLDR_COMM_ENABLED   || \
                                                     SPILCD_SPI_BTLDR_COMM_ENABLED   || \
                                                     SPILCD_EZI2C_BTLDR_COMM_ENABLED || \
                                                     SPILCD_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPILCD_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void SPILCD_I2CCyBtldrCommStart(void);
    void SPILCD_I2CCyBtldrCommStop (void);
    void SPILCD_I2CCyBtldrCommReset(void);
    cystatus SPILCD_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SPILCD_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (SPILCD_SCB_MODE_I2C_CONST_CFG)
        #define SPILCD_CyBtldrCommStart   SPILCD_I2CCyBtldrCommStart
        #define SPILCD_CyBtldrCommStop    SPILCD_I2CCyBtldrCommStop
        #define SPILCD_CyBtldrCommReset   SPILCD_I2CCyBtldrCommReset
        #define SPILCD_CyBtldrCommRead    SPILCD_I2CCyBtldrCommRead
        #define SPILCD_CyBtldrCommWrite   SPILCD_I2CCyBtldrCommWrite
    #endif /* (SPILCD_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPILCD_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPILCD_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void SPILCD_EzI2CCyBtldrCommStart(void);
    void SPILCD_EzI2CCyBtldrCommStop (void);
    void SPILCD_EzI2CCyBtldrCommReset(void);
    cystatus SPILCD_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SPILCD_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (SPILCD_SCB_MODE_EZI2C_CONST_CFG)
        #define SPILCD_CyBtldrCommStart   SPILCD_EzI2CCyBtldrCommStart
        #define SPILCD_CyBtldrCommStop    SPILCD_EzI2CCyBtldrCommStop
        #define SPILCD_CyBtldrCommReset   SPILCD_EzI2CCyBtldrCommReset
        #define SPILCD_CyBtldrCommRead    SPILCD_EzI2CCyBtldrCommRead
        #define SPILCD_CyBtldrCommWrite   SPILCD_EzI2CCyBtldrCommWrite
    #endif /* (SPILCD_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPILCD_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPILCD_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void SPILCD_SpiCyBtldrCommStart(void);
    void SPILCD_SpiCyBtldrCommStop (void);
    void SPILCD_SpiCyBtldrCommReset(void);
    cystatus SPILCD_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SPILCD_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (SPILCD_SCB_MODE_SPI_CONST_CFG)
        #define SPILCD_CyBtldrCommStart   SPILCD_SpiCyBtldrCommStart
        #define SPILCD_CyBtldrCommStop    SPILCD_SpiCyBtldrCommStop
        #define SPILCD_CyBtldrCommReset   SPILCD_SpiCyBtldrCommReset
        #define SPILCD_CyBtldrCommRead    SPILCD_SpiCyBtldrCommRead
        #define SPILCD_CyBtldrCommWrite   SPILCD_SpiCyBtldrCommWrite
    #endif /* (SPILCD_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPILCD_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPILCD_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void SPILCD_UartCyBtldrCommStart(void);
    void SPILCD_UartCyBtldrCommStop (void);
    void SPILCD_UartCyBtldrCommReset(void);
    cystatus SPILCD_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SPILCD_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (SPILCD_SCB_MODE_UART_CONST_CFG)
        #define SPILCD_CyBtldrCommStart   SPILCD_UartCyBtldrCommStart
        #define SPILCD_CyBtldrCommStop    SPILCD_UartCyBtldrCommStop
        #define SPILCD_CyBtldrCommReset   SPILCD_UartCyBtldrCommReset
        #define SPILCD_CyBtldrCommRead    SPILCD_UartCyBtldrCommRead
        #define SPILCD_CyBtldrCommWrite   SPILCD_UartCyBtldrCommWrite
    #endif /* (SPILCD_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPILCD_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPILCD_BTLDR_COMM_ENABLED)
    #if (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void SPILCD_CyBtldrCommStart(void);
        void SPILCD_CyBtldrCommStop (void);
        void SPILCD_CyBtldrCommReset(void);
        cystatus SPILCD_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus SPILCD_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPILCD)
        #define CyBtldrCommStart    SPILCD_CyBtldrCommStart
        #define CyBtldrCommStop     SPILCD_CyBtldrCommStop
        #define CyBtldrCommReset    SPILCD_CyBtldrCommReset
        #define CyBtldrCommWrite    SPILCD_CyBtldrCommWrite
        #define CyBtldrCommRead     SPILCD_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPILCD) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPILCD_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define SPILCD_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define SPILCD_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define SPILCD_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define SPILCD_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef SPILCD_SPI_BYTE_TO_BYTE
    #define SPILCD_SPI_BYTE_TO_BYTE   (2u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef SPILCD_UART_BYTE_TO_BYTE
    #define SPILCD_UART_BYTE_TO_BYTE  (2500u)
#endif /* SPILCD_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_SPILCD_H) */


/* [] END OF FILE */
