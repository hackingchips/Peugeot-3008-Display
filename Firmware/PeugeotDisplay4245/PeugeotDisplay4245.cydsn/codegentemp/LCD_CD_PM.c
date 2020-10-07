/*******************************************************************************
* File Name: LCD_CD.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "LCD_CD.h"

static LCD_CD_BACKUP_STRUCT  LCD_CD_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: LCD_CD_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet LCD_CD_SUT.c usage_LCD_CD_Sleep_Wakeup
*******************************************************************************/
void LCD_CD_Sleep(void)
{
    #if defined(LCD_CD__PC)
        LCD_CD_backup.pcState = LCD_CD_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            LCD_CD_backup.usbState = LCD_CD_CR1_REG;
            LCD_CD_USB_POWER_REG |= LCD_CD_USBIO_ENTER_SLEEP;
            LCD_CD_CR1_REG &= LCD_CD_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LCD_CD__SIO)
        LCD_CD_backup.sioState = LCD_CD_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        LCD_CD_SIO_REG &= (uint32)(~LCD_CD_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: LCD_CD_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to LCD_CD_Sleep() for an example usage.
*******************************************************************************/
void LCD_CD_Wakeup(void)
{
    #if defined(LCD_CD__PC)
        LCD_CD_PC = LCD_CD_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            LCD_CD_USB_POWER_REG &= LCD_CD_USBIO_EXIT_SLEEP_PH1;
            LCD_CD_CR1_REG = LCD_CD_backup.usbState;
            LCD_CD_USB_POWER_REG &= LCD_CD_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LCD_CD__SIO)
        LCD_CD_SIO_REG = LCD_CD_backup.sioState;
    #endif
}


/* [] END OF FILE */
