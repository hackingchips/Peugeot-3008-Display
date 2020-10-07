/*******************************************************************************
* File Name: E.h  
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

#if !defined(CY_PINS_E_H) /* Pins E_H */
#define CY_PINS_E_H

#include "cytypes.h"
#include "cyfitter.h"
#include "E_aliases.h"


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
} E_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   E_Read(void);
void    E_Write(uint8 value);
uint8   E_ReadDataReg(void);
#if defined(E__PC) || (CY_PSOC4_4200L) 
    void    E_SetDriveMode(uint8 mode);
#endif
void    E_SetInterruptMode(uint16 position, uint16 mode);
uint8   E_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void E_Sleep(void); 
void E_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(E__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define E_DRIVE_MODE_BITS        (3)
    #define E_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - E_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the E_SetDriveMode() function.
         *  @{
         */
        #define E_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define E_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define E_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define E_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define E_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define E_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define E_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define E_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define E_MASK               E__MASK
#define E_SHIFT              E__SHIFT
#define E_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in E_SetInterruptMode() function.
     *  @{
     */
        #define E_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define E_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define E_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define E_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(E__SIO)
    #define E_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(E__PC) && (CY_PSOC4_4200L)
    #define E_USBIO_ENABLE               ((uint32)0x80000000u)
    #define E_USBIO_DISABLE              ((uint32)(~E_USBIO_ENABLE))
    #define E_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define E_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define E_USBIO_ENTER_SLEEP          ((uint32)((1u << E_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << E_USBIO_SUSPEND_DEL_SHIFT)))
    #define E_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << E_USBIO_SUSPEND_SHIFT)))
    #define E_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << E_USBIO_SUSPEND_DEL_SHIFT)))
    #define E_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(E__PC)
    /* Port Configuration */
    #define E_PC                 (* (reg32 *) E__PC)
#endif
/* Pin State */
#define E_PS                     (* (reg32 *) E__PS)
/* Data Register */
#define E_DR                     (* (reg32 *) E__DR)
/* Input Buffer Disable Override */
#define E_INP_DIS                (* (reg32 *) E__PC2)

/* Interrupt configuration Registers */
#define E_INTCFG                 (* (reg32 *) E__INTCFG)
#define E_INTSTAT                (* (reg32 *) E__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define E_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(E__SIO)
    #define E_SIO_REG            (* (reg32 *) E__SIO)
#endif /* (E__SIO_CFG) */

/* USBIO registers */
#if !defined(E__PC) && (CY_PSOC4_4200L)
    #define E_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define E_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define E_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define E_DRIVE_MODE_SHIFT       (0x00u)
#define E_DRIVE_MODE_MASK        (0x07u << E_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins E_H */


/* [] END OF FILE */
