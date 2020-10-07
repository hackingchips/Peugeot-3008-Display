/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
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

#if !defined(CY_SCB_PVT_SPILCD_H)
#define CY_SCB_PVT_SPILCD_H

#include "SPILCD.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define SPILCD_SetI2CExtClkInterruptMode(interruptMask) SPILCD_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define SPILCD_ClearI2CExtClkInterruptSource(interruptMask) SPILCD_CLEAR_INTR_I2C_EC(interruptMask)
#define SPILCD_GetI2CExtClkInterruptSource()                (SPILCD_INTR_I2C_EC_REG)
#define SPILCD_GetI2CExtClkInterruptMode()                  (SPILCD_INTR_I2C_EC_MASK_REG)
#define SPILCD_GetI2CExtClkInterruptSourceMasked()          (SPILCD_INTR_I2C_EC_MASKED_REG)

#if (!SPILCD_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define SPILCD_SetSpiExtClkInterruptMode(interruptMask) \
                                                                SPILCD_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define SPILCD_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                SPILCD_CLEAR_INTR_SPI_EC(interruptMask)
    #define SPILCD_GetExtSpiClkInterruptSource()                 (SPILCD_INTR_SPI_EC_REG)
    #define SPILCD_GetExtSpiClkInterruptMode()                   (SPILCD_INTR_SPI_EC_MASK_REG)
    #define SPILCD_GetExtSpiClkInterruptSourceMasked()           (SPILCD_INTR_SPI_EC_MASKED_REG)
#endif /* (!SPILCD_CY_SCBIP_V1) */

#if(SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void SPILCD_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (SPILCD_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SPILCD_CUSTOM_INTR_HANDLER)
    extern cyisraddress SPILCD_customIntrHandler;
#endif /* !defined (CY_REMOVE_SPILCD_CUSTOM_INTR_HANDLER) */
#endif /* (SPILCD_SCB_IRQ_INTERNAL) */

extern SPILCD_BACKUP_STRUCT SPILCD_backup;

#if(SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 SPILCD_scbMode;
    extern uint8 SPILCD_scbEnableWake;
    extern uint8 SPILCD_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 SPILCD_mode;
    extern uint8 SPILCD_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * SPILCD_rxBuffer;
    extern uint8   SPILCD_rxDataBits;
    extern uint32  SPILCD_rxBufferSize;

    extern volatile uint8 * SPILCD_txBuffer;
    extern uint8   SPILCD_txDataBits;
    extern uint32  SPILCD_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 SPILCD_numberOfAddr;
    extern uint8 SPILCD_subAddrSize;
#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (SPILCD_SCB_MODE_I2C_CONST_CFG || \
        SPILCD_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 SPILCD_IntrTxMask;
#endif /* (! (SPILCD_SCB_MODE_I2C_CONST_CFG || \
              SPILCD_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define SPILCD_SCB_MODE_I2C_RUNTM_CFG     (SPILCD_SCB_MODE_I2C      == SPILCD_scbMode)
    #define SPILCD_SCB_MODE_SPI_RUNTM_CFG     (SPILCD_SCB_MODE_SPI      == SPILCD_scbMode)
    #define SPILCD_SCB_MODE_UART_RUNTM_CFG    (SPILCD_SCB_MODE_UART     == SPILCD_scbMode)
    #define SPILCD_SCB_MODE_EZI2C_RUNTM_CFG   (SPILCD_SCB_MODE_EZI2C    == SPILCD_scbMode)
    #define SPILCD_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (SPILCD_SCB_MODE_UNCONFIG == SPILCD_scbMode)

    /* Defines wakeup enable */
    #define SPILCD_SCB_WAKE_ENABLE_CHECK       (0u != SPILCD_scbEnableWake)
#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!SPILCD_CY_SCBIP_V1)
    #define SPILCD_SCB_PINS_NUMBER    (7u)
#else
    #define SPILCD_SCB_PINS_NUMBER    (2u)
#endif /* (!SPILCD_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_SPILCD_H) */


/* [] END OF FILE */
