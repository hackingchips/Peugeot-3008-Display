/***************************************************************************//**
* \file SPILCD_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
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

#include "SPILCD.h"
#include "SPILCD_PVT.h"

#if(SPILCD_SCB_MODE_I2C_INC)
    #include "SPILCD_I2C_PVT.h"
#endif /* (SPILCD_SCB_MODE_I2C_INC) */

#if(SPILCD_SCB_MODE_EZI2C_INC)
    #include "SPILCD_EZI2C_PVT.h"
#endif /* (SPILCD_SCB_MODE_EZI2C_INC) */

#if(SPILCD_SCB_MODE_SPI_INC || SPILCD_SCB_MODE_UART_INC)
    #include "SPILCD_SPI_UART_PVT.h"
#endif /* (SPILCD_SCB_MODE_SPI_INC || SPILCD_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(SPILCD_SCB_MODE_UNCONFIG_CONST_CFG || \
   (SPILCD_SCB_MODE_I2C_CONST_CFG   && (!SPILCD_I2C_WAKE_ENABLE_CONST))   || \
   (SPILCD_SCB_MODE_EZI2C_CONST_CFG && (!SPILCD_EZI2C_WAKE_ENABLE_CONST)) || \
   (SPILCD_SCB_MODE_SPI_CONST_CFG   && (!SPILCD_SPI_WAKE_ENABLE_CONST))   || \
   (SPILCD_SCB_MODE_UART_CONST_CFG  && (!SPILCD_UART_WAKE_ENABLE_CONST)))

    SPILCD_BACKUP_STRUCT SPILCD_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: SPILCD_Sleep
****************************************************************************//**
*
*  Prepares the SPILCD component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the SPILCD_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void SPILCD_Sleep(void)
{
#if(SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SPILCD_SCB_WAKE_ENABLE_CHECK)
    {
        if(SPILCD_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPILCD_I2CSaveConfig();
        }
        else if(SPILCD_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPILCD_EzI2CSaveConfig();
        }
    #if(!SPILCD_CY_SCBIP_V1)
        else if(SPILCD_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPILCD_SpiSaveConfig();
        }
        else if(SPILCD_SCB_MODE_UART_RUNTM_CFG)
        {
            SPILCD_UartSaveConfig();
        }
    #endif /* (!SPILCD_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        SPILCD_backup.enableState = (uint8) SPILCD_GET_CTRL_ENABLED;

        if(0u != SPILCD_backup.enableState)
        {
            SPILCD_Stop();
        }
    }

#else

    #if (SPILCD_SCB_MODE_I2C_CONST_CFG && SPILCD_I2C_WAKE_ENABLE_CONST)
        SPILCD_I2CSaveConfig();

    #elif (SPILCD_SCB_MODE_EZI2C_CONST_CFG && SPILCD_EZI2C_WAKE_ENABLE_CONST)
        SPILCD_EzI2CSaveConfig();

    #elif (SPILCD_SCB_MODE_SPI_CONST_CFG && SPILCD_SPI_WAKE_ENABLE_CONST)
        SPILCD_SpiSaveConfig();

    #elif (SPILCD_SCB_MODE_UART_CONST_CFG && SPILCD_UART_WAKE_ENABLE_CONST)
        SPILCD_UartSaveConfig();

    #else

        SPILCD_backup.enableState = (uint8) SPILCD_GET_CTRL_ENABLED;

        if(0u != SPILCD_backup.enableState)
        {
            SPILCD_Stop();
        }

    #endif /* defined (SPILCD_SCB_MODE_I2C_CONST_CFG) && (SPILCD_I2C_WAKE_ENABLE_CONST) */

#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPILCD_Wakeup
****************************************************************************//**
*
*  Prepares the SPILCD component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the SPILCD_Wakeup() function without first calling the 
*   SPILCD_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void SPILCD_Wakeup(void)
{
#if(SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SPILCD_SCB_WAKE_ENABLE_CHECK)
    {
        if(SPILCD_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPILCD_I2CRestoreConfig();
        }
        else if(SPILCD_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPILCD_EzI2CRestoreConfig();
        }
    #if(!SPILCD_CY_SCBIP_V1)
        else if(SPILCD_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPILCD_SpiRestoreConfig();
        }
        else if(SPILCD_SCB_MODE_UART_RUNTM_CFG)
        {
            SPILCD_UartRestoreConfig();
        }
    #endif /* (!SPILCD_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != SPILCD_backup.enableState)
        {
            SPILCD_Enable();
        }
    }

#else

    #if (SPILCD_SCB_MODE_I2C_CONST_CFG  && SPILCD_I2C_WAKE_ENABLE_CONST)
        SPILCD_I2CRestoreConfig();

    #elif (SPILCD_SCB_MODE_EZI2C_CONST_CFG && SPILCD_EZI2C_WAKE_ENABLE_CONST)
        SPILCD_EzI2CRestoreConfig();

    #elif (SPILCD_SCB_MODE_SPI_CONST_CFG && SPILCD_SPI_WAKE_ENABLE_CONST)
        SPILCD_SpiRestoreConfig();

    #elif (SPILCD_SCB_MODE_UART_CONST_CFG && SPILCD_UART_WAKE_ENABLE_CONST)
        SPILCD_UartRestoreConfig();

    #else

        if(0u != SPILCD_backup.enableState)
        {
            SPILCD_Enable();
        }

    #endif /* (SPILCD_I2C_WAKE_ENABLE_CONST) */

#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
