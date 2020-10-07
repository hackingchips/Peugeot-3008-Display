/*******************************************************************************
* File Name: D6.h  
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

#if !defined(CY_PINS_D6_H) /* Pins D6_H */
#define CY_PINS_D6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "D6_aliases.h"


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
} D6_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   D6_Read(void);
void    D6_Write(uint8 value);
uint8   D6_ReadDataReg(void);
#if defined(D6__PC) || (CY_PSOC4_4200L) 
    void    D6_SetDriveMode(uint8 mode);
#endif
void    D6_SetInterruptMode(uint16 position, uint16 mode);
uint8   D6_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void D6_Sleep(void); 
void D6_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(D6__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define D6_DRIVE_MODE_BITS        (3)
    #define D6_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - D6_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the D6_SetDriveMode() function.
         *  @{
         */
        #define D6_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define D6_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define D6_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define D6_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define D6_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define D6_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define D6_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define D6_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define D6_MASK               D6__MASK
#define D6_SHIFT              D6__SHIFT
#define D6_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in D6_SetInterruptMode() function.
     *  @{
     */
        #define D6_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define D6_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define D6_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define D6_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(D6__SIO)
    #define D6_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(D6__PC) && (CY_PSOC4_4200L)
    #define D6_USBIO_ENABLE               ((uint32)0x80000000u)
    #define D6_USBIO_DISABLE              ((uint32)(~D6_USBIO_ENABLE))
    #define D6_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define D6_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define D6_USBIO_ENTER_SLEEP          ((uint32)((1u << D6_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << D6_USBIO_SUSPEND_DEL_SHIFT)))
    #define D6_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << D6_USBIO_SUSPEND_SHIFT)))
    #define D6_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << D6_USBIO_SUSPEND_DEL_SHIFT)))
    #define D6_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(D6__PC)
    /* Port Configuration */
    #define D6_PC                 (* (reg32 *) D6__PC)
#endif
/* Pin State */
#define D6_PS                     (* (reg32 *) D6__PS)
/* Data Register */
#define D6_DR                     (* (reg32 *) D6__DR)
/* Input Buffer Disable Override */
#define D6_INP_DIS                (* (reg32 *) D6__PC2)

/* Interrupt configuration Registers */
#define D6_INTCFG                 (* (reg32 *) D6__INTCFG)
#define D6_INTSTAT                (* (reg32 *) D6__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define D6_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(D6__SIO)
    #define D6_SIO_REG            (* (reg32 *) D6__SIO)
#endif /* (D6__SIO_CFG) */

/* USBIO registers */
#if !defined(D6__PC) && (CY_PSOC4_4200L)
    #define D6_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define D6_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define D6_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define D6_DRIVE_MODE_SHIFT       (0x00u)
#define D6_DRIVE_MODE_MASK        (0x07u << D6_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins D6_H */


/* [] END OF FILE */
