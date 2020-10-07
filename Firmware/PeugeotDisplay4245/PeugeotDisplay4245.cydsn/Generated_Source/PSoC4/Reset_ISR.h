/*******************************************************************************
* File Name: Reset_ISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Reset_ISR_H)
#define CY_ISR_Reset_ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Reset_ISR_Start(void);
void Reset_ISR_StartEx(cyisraddress address);
void Reset_ISR_Stop(void);

CY_ISR_PROTO(Reset_ISR_Interrupt);

void Reset_ISR_SetVector(cyisraddress address);
cyisraddress Reset_ISR_GetVector(void);

void Reset_ISR_SetPriority(uint8 priority);
uint8 Reset_ISR_GetPriority(void);

void Reset_ISR_Enable(void);
uint8 Reset_ISR_GetState(void);
void Reset_ISR_Disable(void);

void Reset_ISR_SetPending(void);
void Reset_ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Reset_ISR ISR. */
#define Reset_ISR_INTC_VECTOR            ((reg32 *) Reset_ISR__INTC_VECT)

/* Address of the Reset_ISR ISR priority. */
#define Reset_ISR_INTC_PRIOR             ((reg32 *) Reset_ISR__INTC_PRIOR_REG)

/* Priority of the Reset_ISR interrupt. */
#define Reset_ISR_INTC_PRIOR_NUMBER      Reset_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Reset_ISR interrupt. */
#define Reset_ISR_INTC_SET_EN            ((reg32 *) Reset_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Reset_ISR interrupt. */
#define Reset_ISR_INTC_CLR_EN            ((reg32 *) Reset_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Reset_ISR interrupt state to pending. */
#define Reset_ISR_INTC_SET_PD            ((reg32 *) Reset_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Reset_ISR interrupt. */
#define Reset_ISR_INTC_CLR_PD            ((reg32 *) Reset_ISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_Reset_ISR_H */


/* [] END OF FILE */
