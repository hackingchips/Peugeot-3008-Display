/*******************************************************************************
* File Name: Capture_Data_ISR.h
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
#if !defined(CY_ISR_Capture_Data_ISR_H)
#define CY_ISR_Capture_Data_ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Capture_Data_ISR_Start(void);
void Capture_Data_ISR_StartEx(cyisraddress address);
void Capture_Data_ISR_Stop(void);

CY_ISR_PROTO(Capture_Data_ISR_Interrupt);

void Capture_Data_ISR_SetVector(cyisraddress address);
cyisraddress Capture_Data_ISR_GetVector(void);

void Capture_Data_ISR_SetPriority(uint8 priority);
uint8 Capture_Data_ISR_GetPriority(void);

void Capture_Data_ISR_Enable(void);
uint8 Capture_Data_ISR_GetState(void);
void Capture_Data_ISR_Disable(void);

void Capture_Data_ISR_SetPending(void);
void Capture_Data_ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Capture_Data_ISR ISR. */
#define Capture_Data_ISR_INTC_VECTOR            ((reg32 *) Capture_Data_ISR__INTC_VECT)

/* Address of the Capture_Data_ISR ISR priority. */
#define Capture_Data_ISR_INTC_PRIOR             ((reg32 *) Capture_Data_ISR__INTC_PRIOR_REG)

/* Priority of the Capture_Data_ISR interrupt. */
#define Capture_Data_ISR_INTC_PRIOR_NUMBER      Capture_Data_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Capture_Data_ISR interrupt. */
#define Capture_Data_ISR_INTC_SET_EN            ((reg32 *) Capture_Data_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Capture_Data_ISR interrupt. */
#define Capture_Data_ISR_INTC_CLR_EN            ((reg32 *) Capture_Data_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Capture_Data_ISR interrupt state to pending. */
#define Capture_Data_ISR_INTC_SET_PD            ((reg32 *) Capture_Data_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Capture_Data_ISR interrupt. */
#define Capture_Data_ISR_INTC_CLR_PD            ((reg32 *) Capture_Data_ISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_Capture_Data_ISR_H */


/* [] END OF FILE */
