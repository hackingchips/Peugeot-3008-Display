/*******************************************************************************
* File Name: LCD_RESET.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LCD_RESET_ALIASES_H) /* Pins LCD_RESET_ALIASES_H */
#define CY_PINS_LCD_RESET_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LCD_RESET_0			(LCD_RESET__0__PC)
#define LCD_RESET_0_PS		(LCD_RESET__0__PS)
#define LCD_RESET_0_PC		(LCD_RESET__0__PC)
#define LCD_RESET_0_DR		(LCD_RESET__0__DR)
#define LCD_RESET_0_SHIFT	(LCD_RESET__0__SHIFT)
#define LCD_RESET_0_INTR	((uint16)((uint16)0x0003u << (LCD_RESET__0__SHIFT*2u)))

#define LCD_RESET_INTR_ALL	 ((uint16)(LCD_RESET_0_INTR))


#endif /* End Pins LCD_RESET_ALIASES_H */


/* [] END OF FILE */
