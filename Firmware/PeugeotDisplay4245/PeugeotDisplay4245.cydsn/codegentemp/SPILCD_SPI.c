/***************************************************************************//**
* \file SPILCD_SPI.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
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
#include "SPILCD_SPI_UART_PVT.h"

#if(SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const SPILCD_SPI_INIT_STRUCT SPILCD_configSpi =
    {
        SPILCD_SPI_MODE,
        SPILCD_SPI_SUB_MODE,
        SPILCD_SPI_CLOCK_MODE,
        SPILCD_SPI_OVS_FACTOR,
        SPILCD_SPI_MEDIAN_FILTER_ENABLE,
        SPILCD_SPI_LATE_MISO_SAMPLE_ENABLE,
        SPILCD_SPI_WAKE_ENABLE,
        SPILCD_SPI_RX_DATA_BITS_NUM,
        SPILCD_SPI_TX_DATA_BITS_NUM,
        SPILCD_SPI_BITS_ORDER,
        SPILCD_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) SPILCD_SCB_IRQ_INTERNAL,
        SPILCD_SPI_INTR_RX_MASK,
        SPILCD_SPI_RX_TRIGGER_LEVEL,
        SPILCD_SPI_INTR_TX_MASK,
        SPILCD_SPI_TX_TRIGGER_LEVEL,
        (uint8) SPILCD_SPI_BYTE_MODE_ENABLE,
        (uint8) SPILCD_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) SPILCD_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: SPILCD_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SPILCD for SPI operation.
    *
    *  This function is intended specifically to be used when the SPILCD 
    *  configuration is set to “Unconfigured SPILCD” in the customizer. 
    *  After initializing the SPILCD in SPI mode using this function, 
    *  the component can be enabled using the SPILCD_Start() or 
    * SPILCD_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void SPILCD_SpiInit(const SPILCD_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            SPILCD_SetPins(SPILCD_SCB_MODE_SPI, config->mode, SPILCD_DUMMY_PARAM);

            /* Store internal configuration */
            SPILCD_scbMode       = (uint8) SPILCD_SCB_MODE_SPI;
            SPILCD_scbEnableWake = (uint8) config->enableWake;
            SPILCD_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            SPILCD_rxBuffer      =         config->rxBuffer;
            SPILCD_rxDataBits    = (uint8) config->rxDataBits;
            SPILCD_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            SPILCD_txBuffer      =         config->txBuffer;
            SPILCD_txDataBits    = (uint8) config->txDataBits;
            SPILCD_txBufferSize  =         config->txBufferSize;

            /* Configure SPI interface */
            SPILCD_CTRL_REG     = SPILCD_GET_CTRL_OVS(config->oversample)           |
                                            SPILCD_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            SPILCD_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            SPILCD_CTRL_SPI;

            SPILCD_SPI_CTRL_REG = SPILCD_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            SPILCD_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          SPILCD_SPI_MODE_TI_PRECEDES_MASK) |
                                            SPILCD_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            SPILCD_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            SPILCD_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            SPILCD_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            SPILCD_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            SPILCD_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            SPILCD_RX_CTRL_REG     =  SPILCD_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                SPILCD_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                SPILCD_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                SPILCD_SPI_RX_CTRL;

            SPILCD_RX_FIFO_CTRL_REG = SPILCD_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            SPILCD_TX_CTRL_REG      = SPILCD_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                SPILCD_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                SPILCD_SPI_TX_CTRL;

            SPILCD_TX_FIFO_CTRL_REG = SPILCD_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (SPILCD_ISR_NUMBER);
            CyIntSetPriority(SPILCD_ISR_NUMBER, SPILCD_ISR_PRIORITY);
            (void) CyIntSetVector(SPILCD_ISR_NUMBER, &SPILCD_SPI_UART_ISR);

            /* Configure interrupt sources */
            SPILCD_INTR_I2C_EC_MASK_REG = SPILCD_NO_INTR_SOURCES;
            SPILCD_INTR_SPI_EC_MASK_REG = SPILCD_NO_INTR_SOURCES;
            SPILCD_INTR_SLAVE_MASK_REG  = SPILCD_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            SPILCD_INTR_MASTER_MASK_REG = SPILCD_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            SPILCD_INTR_RX_MASK_REG     = SPILCD_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            SPILCD_INTR_TX_MASK_REG     = SPILCD_GET_SPI_INTR_TX_MASK(config->txInterruptMask);
            
            /* Configure TX interrupt sources to restore. */
            SPILCD_IntrTxMask = LO16(SPILCD_INTR_TX_MASK_REG);

            /* Set active SS0 */
            SPILCD_SpiSetActiveSlaveSelect(SPILCD_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            SPILCD_rxBufferHead     = 0u;
            SPILCD_rxBufferTail     = 0u;
            SPILCD_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            SPILCD_txBufferHead = 0u;
            SPILCD_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: SPILCD_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the SPI operation.
    *
    *******************************************************************************/
    void SPILCD_SpiInit(void)
    {
        /* Configure SPI interface */
        SPILCD_CTRL_REG     = SPILCD_SPI_DEFAULT_CTRL;
        SPILCD_SPI_CTRL_REG = SPILCD_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        SPILCD_RX_CTRL_REG      = SPILCD_SPI_DEFAULT_RX_CTRL;
        SPILCD_RX_FIFO_CTRL_REG = SPILCD_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        SPILCD_TX_CTRL_REG      = SPILCD_SPI_DEFAULT_TX_CTRL;
        SPILCD_TX_FIFO_CTRL_REG = SPILCD_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(SPILCD_SCB_IRQ_INTERNAL)
            CyIntDisable    (SPILCD_ISR_NUMBER);
            CyIntSetPriority(SPILCD_ISR_NUMBER, SPILCD_ISR_PRIORITY);
            (void) CyIntSetVector(SPILCD_ISR_NUMBER, &SPILCD_SPI_UART_ISR);
    #endif /* (SPILCD_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        SPILCD_INTR_I2C_EC_MASK_REG = SPILCD_SPI_DEFAULT_INTR_I2C_EC_MASK;
        SPILCD_INTR_SPI_EC_MASK_REG = SPILCD_SPI_DEFAULT_INTR_SPI_EC_MASK;
        SPILCD_INTR_SLAVE_MASK_REG  = SPILCD_SPI_DEFAULT_INTR_SLAVE_MASK;
        SPILCD_INTR_MASTER_MASK_REG = SPILCD_SPI_DEFAULT_INTR_MASTER_MASK;
        SPILCD_INTR_RX_MASK_REG     = SPILCD_SPI_DEFAULT_INTR_RX_MASK;
        SPILCD_INTR_TX_MASK_REG     = SPILCD_SPI_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        SPILCD_IntrTxMask = LO16(SPILCD_INTR_TX_MASK_REG);
            
        /* Set active SS0 for master */
    #if (SPILCD_SPI_MASTER_CONST)
        SPILCD_SpiSetActiveSlaveSelect(SPILCD_SPI_SLAVE_SELECT0);
    #endif /* (SPILCD_SPI_MASTER_CONST) */

    #if(SPILCD_INTERNAL_RX_SW_BUFFER_CONST)
        SPILCD_rxBufferHead     = 0u;
        SPILCD_rxBufferTail     = 0u;
        SPILCD_rxBufferOverflow = 0u;
    #endif /* (SPILCD_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(SPILCD_INTERNAL_TX_SW_BUFFER_CONST)
        SPILCD_txBufferHead = 0u;
        SPILCD_txBufferTail = 0u;
    #endif /* (SPILCD_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: SPILCD_SpiPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
*******************************************************************************/
void SPILCD_SpiPostEnable(void)
{
#if(SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)

    if (SPILCD_CHECK_SPI_MASTER)
    {
    #if (SPILCD_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SCLK_HSIOM_REG, SPILCD_SCLK_HSIOM_MASK,
                                       SPILCD_SCLK_HSIOM_POS, SPILCD_SCLK_HSIOM_SEL_SPI);
    #endif /* (SPILCD_SCLK_PIN) */

    #if (SPILCD_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS0_HSIOM_REG, SPILCD_SS0_HSIOM_MASK,
                                       SPILCD_SS0_HSIOM_POS, SPILCD_SS0_HSIOM_SEL_SPI);
    #endif /* (SPILCD_SS0_PIN) */

    #if (SPILCD_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS1_HSIOM_REG, SPILCD_SS1_HSIOM_MASK,
                                       SPILCD_SS1_HSIOM_POS, SPILCD_SS1_HSIOM_SEL_SPI);
    #endif /* (SPILCD_SS1_PIN) */

    #if (SPILCD_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS2_HSIOM_REG, SPILCD_SS2_HSIOM_MASK,
                                       SPILCD_SS2_HSIOM_POS, SPILCD_SS2_HSIOM_SEL_SPI);
    #endif /* (SPILCD_SS2_PIN) */

    #if (SPILCD_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS3_HSIOM_REG, SPILCD_SS3_HSIOM_MASK,
                                       SPILCD_SS3_HSIOM_POS, SPILCD_SS3_HSIOM_SEL_SPI);
    #endif /* (SPILCD_SS3_PIN) */
    }

