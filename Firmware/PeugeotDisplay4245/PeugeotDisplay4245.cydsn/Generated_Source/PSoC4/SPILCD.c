/***************************************************************************//**
* \file SPILCD.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPILCD_PVT.h"

#if (SPILCD_SCB_MODE_I2C_INC)
    #include "SPILCD_I2C_PVT.h"
#endif /* (SPILCD_SCB_MODE_I2C_INC) */

#if (SPILCD_SCB_MODE_EZI2C_INC)
    #include "SPILCD_EZI2C_PVT.h"
#endif /* (SPILCD_SCB_MODE_EZI2C_INC) */

#if (SPILCD_SCB_MODE_SPI_INC || SPILCD_SCB_MODE_UART_INC)
    #include "SPILCD_SPI_UART_PVT.h"
#endif /* (SPILCD_SCB_MODE_SPI_INC || SPILCD_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 SPILCD_scbMode = SPILCD_SCB_MODE_UNCONFIG;
    uint8 SPILCD_scbEnableWake;
    uint8 SPILCD_scbEnableIntr;

    /* I2C configuration variables */
    uint8 SPILCD_mode;
    uint8 SPILCD_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * SPILCD_rxBuffer;
    uint8  SPILCD_rxDataBits;
    uint32 SPILCD_rxBufferSize;

    volatile uint8 * SPILCD_txBuffer;
    uint8  SPILCD_txDataBits;
    uint32 SPILCD_txBufferSize;

    /* EZI2C configuration variables */
    uint8 SPILCD_numberOfAddr;
    uint8 SPILCD_subAddrSize;
#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** SPILCD_initVar indicates whether the SPILCD 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the SPILCD_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  SPILCD_Init() function can be called before the 
*  SPILCD_Start() or SPILCD_Enable() function.
*/
uint8 SPILCD_initVar = 0u;


#if (! (SPILCD_SCB_MODE_I2C_CONST_CFG || \
        SPILCD_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * SPILCD_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent SPILCD_Enable() call.
    */
    uint16 SPILCD_IntrTxMask = 0u;
#endif /* (! (SPILCD_SCB_MODE_I2C_CONST_CFG || \
              SPILCD_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (SPILCD_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SPILCD_CUSTOM_INTR_HANDLER)
    void (*SPILCD_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_SPILCD_CUSTOM_INTR_HANDLER) */
#endif /* (SPILCD_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void SPILCD_ScbEnableIntr(void);
static void SPILCD_ScbModeStop(void);
static void SPILCD_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: SPILCD_Init
****************************************************************************//**
*
*  Initializes the SPILCD component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SPILCD_I2CInit, SPILCD_SpiInit, 
*  SPILCD_UartInit or SPILCD_EzI2CInit.
*
*******************************************************************************/
void SPILCD_Init(void)
{
#if (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SPILCD_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SPILCD_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (SPILCD_SCB_MODE_I2C_CONST_CFG)
    SPILCD_I2CInit();

#elif (SPILCD_SCB_MODE_SPI_CONST_CFG)
    SPILCD_SpiInit();

#elif (SPILCD_SCB_MODE_UART_CONST_CFG)
    SPILCD_UartInit();

#elif (SPILCD_SCB_MODE_EZI2C_CONST_CFG)
    SPILCD_EzI2CInit();

#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPILCD_Enable
****************************************************************************//**
*
*  Enables SPILCD component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  SPILCD_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The SPILCD configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured SPILCD”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void SPILCD_Enable(void)
{
#if (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!SPILCD_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SPILCD_CTRL_REG |= SPILCD_CTRL_ENABLED;

        SPILCD_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        SPILCD_ScbModePostEnable();
    }
#else
    SPILCD_CTRL_REG |= SPILCD_CTRL_ENABLED;

    SPILCD_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    SPILCD_ScbModePostEnable();
#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPILCD_Start
****************************************************************************//**
*
*  Invokes SPILCD_Init() and SPILCD_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  SPILCD_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void SPILCD_Start(void)
{
    if (0u == SPILCD_initVar)
    {
        SPILCD_Init();
        SPILCD_initVar = 1u; /* Component was initialized */
    }

    SPILCD_Enable();
}


/*******************************************************************************
* Function Name: SPILCD_Stop
****************************************************************************//**
*
*  Disables the SPILCD component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function SPILCD_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void SPILCD_Stop(void)
{
#if (SPILCD_SCB_IRQ_INTERNAL)
    SPILCD_DisableInt();
#endif /* (SPILCD_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    SPILCD_ScbModeStop();

    /* Disable SCB IP */
    SPILCD_CTRL_REG &= (uint32) ~SPILCD_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    SPILCD_SetTxInterruptMode(SPILCD_NO_INTR_SOURCES);

#if (SPILCD_SCB_IRQ_INTERNAL)
    SPILCD_ClearPendingInt();
#endif /* (SPILCD_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SPILCD_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void SPILCD_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = SPILCD_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~SPILCD_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (SPILCD_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SPILCD_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: SPILCD_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void SPILCD_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = SPILCD_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~SPILCD_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (SPILCD_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SPILCD_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (SPILCD_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: SPILCD_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void SPILCD_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_SPILCD_CUSTOM_INTR_HANDLER)
        SPILCD_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_SPILCD_CUSTOM_INTR_HANDLER) */
    }
