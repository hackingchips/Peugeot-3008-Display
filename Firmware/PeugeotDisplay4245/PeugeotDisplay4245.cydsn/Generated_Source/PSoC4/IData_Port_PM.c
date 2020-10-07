/*******************************************************************************
* File Name: IData_Port.c  
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
#include "IData_Port.h"

static IData_Port_BACKUP_STRUCT  IData_Port_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: IData_Port_Sleep
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
*  \snippet IData_Port_SUT.c usage_IData_Port_Sleep_Wakeup
*******************************************************************************/
void IData_Port_Sleep(void)
{
    #if defined(IData_Port__PC)
        IData_Port_backup.pcState = IData_Port_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            IData_Port_backup.usbState = IData_Port_CR1_REG;
            IData_Port_USB_POWER_REG |= IData_Port_USBIO_ENTER_SLEEP;
            IData_Port_CR1_REG &= IData_Port_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(IData_Port__SIO)
        IData_Port_backup.sioState = IData_Port_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        IData_Port_SIO_REG &= (uint32)(~IData_Port_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: IData_Port_Wakeup
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
*  Refer to IData_Port_Sleep() for an example usage.
*******************************************************************************/
void IData_Port_Wakeup(void)
{
    #if defined(IData_Port__PC)
        IData_Port_PC = IData_Port_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            IData_Port_USB_POWER_REG &= IData_Port_USBIO_EXIT_SLEEP_PH1;
            IData_Port_CR1_REG = IData_Port_backup.usbState;
            IData_Port_USB_POWER_REG &= IData_Port_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(IData_Port__SIO)
        IData_Port_SIO_REG = IData_Port_backup.sioState;
    #endif
}


/* [] END OF FILE */
