/*******************************************************************************
* File Name: IData_Port.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_IData_Port_H) /* Pins IData_Port_H */
#define CY_PINS_IData_Port_H

#include "cytypes.h"
#include "cyfitter.h"
#include "IData_Port_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} IData_Port_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   IData_Port_Read(void);
void    IData_Port_Write(uint8 value);
uint8   IData_Port_ReadDataReg(void);
#if defined(IData_Port__PC) || (CY_PSOC4_4200L) 
    void    IData_Port_SetDriveMode(uint8 mode);
#endif
void    IData_Port_SetInterruptMode(uint16 position, uint16 mode);
uint8   IData_Port_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void IData_Port_Sleep(void); 
void IData_Port_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(IData_Port__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define IData_Port_DRIVE_MODE_BITS        (3)
    #define IData_Port_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - IData_Port_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the IData_Port_SetDriveMode() function.
         *  @{
         */
        #define IData_Port_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define IData_Port_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define IData_Port_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define IData_Port_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define IData_Port_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define IData_Port_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define IData_Port_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define IData_Port_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define IData_Port_MASK               IData_Port__MASK
#define IData_Port_SHIFT              IData_Port__SHIFT
#define IData_Port_WIDTH              8u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IData_Port_SetInterruptMode() function.
     *  @{
     */
        #define IData_Port_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define IData_Port_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define IData_Port_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define IData_Port_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(IData_Port__SIO)
    #define IData_Port_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(IData_Port__PC) && (CY_PSOC4_4200L)
    #define IData_Port_USBIO_ENABLE               ((uint32)0x80000000u)
    #define IData_Port_USBIO_DISABLE              ((uint32)(~IData_Port_USBIO_ENABLE))
    #define IData_Port_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define IData_Port_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define IData_Port_USBIO_ENTER_SLEEP          ((uint32)((1u << IData_Port_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << IData_Port_USBIO_SUSPEND_DEL_SHIFT)))
    #define IData_Port_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << IData_Port_USBIO_SUSPEND_SHIFT)))
    #define IData_Port_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << IData_Port_USBIO_SUSPEND_DEL_SHIFT)))
    #define IData_Port_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(IData_Port__PC)
    /* Port Configuration */
    #define IData_Port_PC                 (* (reg32 *) IData_Port__PC)
#endif
/* Pin State */
#define IData_Port_PS                     (* (reg32 *) IData_Port__PS)
/* Data Register */
#define IData_Port_DR                     (* (reg32 *) IData_Port__DR)
/* Input Buffer Disable Override */
#define IData_Port_INP_DIS                (* (reg32 *) IData_Port__PC2)

/* Interrupt configuration Registers */
#define IData_Port_INTCFG                 (* (reg32 *) IData_Port__INTCFG)
#define IData_Port_INTSTAT                (* (reg32 *) IData_Port__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define IData_Port_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(IData_Port__SIO)
    #define IData_Port_SIO_REG            (* (reg32 *) IData_Port__SIO)
#endif /* (IData_Port__SIO_CFG) */

/* USBIO registers */
#if !defined(IData_Port__PC) && (CY_PSOC4_4200L)
    #define IData_Port_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define IData_Port_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define IData_Port_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define IData_Port_DRIVE_MODE_SHIFT       (0x00u)
#define IData_Port_DRIVE_MODE_MASK        (0x07u << IData_Port_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins IData_Port_H */


/* [] END OF FILE */
