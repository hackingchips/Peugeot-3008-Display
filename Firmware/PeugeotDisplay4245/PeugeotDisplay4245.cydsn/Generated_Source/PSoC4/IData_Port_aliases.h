/*******************************************************************************
* File Name: IData_Port.h  
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

#if !defined(CY_PINS_IData_Port_ALIASES_H) /* Pins IData_Port_ALIASES_H */
#define CY_PINS_IData_Port_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define IData_Port_0			(IData_Port__0__PC)
#define IData_Port_0_PS		(IData_Port__0__PS)
#define IData_Port_0_PC		(IData_Port__0__PC)
#define IData_Port_0_DR		(IData_Port__0__DR)
#define IData_Port_0_SHIFT	(IData_Port__0__SHIFT)
#define IData_Port_0_INTR	((uint16)((uint16)0x0003u << (IData_Port__0__SHIFT*2u)))

#define IData_Port_1			(IData_Port__1__PC)
#define IData_Port_1_PS		(IData_Port__1__PS)
#define IData_Port_1_PC		(IData_Port__1__PC)
#define IData_Port_1_DR		(IData_Port__1__DR)
#define IData_Port_1_SHIFT	(IData_Port__1__SHIFT)
#define IData_Port_1_INTR	((uint16)((uint16)0x0003u << (IData_Port__1__SHIFT*2u)))

#define IData_Port_2			(IData_Port__2__PC)
#define IData_Port_2_PS		(IData_Port__2__PS)
#define IData_Port_2_PC		(IData_Port__2__PC)
#define IData_Port_2_DR		(IData_Port__2__DR)
#define IData_Port_2_SHIFT	(IData_Port__2__SHIFT)
#define IData_Port_2_INTR	((uint16)((uint16)0x0003u << (IData_Port__2__SHIFT*2u)))

#define IData_Port_3			(IData_Port__3__PC)
#define IData_Port_3_PS		(IData_Port__3__PS)
#define IData_Port_3_PC		(IData_Port__3__PC)
#define IData_Port_3_DR		(IData_Port__3__DR)
#define IData_Port_3_SHIFT	(IData_Port__3__SHIFT)
#define IData_Port_3_INTR	((uint16)((uint16)0x0003u << (IData_Port__3__SHIFT*2u)))

#define IData_Port_4			(IData_Port__4__PC)
#define IData_Port_4_PS		(IData_Port__4__PS)
#define IData_Port_4_PC		(IData_Port__4__PC)
#define IData_Port_4_DR		(IData_Port__4__DR)
#define IData_Port_4_SHIFT	(IData_Port__4__SHIFT)
#define IData_Port_4_INTR	((uint16)((uint16)0x0003u << (IData_Port__4__SHIFT*2u)))

#define IData_Port_5			(IData_Port__5__PC)
#define IData_Port_5_PS		(IData_Port__5__PS)
#define IData_Port_5_PC		(IData_Port__5__PC)
#define IData_Port_5_DR		(IData_Port__5__DR)
#define IData_Port_5_SHIFT	(IData_Port__5__SHIFT)
#define IData_Port_5_INTR	((uint16)((uint16)0x0003u << (IData_Port__5__SHIFT*2u)))

#define IData_Port_6			(IData_Port__6__PC)
#define IData_Port_6_PS		(IData_Port__6__PS)
#define IData_Port_6_PC		(IData_Port__6__PC)
#define IData_Port_6_DR		(IData_Port__6__DR)
#define IData_Port_6_SHIFT	(IData_Port__6__SHIFT)
#define IData_Port_6_INTR	((uint16)((uint16)0x0003u << (IData_Port__6__SHIFT*2u)))

#define IData_Port_7			(IData_Port__7__PC)
#define IData_Port_7_PS		(IData_Port__7__PS)
#define IData_Port_7_PC		(IData_Port__7__PC)
#define IData_Port_7_DR		(IData_Port__7__DR)
#define IData_Port_7_SHIFT	(IData_Port__7__SHIFT)
#define IData_Port_7_INTR	((uint16)((uint16)0x0003u << (IData_Port__7__SHIFT*2u)))

#define IData_Port_INTR_ALL	 ((uint16)(IData_Port_0_INTR| IData_Port_1_INTR| IData_Port_2_INTR| IData_Port_3_INTR| IData_Port_4_INTR| IData_Port_5_INTR| IData_Port_6_INTR| IData_Port_7_INTR))


#endif /* End Pins IData_Port_ALIASES_H */


/* [] END OF FILE */