#endif /* (SPILCD_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: SPILCD_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void SPILCD_ScbEnableIntr(void)
{
#if (SPILCD_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != SPILCD_scbEnableIntr)
        {
            SPILCD_EnableInt();
        }

    #else
        SPILCD_EnableInt();

    #endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (SPILCD_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SPILCD_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void SPILCD_ScbModePostEnable(void)
{
#if (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!SPILCD_CY_SCBIP_V1)
    if (SPILCD_SCB_MODE_SPI_RUNTM_CFG)
    {
        SPILCD_SpiPostEnable();
    }
    else if (SPILCD_SCB_MODE_UART_RUNTM_CFG)
    {
        SPILCD_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!SPILCD_CY_SCBIP_V1) */

#elif (SPILCD_SCB_MODE_SPI_CONST_CFG)
    SPILCD_SpiPostEnable();

#elif (SPILCD_SCB_MODE_UART_CONST_CFG)
    SPILCD_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPILCD_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void SPILCD_ScbModeStop(void)
{
#if (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SPILCD_SCB_MODE_I2C_RUNTM_CFG)
    {
        SPILCD_I2CStop();
    }
    else if (SPILCD_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SPILCD_EzI2CStop();
    }
#if (!SPILCD_CY_SCBIP_V1)
    else if (SPILCD_SCB_MODE_SPI_RUNTM_CFG)
    {
        SPILCD_SpiStop();
    }
    else if (SPILCD_SCB_MODE_UART_RUNTM_CFG)
    {
        SPILCD_UartStop();
    }
#endif /* (!SPILCD_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (SPILCD_SCB_MODE_I2C_CONST_CFG)
    SPILCD_I2CStop();

#elif (SPILCD_SCB_MODE_EZI2C_CONST_CFG)
    SPILCD_EzI2CStop();

#elif (SPILCD_SCB_MODE_SPI_CONST_CFG)
    SPILCD_SpiStop();

#elif (SPILCD_SCB_MODE_UART_CONST_CFG)
    SPILCD_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: SPILCD_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void SPILCD_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[SPILCD_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!SPILCD_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!SPILCD_CY_SCBIP_V1) */
        
        uint32 hsiomSel[SPILCD_SCB_PINS_NUMBER] = 
        {
            SPILCD_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            SPILCD_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (SPILCD_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (SPILCD_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < SPILCD_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = SPILCD_PIN_DM_ALG_HIZ;
        }

        if ((SPILCD_SCB_MODE_I2C   == mode) ||
            (SPILCD_SCB_MODE_EZI2C == mode))
        {
        #if (SPILCD_RX_SCL_MOSI_PIN)
            hsiomSel[SPILCD_RX_SCL_MOSI_PIN_INDEX] = SPILCD_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [SPILCD_RX_SCL_MOSI_PIN_INDEX] = SPILCD_PIN_DM_OD_LO;
        #elif (SPILCD_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[SPILCD_RX_WAKE_SCL_MOSI_PIN_INDEX] = SPILCD_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [SPILCD_RX_WAKE_SCL_MOSI_PIN_INDEX] = SPILCD_PIN_DM_OD_LO;
        #else
        #endif /* (SPILCD_RX_SCL_MOSI_PIN) */
        
        #if (SPILCD_TX_SDA_MISO_PIN)
            hsiomSel[SPILCD_TX_SDA_MISO_PIN_INDEX] = SPILCD_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [SPILCD_TX_SDA_MISO_PIN_INDEX] = SPILCD_PIN_DM_OD_LO;
        #endif /* (SPILCD_TX_SDA_MISO_PIN) */
        }
    #if (!SPILCD_CY_SCBIP_V1)
        else if (SPILCD_SCB_MODE_SPI == mode)
        {
        #if (SPILCD_RX_SCL_MOSI_PIN)
            hsiomSel[SPILCD_RX_SCL_MOSI_PIN_INDEX] = SPILCD_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (SPILCD_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[SPILCD_RX_WAKE_SCL_MOSI_PIN_INDEX] = SPILCD_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (SPILCD_RX_SCL_MOSI_PIN) */
        
        #if (SPILCD_TX_SDA_MISO_PIN)
            hsiomSel[SPILCD_TX_SDA_MISO_PIN_INDEX] = SPILCD_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (SPILCD_TX_SDA_MISO_PIN) */
        
        #if (SPILCD_SCLK_PIN)
            hsiomSel[SPILCD_SCLK_PIN_INDEX] = SPILCD_SCLK_HSIOM_SEL_SPI;
        #endif /* (SPILCD_SCLK_PIN) */

            if (SPILCD_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[SPILCD_RX_SCL_MOSI_PIN_INDEX] = SPILCD_PIN_DM_DIG_HIZ;
                pinsDm[SPILCD_TX_SDA_MISO_PIN_INDEX] = SPILCD_PIN_DM_STRONG;
                pinsDm[SPILCD_SCLK_PIN_INDEX] = SPILCD_PIN_DM_DIG_HIZ;

            #if (SPILCD_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[SPILCD_SS0_PIN_INDEX] = SPILCD_SS0_HSIOM_SEL_SPI;
                pinsDm  [SPILCD_SS0_PIN_INDEX] = SPILCD_PIN_DM_DIG_HIZ;
            #endif /* (SPILCD_SS0_PIN) */

            #if (SPILCD_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= SPILCD_TX_SDA_MISO_PIN_MASK;
            #endif /* (SPILCD_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[SPILCD_RX_SCL_MOSI_PIN_INDEX] = SPILCD_PIN_DM_STRONG;
                pinsDm[SPILCD_TX_SDA_MISO_PIN_INDEX] = SPILCD_PIN_DM_DIG_HIZ;
                pinsDm[SPILCD_SCLK_PIN_INDEX] = SPILCD_PIN_DM_STRONG;

            #if (SPILCD_SS0_PIN)
                hsiomSel [SPILCD_SS0_PIN_INDEX] = SPILCD_SS0_HSIOM_SEL_SPI;
                pinsDm   [SPILCD_SS0_PIN_INDEX] = SPILCD_PIN_DM_STRONG;
                pinsInBuf |= SPILCD_SS0_PIN_MASK;
            #endif /* (SPILCD_SS0_PIN) */

            #if (SPILCD_SS1_PIN)
                hsiomSel [SPILCD_SS1_PIN_INDEX] = SPILCD_SS1_HSIOM_SEL_SPI;
                pinsDm   [SPILCD_SS1_PIN_INDEX] = SPILCD_PIN_DM_STRONG;
                pinsInBuf |= SPILCD_SS1_PIN_MASK;
            #endif /* (SPILCD_SS1_PIN) */

            #if (SPILCD_SS2_PIN)
                hsiomSel [SPILCD_SS2_PIN_INDEX] = SPILCD_SS2_HSIOM_SEL_SPI;
                pinsDm   [SPILCD_SS2_PIN_INDEX] = SPILCD_PIN_DM_STRONG;
                pinsInBuf |= SPILCD_SS2_PIN_MASK;
            #endif /* (SPILCD_SS2_PIN) */

            #if (SPILCD_SS3_PIN)
                hsiomSel [SPILCD_SS3_PIN_INDEX] = SPILCD_SS3_HSIOM_SEL_SPI;
                pinsDm   [SPILCD_SS3_PIN_INDEX] = SPILCD_PIN_DM_STRONG;
                pinsInBuf |= SPILCD_SS3_PIN_MASK;
            #endif /* (SPILCD_SS3_PIN) */

                /* Disable input buffers */
            #if (SPILCD_RX_SCL_MOSI_PIN)
                pinsInBuf |= SPILCD_RX_SCL_MOSI_PIN_MASK;
            #elif (SPILCD_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= SPILCD_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (SPILCD_RX_SCL_MOSI_PIN) */

            #if (SPILCD_SCLK_PIN)
                pinsInBuf |= SPILCD_SCLK_PIN_MASK;
            #endif /* (SPILCD_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (SPILCD_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (SPILCD_TX_SDA_MISO_PIN)
                hsiomSel[SPILCD_TX_SDA_MISO_PIN_INDEX] = SPILCD_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [SPILCD_TX_SDA_MISO_PIN_INDEX] = SPILCD_PIN_DM_OD_LO;
            #endif /* (SPILCD_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (SPILCD_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (SPILCD_RX_SCL_MOSI_PIN)
                    hsiomSel[SPILCD_RX_SCL_MOSI_PIN_INDEX] = SPILCD_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [SPILCD_RX_SCL_MOSI_PIN_INDEX] = SPILCD_PIN_DM_DIG_HIZ;
                #elif (SPILCD_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[SPILCD_RX_WAKE_SCL_MOSI_PIN_INDEX] = SPILCD_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [SPILCD_RX_WAKE_SCL_MOSI_PIN_INDEX] = SPILCD_PIN_DM_DIG_HIZ;
                #else
                #endif /* (SPILCD_RX_SCL_MOSI_PIN) */
                }

                if (0u != (SPILCD_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (SPILCD_TX_SDA_MISO_PIN)
                    hsiomSel[SPILCD_TX_SDA_MISO_PIN_INDEX] = SPILCD_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [SPILCD_TX_SDA_MISO_PIN_INDEX] = SPILCD_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= SPILCD_TX_SDA_MISO_PIN_MASK;
                #endif /* (SPILCD_TX_SDA_MISO_PIN) */
                }

            #if !(SPILCD_CY_SCBIP_V0 || SPILCD_CY_SCBIP_V1)
                if (SPILCD_UART_MODE_STD == subMode)
                {
                    if (0u != (SPILCD_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (SPILCD_SCLK_PIN)
                        hsiomSel[SPILCD_SCLK_PIN_INDEX] = SPILCD_SCLK_HSIOM_SEL_UART;
                        pinsDm  [SPILCD_SCLK_PIN_INDEX] = SPILCD_PIN_DM_DIG_HIZ;
                    #endif /* (SPILCD_SCLK_PIN) */
                    }

                    if (0u != (SPILCD_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (SPILCD_SS0_PIN)
                        hsiomSel[SPILCD_SS0_PIN_INDEX] = SPILCD_SS0_HSIOM_SEL_UART;
                        pinsDm  [SPILCD_SS0_PIN_INDEX] = SPILCD_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= SPILCD_SS0_PIN_MASK;
                    #endif /* (SPILCD_SS0_PIN) */
                    }
                }
            #endif /* !(SPILCD_CY_SCBIP_V0 || SPILCD_CY_SCBIP_V1) */
            }
        }
    #endif /* (!SPILCD_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (SPILCD_RX_SCL_MOSI_PIN)
        SPILCD_SET_HSIOM_SEL(SPILCD_RX_SCL_MOSI_HSIOM_REG,
                                       SPILCD_RX_SCL_MOSI_HSIOM_MASK,
                                       SPILCD_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[SPILCD_RX_SCL_MOSI_PIN_INDEX]);

        SPILCD_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[SPILCD_RX_SCL_MOSI_PIN_INDEX]);

        #if (!SPILCD_CY_SCBIP_V1)
            SPILCD_SET_INP_DIS(SPILCD_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         SPILCD_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & SPILCD_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!SPILCD_CY_SCBIP_V1) */
    
    #elif (SPILCD_RX_WAKE_SCL_MOSI_PIN)
        SPILCD_SET_HSIOM_SEL(SPILCD_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       SPILCD_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       SPILCD_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[SPILCD_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SPILCD_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[SPILCD_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SPILCD_SET_INP_DIS(SPILCD_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     SPILCD_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & SPILCD_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        SPILCD_SET_INCFG_TYPE(SPILCD_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        SPILCD_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        SPILCD_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        SPILCD_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (SPILCD_RX_WAKE_SCL_MOSI_PIN) */

    #if (SPILCD_TX_SDA_MISO_PIN)
        SPILCD_SET_HSIOM_SEL(SPILCD_TX_SDA_MISO_HSIOM_REG,
                                       SPILCD_TX_SDA_MISO_HSIOM_MASK,
                                       SPILCD_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[SPILCD_TX_SDA_MISO_PIN_INDEX]);

        SPILCD_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[SPILCD_TX_SDA_MISO_PIN_INDEX]);

    #if (!SPILCD_CY_SCBIP_V1)
        SPILCD_SET_INP_DIS(SPILCD_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     SPILCD_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & SPILCD_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!SPILCD_CY_SCBIP_V1) */
    #endif /* (SPILCD_RX_SCL_MOSI_PIN) */

    #if (SPILCD_SCLK_PIN)
        SPILCD_SET_HSIOM_SEL(SPILCD_SCLK_HSIOM_REG,
                                       SPILCD_SCLK_HSIOM_MASK,
                                       SPILCD_SCLK_HSIOM_POS,
                                       hsiomSel[SPILCD_SCLK_PIN_INDEX]);

        SPILCD_spi_sclk_SetDriveMode((uint8) pinsDm[SPILCD_SCLK_PIN_INDEX]);

        SPILCD_SET_INP_DIS(SPILCD_spi_sclk_INP_DIS,
                                     SPILCD_spi_sclk_MASK,
                                     (0u != (pinsInBuf & SPILCD_SCLK_PIN_MASK)));
    #endif /* (SPILCD_SCLK_PIN) */

    #if (SPILCD_SS0_PIN)
        SPILCD_SET_HSIOM_SEL(SPILCD_SS0_HSIOM_REG,
                                       SPILCD_SS0_HSIOM_MASK,
                                       SPILCD_SS0_HSIOM_POS,
                                       hsiomSel[SPILCD_SS0_PIN_INDEX]);

        SPILCD_spi_ss0_SetDriveMode((uint8) pinsDm[SPILCD_SS0_PIN_INDEX]);

        SPILCD_SET_INP_DIS(SPILCD_spi_ss0_INP_DIS,
                                     SPILCD_spi_ss0_MASK,
                                     (0u != (pinsInBuf & SPILCD_SS0_PIN_MASK)));
    #endif /* (SPILCD_SS0_PIN) */

    #if (SPILCD_SS1_PIN)
        SPILCD_SET_HSIOM_SEL(SPILCD_SS1_HSIOM_REG,
                                       SPILCD_SS1_HSIOM_MASK,
                                       SPILCD_SS1_HSIOM_POS,
                                       hsiomSel[SPILCD_SS1_PIN_INDEX]);

        SPILCD_spi_ss1_SetDriveMode((uint8) pinsDm[SPILCD_SS1_PIN_INDEX]);

        SPILCD_SET_INP_DIS(SPILCD_spi_ss1_INP_DIS,
                                     SPILCD_spi_ss1_MASK,
                                     (0u != (pinsInBuf & SPILCD_SS1_PIN_MASK)));
    #endif /* (SPILCD_SS1_PIN) */

    #if (SPILCD_SS2_PIN)
        SPILCD_SET_HSIOM_SEL(SPILCD_SS2_HSIOM_REG,
                                       SPILCD_SS2_HSIOM_MASK,
                                       SPILCD_SS2_HSIOM_POS,
                                       hsiomSel[SPILCD_SS2_PIN_INDEX]);

        SPILCD_spi_ss2_SetDriveMode((uint8) pinsDm[SPILCD_SS2_PIN_INDEX]);

        SPILCD_SET_INP_DIS(SPILCD_spi_ss2_INP_DIS,
                                     SPILCD_spi_ss2_MASK,
                                     (0u != (pinsInBuf & SPILCD_SS2_PIN_MASK)));
    #endif /* (SPILCD_SS2_PIN) */

    #if (SPILCD_SS3_PIN)
        SPILCD_SET_HSIOM_SEL(SPILCD_SS3_HSIOM_REG,
                                       SPILCD_SS3_HSIOM_MASK,
                                       SPILCD_SS3_HSIOM_POS,
                                       hsiomSel[SPILCD_SS3_PIN_INDEX]);

        SPILCD_spi_ss3_SetDriveMode((uint8) pinsDm[SPILCD_SS3_PIN_INDEX]);

        SPILCD_SET_INP_DIS(SPILCD_spi_ss3_INP_DIS,
                                     SPILCD_spi_ss3_MASK,
                                     (0u != (pinsInBuf & SPILCD_SS3_PIN_MASK)));
    #endif /* (SPILCD_SS3_PIN) */
    }

#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (SPILCD_CY_SCBIP_V0 || SPILCD_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SPILCD_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void SPILCD_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (SPILCD_CTRL_REG & SPILCD_CTRL_EC_AM_MODE)) &&
            (0u == (SPILCD_I2C_CTRL_REG & SPILCD_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            SPILCD_CTRL_REG &= ~SPILCD_CTRL_EC_AM_MODE;
            SPILCD_CTRL_REG |=  SPILCD_CTRL_EC_AM_MODE;
        }

        SPILCD_I2C_SLAVE_CMD_REG = SPILCD_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (SPILCD_CY_SCBIP_V0 || SPILCD_CY_SCBIP_V1) */


/* [] END OF FILE */