#else

    #if (SPILCD_SPI_MASTER_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SCLK_M_HSIOM_REG, SPILCD_SCLK_M_HSIOM_MASK,
                                       SPILCD_SCLK_M_HSIOM_POS, SPILCD_SCLK_M_HSIOM_SEL_SPI);
    #endif /* (SPILCD_MISO_SDA_TX_PIN_PIN) */

    #if (SPILCD_SPI_MASTER_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS0_M_HSIOM_REG, SPILCD_SS0_M_HSIOM_MASK,
                                       SPILCD_SS0_M_HSIOM_POS, SPILCD_SS0_M_HSIOM_SEL_SPI);
    #endif /* (SPILCD_SPI_MASTER_SS0_PIN) */

    #if (SPILCD_SPI_MASTER_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS1_M_HSIOM_REG, SPILCD_SS1_M_HSIOM_MASK,
                                       SPILCD_SS1_M_HSIOM_POS, SPILCD_SS1_M_HSIOM_SEL_SPI);
    #endif /* (SPILCD_SPI_MASTER_SS1_PIN) */

    #if (SPILCD_SPI_MASTER_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS2_M_HSIOM_REG, SPILCD_SS2_M_HSIOM_MASK,
                                       SPILCD_SS2_M_HSIOM_POS, SPILCD_SS2_M_HSIOM_SEL_SPI);
    #endif /* (SPILCD_SPI_MASTER_SS2_PIN) */

    #if (SPILCD_SPI_MASTER_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS3_M_HSIOM_REG, SPILCD_SS3_M_HSIOM_MASK,
                                       SPILCD_SS3_M_HSIOM_POS, SPILCD_SS3_M_HSIOM_SEL_SPI);
    #endif /* (SPILCD_SPI_MASTER_SS3_PIN) */

