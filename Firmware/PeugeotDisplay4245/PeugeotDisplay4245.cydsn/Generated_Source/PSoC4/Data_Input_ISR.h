/*******************************************************************************
* File Name: Data_Input_ISR.h
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
#if !defined(CY_ISR_Data_Input_ISR_H)
#define CY_ISR_Data_Input_ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Data_Input_ISR_Start(void);
void Data_Input_ISR_StartEx(cyisraddress address);
void Data_Input_ISR_Stop(void);

CY_ISR_PROTO(Data_Input_ISR_Interrupt);

void Data_Input_ISR_SetVector(cyisraddress address);
cyisraddress Data_Input_ISR_GetVector(void);

void Data_Input_ISR_SetPriority(uint8 priority);
uint8 Data_Input_ISR_GetPriority(void);

void Data_Input_ISR_Enable(void);
uint8 Data_Input_ISR_GetState(void);
void Data_Input_ISR_Disable(void);

void Data_Input_ISR_SetPending(void);
void Data_Input_ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Data_Input_ISR ISR. */
#define Data_Input_ISR_INTC_VECTOR            ((reg32 *) Data_Input_ISR__INTC_VECT)

/* Address of the Data_Input_ISR ISR priority. */
#define Data_Input_ISR_INTC_PRIOR             ((reg32 *) Data_Input_ISR__INTC_PRIOR_REG)

/* Priority of the Data_Input_ISR interrupt. */
#define Data_Input_ISR_INTC_PRIOR_NUMBER      Data_Input_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Data_Input_ISR interrupt. */
#define Data_Input_ISR_INTC_SET_EN            ((reg32 *) Data_Input_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Data_Input_ISR interrupt. */
#define Data_Input_ISR_INTC_CLR_EN            ((reg32 *) Data_Input_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Data_Input_ISR interrupt state to pending. */
#define Data_Input_ISR_INTC_SET_PD            ((reg32 *) Data_Input_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Data_Input_ISR interrupt. */
#define Data_Input_ISR_INTC_CLR_PD            ((reg32 *) Data_Input_ISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_Data_Input_ISR_H */


/* [] END OF FILE */
