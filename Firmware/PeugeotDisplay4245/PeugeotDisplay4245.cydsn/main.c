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

//#define SERIAL_PORT_SEND_DATA
#define SERIAL_PORT_SEND_PROCCESSED

/* ************************************************************************* */
enum { IDLE, DATA0, DATA1, DATA2 } BUS_STATE;

volatile    uint8 bus_state = IDLE;

volatile    uint8 data_buffer[2000];
volatile    uint16 data_buffer_ptr = 0;

volatile    uint8 data_ready = 0;

volatile    uint8 enable_capture = 0;

volatile    uint8 combined_data = 0;
volatile    uint8 page_counter = 0;
volatile    uint8 column_counter = 0;
volatile    uint8 is_first_byte = 1;

volatile    uint8 display_set_normal = 0;
volatile    uint8 display_set_reverse = 0;

/* Interrupt prototypes */
CY_ISR_PROTO(ISR_Reset_Handler);
CY_ISR_PROTO(ISR_Capture);

void Uart_SendCommandString(uint8 command);

/* ************************************************************************* */


/* Manage interrupt from RESET. */
CY_ISR(ISR_Reset_Handler)
{
}

/* Manage interrupt for command capture. */
CY_ISR(ISR_Capture_Handler)
{
    uint8 a0_state = A0_Read();
    uint8 e_state = E_Read();
    
    uint8 bdata = IData_Port_Read();
    
    /* *** Waiting for command "data write". *** */
    if (bus_state == IDLE)
    {
        if ((e_state == 1) && (a0_state == 0))
        {
            if (bdata == 0b00011101)                                            // 0b00011101 = Display data write command.
            {
                page_counter = column_counter = data_buffer_ptr = 0;            // Initialize counters and buffer pointer.
                bus_state = DATA0;
            }
            
            if (bdata == 0b10100110) display_set_normal = 1;                    // Display normal.
            if (bdata == 0b10100111) display_set_reverse = 1;                   // Display reverse.
        }
    }
    /* *** First byte received is a dummy byte. We discard it. *** */
    else if (bus_state == DATA0) 
    {
        bus_state = DATA1;
    }
    /* *** Received even page byte. *** */
    else if (bus_state == DATA1)
    {

        if ((e_state == 0) && (a0_state == 1))
        {
            if ((page_counter < 16) && (column_counter < 240))                  // Data outside display is discarded.
            {
                combined_data = (bdata & 0b00000001) |                          // Isolate every low bit of every pixel and move them to the 
                                ((bdata & 0b00000100) >> 1) |                   // lower nibble of the final data byte.
                                ((bdata & 0b00010000) >> 2) |
                                ((bdata & 0b01000000) >> 3);
                                
                bus_state = DATA2;
            }
                            
            page_counter++;
            if (page_counter == 21) 
            {
                page_counter = 0; 
                column_counter++;
            }
        }
        else if ( e_state == 1 )
        {
            data_ready = 1;
            bus_state = IDLE;
            CyGlobalIntDisable;
        }

    }
    /* *** Received odd page byte. *** */
    else if (bus_state == DATA2)
    {
        if ((e_state == 0) && (a0_state == 1))
        {
            if ((page_counter < 16) && (column_counter < 240))                  // Data outside display is discarded.
            {
                combined_data = combined_data | ((bdata & 0b00000001) << 4) |   // Isolate every low bit of every pixel and move them to the
                                                ((bdata & 0b00000100) << 3) |   // higher nibble of the final data byte.
                                                ((bdata & 0b00010000) << 2) |   // Combine it with the previous lower nibble.
                                                ((bdata & 0b01000000) << 1);
                                                
                bus_state = DATA1;
                                                
                data_buffer[data_buffer_ptr] = combined_data;
                data_buffer_ptr++;
            }
                                            
            page_counter++;
            if (page_counter == 21) 
            {
                page_counter = 0; 
                column_counter++;
            }                                             
        }
        else if ( e_state == 1 )                                                
        {
            data_ready = 1;                                                     // All data has been received, converted to 1 byte 
            bus_state = IDLE;                                                   // monocrome and stored in buffer.
            CyGlobalIntDisable;                                                 // Set data_ready flag and disable interrupts.
        }
    }    
}

/* ************************************************************************* */

int main(void)
{
    uint8 page, column;
    
    /* Configure and enable interrupts. */
    ISR_Reset_StartEx(ISR_Reset_Handler);
    ISR_Capture_StartEx(ISR_Capture_Handler);
    //CyGlobalIntEnable;
    
    /* Init SPILCD. */
    SPILCD_Start();
    
    /* Initialize the display. */
    LCD_Init();
    LCD_Clear();     
          
    LCD_SetPageAddress(0);
    LCD_SetColumnAddress(0);    
    
    enable_capture = 1;
    CyGlobalIntEnable;    

    for(;;)
    {
  
        /* --------------------------------------------- */
        
        if (data_ready == 1)
        {
            LCD_SetPageAddress(0);
            LCD_SetColumnAddress(0);
        
            for (page = 0; page < 8; page++)
            {    
                for (column = 0; column < 240; column++)
                {
                
                    UC1608_Write_data(data_buffer[(column * 8) + page]);
                }
            }            
            
            if (enable_capture) CyGlobalIntEnable;
        }
        
        if (display_set_normal)
        {
            LCD_DisplayNormal();
            display_set_normal = 0;
        }
        
        if (display_set_reverse)
        {
            LCD_DisplayReverse();
            display_set_reverse = 0;
        }
    
        
    }
}

/* [] END OF FILE */