#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    SPILCD_SetTxInterruptMode(SPILCD_IntrTxMask);
}


/*******************************************************************************
* Function Name: SPILCD_SpiStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the SPI master output pins 
*  (SCLK and/or SS0-SS3) to keep them inactive after the block is disabled. 
*  The output pins are controlled by the GPIO data register.
*
*******************************************************************************/
void SPILCD_SpiStop(void)
{
#if(SPILCD_SCB_MODE_UNCONFIG_CONST_CFG)

    if (SPILCD_CHECK_SPI_MASTER)
    {
    #if (SPILCD_SCLK_PIN)
        /* Set output pin state after block is disabled */
        SPILCD_spi_sclk_Write(SPILCD_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SCLK_HSIOM_REG, SPILCD_SCLK_HSIOM_MASK,
                                       SPILCD_SCLK_HSIOM_POS, SPILCD_SCLK_HSIOM_SEL_GPIO);
    #endif /* (SPILCD_spi_sclk_PIN) */

    #if (SPILCD_SS0_PIN)
        /* Set output pin state after block is disabled */
        SPILCD_spi_ss0_Write(SPILCD_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS0_HSIOM_REG, SPILCD_SS0_HSIOM_MASK,
                                       SPILCD_SS0_HSIOM_POS, SPILCD_SS0_HSIOM_SEL_GPIO);
    #endif /* (SPILCD_spi_ss0_PIN) */

    #if (SPILCD_SS1_PIN)
        /* Set output pin state after block is disabled */
        SPILCD_spi_ss1_Write(SPILCD_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS1_HSIOM_REG, SPILCD_SS1_HSIOM_MASK,
                                       SPILCD_SS1_HSIOM_POS, SPILCD_SS1_HSIOM_SEL_GPIO);
    #endif /* (SPILCD_SS1_PIN) */

    #if (SPILCD_SS2_PIN)
        /* Set output pin state after block is disabled */
        SPILCD_spi_ss2_Write(SPILCD_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS2_HSIOM_REG, SPILCD_SS2_HSIOM_MASK,
                                       SPILCD_SS2_HSIOM_POS, SPILCD_SS2_HSIOM_SEL_GPIO);
    #endif /* (SPILCD_SS2_PIN) */

    #if (SPILCD_SS3_PIN)
        /* Set output pin state after block is disabled */
        SPILCD_spi_ss3_Write(SPILCD_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        SPILCD_SET_HSIOM_SEL(SPILCD_SS3_HSIOM_REG, SPILCD_SS3_HSIOM_MASK,
                                       SPILCD_SS3_HSIOM_POS, SPILCD_SS3_HSIOM_SEL_GPIO);
    #endif /* (SPILCD_SS3_PIN) */
    
        /* Store TX interrupt sources (exclude level triggered) for master. */
        SPILCD_IntrTxMask = LO16(SPILCD_GetTxInterruptMode() & SPILCD_INTR_SPIM_TX_RESTORE);
    }
    else
    {
        /* Store TX interrupt sources (exclude level triggered) for slave. */
        SPILCD_IntrTxMask = LO16(SPILCD_GetTxInterruptMode() & SPILCD_INTR_SPIS_TX_RESTORE);
    }

#else

#if (SPILCD_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    SPILCD_sclk_m_Write(SPILCD_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    SPILCD_SET_HSIOM_SEL(SPILCD_SCLK_M_HSIOM_REG, SPILCD_SCLK_M_HSIOM_MASK,
                                   SPILCD_SCLK_M_HSIOM_POS, SPILCD_SCLK_M_HSIOM_SEL_GPIO);
#endif /* (SPILCD_MISO_SDA_TX_PIN_PIN) */

#if (SPILCD_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    SPILCD_ss0_m_Write(SPILCD_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    SPILCD_SET_HSIOM_SEL(SPILCD_SS0_M_HSIOM_REG, SPILCD_SS0_M_HSIOM_MASK,
                                   SPILCD_SS0_M_HSIOM_POS, SPILCD_SS0_M_HSIOM_SEL_GPIO);
