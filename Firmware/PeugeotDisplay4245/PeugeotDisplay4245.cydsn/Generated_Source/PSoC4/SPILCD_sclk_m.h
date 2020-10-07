/*******************************************************************************
* File Name: SPILCD_sclk_m.h  
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

#if !defined(CY_PINS_SPILCD_sclk_m_H) /* Pins SPILCD_sclk_m_H */
#define CY_PINS_SPILCD_sclk_m_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SPILCD_sclk_m_aliases.h"


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
} SPILCD_sclk_m_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SPILCD_sclk_m_Read(void);
void    SPILCD_sclk_m_Write(uint8 value);
uint8   SPILCD_sclk_m_ReadDataReg(void);
#if defined(SPILCD_sclk_m__PC) || (CY_PSOC4_4200L) 
    void    SPILCD_sclk_m_SetDriveMode(uint8 mode);
#endif
void    SPILCD_sclk_m_SetInterruptMode(uint16 position, uint16 mode);
uint8   SPILCD_sclk_m_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SPILCD_sclk_m_Sleep(void); 
void SPILCD_sclk_m_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SPILCD_sclk_m__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SPILCD_sclk_m_DRIVE_MODE_BITS        (3)
    #define SPILCD_sclk_m_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SPILCD_sclk_m_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SPILCD_sclk_m_SetDriveMode() function.
         *  @{
         */
        #define SPILCD_sclk_m_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SPILCD_sclk_m_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SPILCD_sclk_m_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SPILCD_sclk_m_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SPILCD_sclk_m_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SPILCD_sclk_m_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SPILCD_sclk_m_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SPILCD_sclk_m_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SPILCD_sclk_m_MASK               SPILCD_sclk_m__MASK
#define SPILCD_sclk_m_SHIFT              SPILCD_sclk_m__SHIFT
#define SPILCD_sclk_m_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SPILCD_sclk_m_SetInterruptMode() function.
     *  @{
     */
        #define SPILCD_sclk_m_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SPILCD_sclk_m_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SPILCD_sclk_m_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SPILCD_sclk_m_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SPILCD_sclk_m__SIO)
    #define SPILCD_sclk_m_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SPILCD_sclk_m__PC) && (CY_PSOC4_4200L)
    #define SPILCD_sclk_m_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SPILCD_sclk_m_USBIO_DISABLE              ((uint32)(~SPILCD_sclk_m_USBIO_ENABLE))
    #define SPILCD_sclk_m_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SPILCD_sclk_m_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SPILCD_sclk_m_USBIO_ENTER_SLEEP          ((uint32)((1u << SPILCD_sclk_m_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SPILCD_sclk_m_USBIO_SUSPEND_DEL_SHIFT)))
    #define SPILCD_sclk_m_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SPILCD_sclk_m_USBIO_SUSPEND_SHIFT)))
    #define SPILCD_sclk_m_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SPILCD_sclk_m_USBIO_SUSPEND_DEL_SHIFT)))
    #define SPILCD_sclk_m_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SPILCD_sclk_m__PC)
    /* Port Configuration */
    #define SPILCD_sclk_m_PC                 (* (reg32 *) SPILCD_sclk_m__PC)
#endif
/* Pin State */
#define SPILCD_sclk_m_PS                     (* (reg32 *) SPILCD_sclk_m__PS)
/* Data Register */
#define SPILCD_sclk_m_DR                     (* (reg32 *) SPILCD_sclk_m__DR)
/* Input Buffer Disable Override */
#define SPILCD_sclk_m_INP_DIS                (* (reg32 *) SPILCD_sclk_m__PC2)

/* Interrupt configuration Registers */
#define SPILCD_sclk_m_INTCFG                 (* (reg32 *) SPILCD_sclk_m__INTCFG)
#define SPILCD_sclk_m_INTSTAT                (* (reg32 *) SPILCD_sclk_m__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SPILCD_sclk_m_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SPILCD_sclk_m__SIO)
    #define SPILCD_sclk_m_SIO_REG            (* (reg32 *) SPILCD_sclk_m__SIO)
#endif /* (SPILCD_sclk_m__SIO_CFG) */

/* USBIO registers */
#if !defined(SPILCD_sclk_m__PC) && (CY_PSOC4_4200L)
    #define SPILCD_sclk_m_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SPILCD_sclk_m_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SPILCD_sclk_m_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SPILCD_sclk_m_DRIVE_MODE_SHIFT       (0x00u)
#define SPILCD_sclk_m_DRIVE_MODE_MASK        (0x07u << SPILCD_sclk_m_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SPILCD_sclk_m_H */


/* [] END OF FILE */
