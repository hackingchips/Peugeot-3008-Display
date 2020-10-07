/*******************************************************************************
* File Name: CS.h  
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

#if !defined(CY_PINS_CS_H) /* Pins CS_H */
#define CY_PINS_CS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CS_aliases.h"


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
} CS_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CS_Read(void);
void    CS_Write(uint8 value);
uint8   CS_ReadDataReg(void);
#if defined(CS__PC) || (CY_PSOC4_4200L) 
    void    CS_SetDriveMode(uint8 mode);
#endif
void    CS_SetInterruptMode(uint16 position, uint16 mode);
uint8   CS_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CS_Sleep(void); 
void CS_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CS__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CS_DRIVE_MODE_BITS        (3)
    #define CS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CS_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CS_SetDriveMode() function.
         *  @{
         */
        #define CS_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CS_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CS_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CS_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CS_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CS_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CS_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CS_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CS_MASK               CS__MASK
#define CS_SHIFT              CS__SHIFT
#define CS_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CS_SetInterruptMode() function.
     *  @{
     */
        #define CS_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CS_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CS_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CS_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CS__SIO)
    #define CS_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CS__PC) && (CY_PSOC4_4200L)
    #define CS_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CS_USBIO_DISABLE              ((uint32)(~CS_USBIO_ENABLE))
    #define CS_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CS_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CS_USBIO_ENTER_SLEEP          ((uint32)((1u << CS_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CS_USBIO_SUSPEND_DEL_SHIFT)))
    #define CS_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CS_USBIO_SUSPEND_SHIFT)))
    #define CS_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CS_USBIO_SUSPEND_DEL_SHIFT)))
    #define CS_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CS__PC)
    /* Port Configuration */
    #define CS_PC                 (* (reg32 *) CS__PC)
#endif
/* Pin State */
#define CS_PS                     (* (reg32 *) CS__PS)
/* Data Register */
#define CS_DR                     (* (reg32 *) CS__DR)
/* Input Buffer Disable Override */
#define CS_INP_DIS                (* (reg32 *) CS__PC2)

/* Interrupt configuration Registers */
#define CS_INTCFG                 (* (reg32 *) CS__INTCFG)
#define CS_INTSTAT                (* (reg32 *) CS__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CS_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CS__SIO)
    #define CS_SIO_REG            (* (reg32 *) CS__SIO)
#endif /* (CS__SIO_CFG) */

/* USBIO registers */
#if !defined(CS__PC) && (CY_PSOC4_4200L)
    #define CS_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CS_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CS_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CS_DRIVE_MODE_SHIFT       (0x00u)
#define CS_DRIVE_MODE_MASK        (0x07u << CS_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CS_H */


/* [] END OF FILE */
