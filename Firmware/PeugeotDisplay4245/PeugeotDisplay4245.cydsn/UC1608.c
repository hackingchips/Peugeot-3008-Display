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

#include "project.h"
#include "UC1608.h"

void UC1608_Write_Command(uint8 command); 
void UC1608_Write_Data(uint8 data);

uint8 contrast_value = 11;

void UC1608_Write_Command(uint8 command)
{
    /* When CD line = 0 data sent is command. */
    LCD_CD_Write(0); 
    SPILCD_SpiUartWriteTxData(command);
}

void UC1608_Write_data(uint8 data)
{
    /* When CD line = 1 data sent is display data. */
    LCD_CD_Write(1);
    SPILCD_SpiUartWriteTxData(data);
}

void LCD_Init()
{
    /* Hardware reset. */
    LCD_RESET_Write(0);
    CyDelay(5);
    LCD_RESET_Write(1);
    CyDelay(5);
    
    /* Software reset. */
    UC1608_Write_Command(0xE2);
    CyDelay(30);
    
    /* Configure display. */
    UC1608_Write_Command(0x23);                     // Mux. ratio :96, Temperature compensation = -0,20%/C
   	UC1608_Write_Command(0xC8);                     // Set LCD mapping control. MX=0, MY=1
	UC1608_Write_Command(0xE8);                     // LCD bias ratio = 1/10.7
	UC1608_Write_Command(0x81);                     // Set Gain and Potentiometer
    UC1608_Write_Command(0x00 | contrast_value);     
	UC1608_Write_Command(0x2F);                     // Use internal charge pump. Internal VLCD.	
	UC1608_Write_Command(0x40);                     // Start line = 0.
	UC1608_Write_Command(0xA4);                     // All pixels OFF.
//	Write_Instruction(0xA5);                        //--set  all pixel on
	UC1608_Write_Command(0xA6);                     //--set normal display
//    UC1608_Write_Command(0xA7);                        //--set inverse display
	UC1608_Write_Command(0x89);                     // Set RAM Address control
//  Write_Instruction(0x90);                        //set fixed lines 1001xxxx
    UC1608_Write_Command(0xB0);                     // Page address = 0.
    UC1608_Write_Command(0x00);                     // Column address = 0.
    UC1608_Write_Command(0x10);                     
    UC1608_Write_Command(0xAF);                     // Enable the display.
}

void LCD_Clear()
{
    uint8 page, column;
    
    for (page = 0; page < 8; page++)
    {
        LCD_SetPageAddress(page);
        LCD_SetColumnAddress(0);
        
        for (column = 0; column < 240; column++)
        {
            UC1608_Write_data(0x80);
        }
    }
}

void LCD_SetPageAddress(uint8 page)
{
    UC1608_Write_Command(0xB0 | page);
	
    return;
}

//**********************************************************
//  Set Column Address
//**********************************************************
void LCD_SetColumnAddress(uint8 column)
{
    UC1608_Write_Command((0x10 |(column >> 4)));
	UC1608_Write_Command((0x0F & column));
	return;
}




//**********************************************************
//  Set Contrast Control Register
//**********************************************************
void LCD_SetContrast(uint8 contrast_value)
{
    UC1608_Write_Command(0x81);
	UC1608_Write_Command(0x00 | contrast_value);
	return;
}

void LCD_DisplayNormal()
{
    UC1608_Write_Command(0xA7);
}

void LCD_DisplayReverse()
{
    UC1608_Write_Command(0xA6);
}

/* [] END OF FILE */
