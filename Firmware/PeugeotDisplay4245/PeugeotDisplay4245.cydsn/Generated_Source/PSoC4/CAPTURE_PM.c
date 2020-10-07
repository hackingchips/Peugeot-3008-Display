/*******************************************************************************
* File Name: CAPTURE.c  
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
#include "CAPTURE.h"

static CAPTURE_BACKUP_STRUCT  CAPTURE_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: CAPTURE_Sleep
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
*  \snippet CAPTURE_SUT.c usage_CAPTURE_Sleep_Wakeup
*******************************************************************************/
void CAPTURE_Sleep(void)
{
    #if defined(CAPTURE__PC)
        CAPTURE_backup.pcState = CAPTURE_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            CAPTURE_backup.usbState = CAPTURE_CR1_REG;
            CAPTURE_USB_POWER_REG |= CAPTURE_USBIO_ENTER_SLEEP;
            CAPTURE_CR1_REG &= CAPTURE_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CAPTURE__SIO)
        CAPTURE_backup.sioState = CAPTURE_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        CAPTURE_SIO_REG &= (uint32)(~CAPTURE_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: CAPTURE_Wakeup
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
*  Refer to CAPTURE_Sleep() for an example usage.
*******************************************************************************/
void CAPTURE_Wakeup(void)
{
    #if defined(CAPTURE__PC)
        CAPTURE_PC = CAPTURE_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            CAPTURE_USB_POWER_REG &= CAPTURE_USBIO_EXIT_SLEEP_PH1;
            CAPTURE_CR1_REG = CAPTURE_backup.usbState;
            CAPTURE_USB_POWER_REG &= CAPTURE_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CAPTURE__SIO)
        CAPTURE_SIO_REG = CAPTURE_backup.sioState;
    #endif
}


/* [] END OF FILE */
