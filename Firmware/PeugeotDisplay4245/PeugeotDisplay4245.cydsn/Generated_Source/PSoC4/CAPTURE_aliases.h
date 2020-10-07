/*******************************************************************************
* File Name: CAPTURE.h  
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

#if !defined(CY_PINS_CAPTURE_ALIASES_H) /* Pins CAPTURE_ALIASES_H */
#define CY_PINS_CAPTURE_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CAPTURE_0			(CAPTURE__0__PC)
#define CAPTURE_0_PS		(CAPTURE__0__PS)
#define CAPTURE_0_PC		(CAPTURE__0__PC)
#define CAPTURE_0_DR		(CAPTURE__0__DR)
#define CAPTURE_0_SHIFT	(CAPTURE__0__SHIFT)
#define CAPTURE_0_INTR	((uint16)((uint16)0x0003u << (CAPTURE__0__SHIFT*2u)))

#define CAPTURE_INTR_ALL	 ((uint16)(CAPTURE_0_INTR))


#endif /* End Pins CAPTURE_ALIASES_H */


/* [] END OF FILE */