#endif /* (SPILCD_SPI_MASTER_SS0_PIN) */

#if (SPILCD_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    SPILCD_ss1_m_Write(SPILCD_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    SPILCD_SET_HSIOM_SEL(SPILCD_SS1_M_HSIOM_REG, SPILCD_SS1_M_HSIOM_MASK,
                                   SPILCD_SS1_M_HSIOM_POS, SPILCD_SS1_M_HSIOM_SEL_GPIO);
#endif /* (SPILCD_SPI_MASTER_SS1_PIN) */

#if (SPILCD_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    SPILCD_ss2_m_Write(SPILCD_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    SPILCD_SET_HSIOM_SEL(SPILCD_SS2_M_HSIOM_REG, SPILCD_SS2_M_HSIOM_MASK,
                                   SPILCD_SS2_M_HSIOM_POS, SPILCD_SS2_M_HSIOM_SEL_GPIO);
#endif /* (SPILCD_SPI_MASTER_SS2_PIN) */

#if (SPILCD_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    SPILCD_ss3_m_Write(SPILCD_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    SPILCD_SET_HSIOM_SEL(SPILCD_SS3_M_HSIOM_REG, SPILCD_SS3_M_HSIOM_MASK,
                                   SPILCD_SS3_M_HSIOM_POS, SPILCD_SS3_M_HSIOM_SEL_GPIO);
