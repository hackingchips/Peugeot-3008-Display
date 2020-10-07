/*******************************************************************************
* File Name: D0.h  
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

#if !defined(CY_PINS_D0_ALIASES_H) /* Pins D0_ALIASES_H */
#define CY_PINS_D0_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define D0_0			(D0__0__PC)
#define D0_0_PS		(D0__0__PS)
#define D0_0_PC		(D0__0__PC)
#define D0_0_DR		(D0__0__DR)
#define D0_0_SHIFT	(D0__0__SHIFT)
#define D0_0_INTR	((uint16)((uint16)0x0003u << (D0__0__SHIFT*2u)))

#define D0_INTR_ALL	 ((uint16)(D0_0_INTR))


#endif /* End Pins D0_ALIASES_H */


/* [] END OF FILE */
