/*******************************************************************************
* File Name: RESET.h  
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

#if !defined(CY_PINS_RESET_H) /* Pins RESET_H */
#define CY_PINS_RESET_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RESET_aliases.h"


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
} RESET_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   RESET_Read(void);
void    RESET_Write(uint8 value);
uint8   RESET_ReadDataReg(void);
#if defined(RESET__PC) || (CY_PSOC4_4200L) 
    void    RESET_SetDriveMode(uint8 mode);
#endif
void    RESET_SetInterruptMode(uint16 position, uint16 mode);
uint8   RESET_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void RESET_Sleep(void); 
void RESET_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(RESET__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define RESET_DRIVE_MODE_BITS        (3)
    #define RESET_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RESET_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the RESET_SetDriveMode() function.
         *  @{
         */
        #define RESET_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define RESET_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define RESET_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define RESET_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define RESET_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define RESET_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define RESET_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define RESET_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define RESET_MASK               RESET__MASK
#define RESET_SHIFT              RESET__SHIFT
#define RESET_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RESET_SetInterruptMode() function.
     *  @{
     */
        #define RESET_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define RESET_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define RESET_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define RESET_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(RESET__SIO)
    #define RESET_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(RESET__PC) && (CY_PSOC4_4200L)
    #define RESET_USBIO_ENABLE               ((uint32)0x80000000u)
    #define RESET_USBIO_DISABLE              ((uint32)(~RESET_USBIO_ENABLE))
    #define RESET_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define RESET_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define RESET_USBIO_ENTER_SLEEP          ((uint32)((1u << RESET_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << RESET_USBIO_SUSPEND_DEL_SHIFT)))
    #define RESET_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << RESET_USBIO_SUSPEND_SHIFT)))
    #define RESET_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << RESET_USBIO_SUSPEND_DEL_SHIFT)))
    #define RESET_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(RESET__PC)
    /* Port Configuration */
    #define RESET_PC                 (* (reg32 *) RESET__PC)
#endif
/* Pin State */
#define RESET_PS                     (* (reg32 *) RESET__PS)
/* Data Register */
#define RESET_DR                     (* (reg32 *) RESET__DR)
/* Input Buffer Disable Override */
#define RESET_INP_DIS                (* (reg32 *) RESET__PC2)

/* Interrupt configuration Registers */
#define RESET_INTCFG                 (* (reg32 *) RESET__INTCFG)
#define RESET_INTSTAT                (* (reg32 *) RESET__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define RESET_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(RESET__SIO)
    #define RESET_SIO_REG            (* (reg32 *) RESET__SIO)
#endif /* (RESET__SIO_CFG) */

/* USBIO registers */
#if !defined(RESET__PC) && (CY_PSOC4_4200L)
    #define RESET_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define RESET_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define RESET_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define RESET_DRIVE_MODE_SHIFT       (0x00u)
#define RESET_DRIVE_MODE_MASK        (0x07u << RESET_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins RESET_H */


/* [] END OF FILE */
