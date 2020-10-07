/*******************************************************************************
* File Name: CAPTURE.h  
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

#if !defined(CY_PINS_CAPTURE_H) /* Pins CAPTURE_H */
#define CY_PINS_CAPTURE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CAPTURE_aliases.h"


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
} CAPTURE_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CAPTURE_Read(void);
void    CAPTURE_Write(uint8 value);
uint8   CAPTURE_ReadDataReg(void);
#if defined(CAPTURE__PC) || (CY_PSOC4_4200L) 
    void    CAPTURE_SetDriveMode(uint8 mode);
#endif
void    CAPTURE_SetInterruptMode(uint16 position, uint16 mode);
uint8   CAPTURE_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CAPTURE_Sleep(void); 
void CAPTURE_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CAPTURE__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CAPTURE_DRIVE_MODE_BITS        (3)
    #define CAPTURE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CAPTURE_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CAPTURE_SetDriveMode() function.
         *  @{
         */
        #define CAPTURE_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CAPTURE_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CAPTURE_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CAPTURE_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CAPTURE_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CAPTURE_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CAPTURE_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CAPTURE_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CAPTURE_MASK               CAPTURE__MASK
#define CAPTURE_SHIFT              CAPTURE__SHIFT
#define CAPTURE_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CAPTURE_SetInterruptMode() function.
     *  @{
     */
        #define CAPTURE_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CAPTURE_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CAPTURE_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CAPTURE_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CAPTURE__SIO)
    #define CAPTURE_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CAPTURE__PC) && (CY_PSOC4_4200L)
    #define CAPTURE_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CAPTURE_USBIO_DISABLE              ((uint32)(~CAPTURE_USBIO_ENABLE))
    #define CAPTURE_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CAPTURE_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CAPTURE_USBIO_ENTER_SLEEP          ((uint32)((1u << CAPTURE_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CAPTURE_USBIO_SUSPEND_DEL_SHIFT)))
    #define CAPTURE_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CAPTURE_USBIO_SUSPEND_SHIFT)))
    #define CAPTURE_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CAPTURE_USBIO_SUSPEND_DEL_SHIFT)))
    #define CAPTURE_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CAPTURE__PC)
    /* Port Configuration */
    #define CAPTURE_PC                 (* (reg32 *) CAPTURE__PC)
#endif
/* Pin State */
#define CAPTURE_PS                     (* (reg32 *) CAPTURE__PS)
/* Data Register */
#define CAPTURE_DR                     (* (reg32 *) CAPTURE__DR)
/* Input Buffer Disable Override */
#define CAPTURE_INP_DIS                (* (reg32 *) CAPTURE__PC2)

/* Interrupt configuration Registers */
#define CAPTURE_INTCFG                 (* (reg32 *) CAPTURE__INTCFG)
#define CAPTURE_INTSTAT                (* (reg32 *) CAPTURE__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CAPTURE_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CAPTURE__SIO)
    #define CAPTURE_SIO_REG            (* (reg32 *) CAPTURE__SIO)
#endif /* (CAPTURE__SIO_CFG) */

/* USBIO registers */
#if !defined(CAPTURE__PC) && (CY_PSOC4_4200L)
    #define CAPTURE_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CAPTURE_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CAPTURE_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CAPTURE_DRIVE_MODE_SHIFT       (0x00u)
#define CAPTURE_DRIVE_MODE_MASK        (0x07u << CAPTURE_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CAPTURE_H */


/* [] END OF FILE */
