/*******************************************************************************
* File Name: SPILCD_ss0_m.h  
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

#if !defined(CY_PINS_SPILCD_ss0_m_ALIASES_H) /* Pins SPILCD_ss0_m_ALIASES_H */
#define CY_PINS_SPILCD_ss0_m_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SPILCD_ss0_m_0			(SPILCD_ss0_m__0__PC)
#define SPILCD_ss0_m_0_PS		(SPILCD_ss0_m__0__PS)
#define SPILCD_ss0_m_0_PC		(SPILCD_ss0_m__0__PC)
#define SPILCD_ss0_m_0_DR		(SPILCD_ss0_m__0__DR)
#define SPILCD_ss0_m_0_SHIFT	(SPILCD_ss0_m__0__SHIFT)
#define SPILCD_ss0_m_0_INTR	((uint16)((uint16)0x0003u << (SPILCD_ss0_m__0__SHIFT*2u)))

#define SPILCD_ss0_m_INTR_ALL	 ((uint16)(SPILCD_ss0_m_0_INTR))


#endif /* End Pins SPILCD_ss0_m_ALIASES_H */


/* [] END OF FILE */