#endif /* (SPILCD_SPI_MASTER_SS3_PIN) */

    #if (SPILCD_SPI_MASTER_CONST)
        /* Store TX interrupt sources (exclude level triggered). */
        SPILCD_IntrTxMask = LO16(SPILCD_GetTxInterruptMode() & SPILCD_INTR_SPIM_TX_RESTORE);
    #else
        /* Store TX interrupt sources (exclude level triggered). */
        SPILCD_IntrTxMask = LO16(SPILCD_GetTxInterruptMode() & SPILCD_INTR_SPIS_TX_RESTORE);
    #endif /* (SPILCD_SPI_MASTER_CONST) */

#endif /* (SPILCD_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (SPILCD_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: SPILCD_SetActiveSlaveSelect
    ****************************************************************************//**
    *
    *  Selects one of the four slave select lines to be active during the transfer.
    *  After initialization the active slave select line is 0.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer (TX FIFO is empty and the
    *     SCB_INTR_MASTER_SPI_DONE status is set).
    *
    *  This function does not check that these conditions are met.
    *  This function is only applicable to SPI Master mode of operation.
    *
    *  \param slaveSelect: slave select line which will be active while the following
    *   transfer.
    *   - SPILCD_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - SPILCD_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - SPILCD_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - SPILCD_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *******************************************************************************/
    void SPILCD_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = SPILCD_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~SPILCD_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  SPILCD_GET_SPI_CTRL_SS(slaveSelect);

        SPILCD_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (SPILCD_SPI_MASTER_CONST) */


#if !(SPILCD_CY_SCBIP_V0 || SPILCD_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SPILCD_SpiSetSlaveSelectPolarity
    ****************************************************************************//**
    *
    *  Sets active polarity for slave select line.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer.
    *  
    *  This function does not check that these conditions are met.
    *
    *  \param slaveSelect: slave select line to change active polarity.
    *   - SPILCD_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - SPILCD_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - SPILCD_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - SPILCD_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *  \param polarity: active polarity of slave select line.
    *   - SPILCD_SPI_SS_ACTIVE_LOW  - Slave select is active low.
    *   - SPILCD_SPI_SS_ACTIVE_HIGH - Slave select is active high.
    *
    *******************************************************************************/
    void SPILCD_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = SPILCD_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            SPILCD_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            SPILCD_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(SPILCD_CY_SCBIP_V0 || SPILCD_CY_SCBIP_V1) */


#if(SPILCD_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: SPILCD_SpiSaveConfig
    ****************************************************************************//**
    *
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    *******************************************************************************/
    void SPILCD_SpiSaveConfig(void)
    {
        /* Clear and enable SPI wakeup interrupt source */
        SPILCD_ClearSpiExtClkInterruptSource(SPILCD_INTR_SPI_EC_WAKE_UP);
        SPILCD_SetSpiExtClkInterruptMode(SPILCD_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: SPILCD_SpiRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    *******************************************************************************/
    void SPILCD_SpiRestoreConfig(void)
    {
        /* Disable SPI wakeup interrupt source */
        SPILCD_SetSpiExtClkInterruptMode(SPILCD_NO_INTR_SOURCES);
    }
#endif /* (SPILCD_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
