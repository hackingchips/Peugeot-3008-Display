/*******************************************************************************
* File Name: D7.h  
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

#if !defined(CY_PINS_D7_H) /* Pins D7_H */
#define CY_PINS_D7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "D7_aliases.h"


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
} D7_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   D7_Read(void);
void    D7_Write(uint8 value);
uint8   D7_ReadDataReg(void);
#if defined(D7__PC) || (CY_PSOC4_4200L) 
    void    D7_SetDriveMode(uint8 mode);
#endif
void    D7_SetInterruptMode(uint16 position, uint16 mode);
uint8   D7_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void D7_Sleep(void); 
void D7_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(D7__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define D7_DRIVE_MODE_BITS        (3)
    #define D7_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - D7_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the D7_SetDriveMode() function.
         *  @{
         */
        #define D7_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define D7_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define D7_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define D7_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define D7_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define D7_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define D7_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define D7_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define D7_MASK               D7__MASK
#define D7_SHIFT              D7__SHIFT
#define D7_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in D7_SetInterruptMode() function.
     *  @{
     */
        #define D7_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define D7_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define D7_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define D7_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(D7__SIO)
    #define D7_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(D7__PC) && (CY_PSOC4_4200L)
    #define D7_USBIO_ENABLE               ((uint32)0x80000000u)
    #define D7_USBIO_DISABLE              ((uint32)(~D7_USBIO_ENABLE))
    #define D7_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define D7_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define D7_USBIO_ENTER_SLEEP          ((uint32)((1u << D7_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << D7_USBIO_SUSPEND_DEL_SHIFT)))
    #define D7_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << D7_USBIO_SUSPEND_SHIFT)))
    #define D7_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << D7_USBIO_SUSPEND_DEL_SHIFT)))
    #define D7_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(D7__PC)
    /* Port Configuration */
    #define D7_PC                 (* (reg32 *) D7__PC)
#endif
/* Pin State */
#define D7_PS                     (* (reg32 *) D7__PS)
/* Data Register */
#define D7_DR                     (* (reg32 *) D7__DR)
/* Input Buffer Disable Override */
#define D7_INP_DIS                (* (reg32 *) D7__PC2)

/* Interrupt configuration Registers */
#define D7_INTCFG                 (* (reg32 *) D7__INTCFG)
#define D7_INTSTAT                (* (reg32 *) D7__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define D7_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(D7__SIO)
    #define D7_SIO_REG            (* (reg32 *) D7__SIO)
#endif /* (D7__SIO_CFG) */

/* USBIO registers */
#if !defined(D7__PC) && (CY_PSOC4_4200L)
    #define D7_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define D7_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define D7_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define D7_DRIVE_MODE_SHIFT       (0x00u)
#define D7_DRIVE_MODE_MASK        (0x07u << D7_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins D7_H */


/* [] END OF FILE */
