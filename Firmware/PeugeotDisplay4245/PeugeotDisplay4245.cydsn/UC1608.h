/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef UC1608_H
#define UC1608_H
    
#include "project.h"
    
extern uint8 contrast_value;

void UC1608_Write_Command(uint8 command);
void UC1608_Write_data(uint8 data);  
    
void LCD_Init();    
void LCD_Clear();
void LCD_SetPageAddress(uint8 page);
void LCD_SetColumnAddress(uint8 column);
void LCD_SetContrast(uint8 contrast_value);
void LCD_DisplayNormal();
void LCD_DisplayReverse();
    
#endif /* UC1608_H */   

/* [] END OF FILE */
