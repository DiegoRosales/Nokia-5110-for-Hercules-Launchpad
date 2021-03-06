/** @file spi.c
*   @brief SPI Driver Implementation File
*   @date 25.July.2013
*   @version 03.06.00
*
*   (c) Texas Instruments 2009-2013, All rights reserved.
*/

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "spi.h"
#include "sys_vim.h"
/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @struct g_spiPacket
*   @brief globals
*
*/
static struct g_spiPacket
{
    spiDAT1_t g_spiDataFormat;
    uint32  tx_length;
    uint32  rx_length;
    uint16  * txdata_ptr;
    uint16  * rxdata_ptr;
    SpiDataStatus_t tx_data_status;
    SpiDataStatus_t rx_data_status;
} g_spiPacket_t[3U];

/** @fn void spiInit(void)
*   @brief Initializes the SPI Driver
*
*   This function initializes the SPI module.
*/
void spiInit(void)
{
/* USER CODE BEGIN (2) */
/* USER CODE END */

    /** @b initialize @b SPI1 */

    /** bring SPI out of reset */
    spiREG1->GCR0 = 1U;

    /** SPI1 master mode and clock configuration */
    spiREG1->GCR1 = (spiREG1->GCR1 & 0xFFFFFFFCU) | ((1U << 1U)  /* CLOKMOD */
                  | 1U);  /* MASTER */

    /** SPI1 enable pin configuration */
    spiREG1->INT0 = (spiREG1->INT0 & 0xFEFFFFFFU)| (0U << 24U);  /* ENABLE HIGHZ */

    /** - Delays */
    spiREG1->DELAY = (0U << 24U)  /* C2TDELAY */
                   | (0U << 16U)  /* T2CDELAY */
                   | (0U << 8U)  /* T2EDELAY */
                   | 0U;  /* C2EDELAY */

    /** - Data Format 0 */
    spiREG1->FMT0 = (0U << 24U)  /* wdelay */
                  | (0U << 23U)  /* parity Polarity */
                  | (0U << 22U)  /* parity enable */
                  | (0U << 21U)  /* wait on enable */
                  | (0U << 20U)  /* shift direction */
                  | (0U << 17U)  /* clock polarity */
                  | (0U << 16U)  /* clock phase */
                  | (99U << 8U) /* baudrate prescale */
                  | 8U;  /* data word length */

    /** - Data Format 1 */
    spiREG1->FMT1 = (0U << 24U)  /* wdelay */
                  | (0U << 23U)  /* parity Polarity */
                  | (0U << 22U)  /* parity enable */
                  | (0U << 21U)  /* wait on enable */
                  | (0U << 20U)  /* shift direction */
                  | (0U << 17U)  /* clock polarity */
                  | (0U << 16U)  /* clock phase */
                  | (99U << 8U) /* baudrate prescale */
                  | 16U;  /* data word length */

    /** - Data Format 2 */
    spiREG1->FMT2 = (0U << 24U)  /* wdelay */
                  | (0U << 23U)  /* parity Polarity */
                  | (0U << 22U)  /* parity enable */
                  | (0U << 21U)  /* wait on enable */
                  | (0U << 20U)  /* shift direction */
                  | (0U << 17U)  /* clock polarity */
                  | (0U << 16U)  /* clock phase */
                  | (99U << 8U) /* baudrate prescale */
                  | 16U;  /* data word length */

    /** - Data Format 3 */
    spiREG1->FMT3 = (0U << 24U)  /* wdelay */
                  | (0U << 23U)  /* parity Polarity */
                  | (0U << 22U)  /* parity enable */
                  | (0U << 21U)  /* wait on enable */
                  | (0U << 20U)  /* shift direction */
                  | (0U << 17U)  /* clock polarity */
                  | (0U << 16U)  /* clock phase */
                  | (99U << 8U) /* baudrate prescale */
                  | 16U;  /* data word length */

    /** - set interrupt levels */
    spiREG1->LVL = (0U << 9U)  /* TXINT */
                 | (0U << 8U)  /* RXINT */
                 | (0U << 6U)  /* OVRNINT */
                 | (0U << 4U)  /* BITERR */
                 | (0U << 3U)  /* DESYNC */
                 | (0U << 2U)  /* PARERR */
                 | (0U << 1U) /* TIMEOUT */
                 | (0U);  /* DLENERR */

    /** - clear any pending interrupts */
    spiREG1->FLG |= 0xFFFFU;

    /** - enable interrupts */
    spiREG1->INT0 = (spiREG1->INT0 & 0xFFFF0000U)
				  | (0U << 9U)  /* TXINT */
                  | (0U << 8U)  /* RXINT */
                  | (0U << 6U)  /* OVRNINT */
                  | (0U << 4U)  /* BITERR */
                  | (0U << 3U)  /* DESYNC */
                  | (0U << 2U)  /* PARERR */
                  | (0U << 1U) /* TIMEOUT */
                  | (0U);  /* DLENERR */

    /** @b initialize @b SPI1 @b Port */

    /** - SPI1 Port output values */
    spiREG1->PC3 =  1U        /* SCS[0] */
                    | (1U << 1U)  /* SCS[1] */
                    | (1U << 2U)  /* SCS[2] */
                    | (1U << 3U)  /* SCS[3] */
                    | (0U << 8U)  /* ENA */
                    | (0U << 9U)  /* CLK */
                    | (0U << 10U)  /* SIMO */
                    | (0U << 11U); /* SOMI */

    /** - SPI1 Port direction */
    spiREG1->PC1  =  1U        /* SCS[0] */
                    | (1U << 1U)  /* SCS[1] */
                    | (1U << 2U)  /* SCS[2] */
                    | (1U << 3U)  /* SCS[3] */
                    | (0U << 8U)  /* ENA */
                    | (1U << 9U)  /* CLK */
                    | (1U << 10U)  /* SIMO */
                    | (0U << 11U); /* SOMI */

    /** - SPI1 Port open drain enable */
    spiREG1->PC6  =  0U        /* SCS[0] */
                    | (0U << 1U)  /* SCS[1] */
                    | (0U << 2U)  /* SCS[2] */
                    | (0U << 3U)  /* SCS[3] */
                    | (0U << 8U)  /* ENA */
                    | (0U << 9U)  /* CLK */
                    | (0U << 10U)  /* SIMO */
                    | (0U << 11U); /* SOMI */

    /** - SPI1 Port pullup / pulldown selection */
    spiREG1->PC8  =  1U       /* SCS[0] */
                    | (1U << 1U)  /* SCS[1] */
                    | (1U << 2U)  /* SCS[2] */
                    | (1U << 3U)  /* SCS[3] */
                    | (1U << 8U)  /* ENA */
                    | (1U << 9U)  /* CLK */
                    | (1U << 10U)  /* SIMO */
                    | (1U << 11U); /* SOMI */

    /** - SPI1 Port pullup / pulldown enable*/
    spiREG1->PC7  =  0U        /* SCS[0] */
                    | (0U << 1U)  /* SCS[1] */
                    | (0U << 2U)  /* SCS[2] */
                    | (0U << 3U)  /* SCS[3] */
                    | (0U << 8U)  /* ENA */
                    | (0U << 9U)  /* CLK */
                    | (0U << 10U)  /* SIMO */
                    | (0U << 11U); /* SOMI */

    /* SPI1 set all pins to functional */
    spiREG1->PC0  =  1U        /* SCS[0] */
                    | (1U << 1U)  /* SCS[1] */
                    | (1U << 2U)  /* SCS[2] */
                    | (1U << 3U)  /* SCS[3] */
                    | (1U << 8U)  /* ENA */
                    | (1U << 9U)  /* CLK */
                    | (1U << 10U)  /* SIMO */
                    | (1U << 11U); /* SOMI */

    /** - Initialize TX and RX data buffer Status */                    
    g_spiPacket_t[0U].tx_data_status  = SPI_READY;
    g_spiPacket_t[0U].rx_data_status  = SPI_READY;
                    
    /** - Finally start SPI1 */
    spiREG1->GCR1 = (spiREG1->GCR1 & 0xFEFFFFFFU) | (1U << 24U);



/* USER CODE BEGIN (3) */
/* USER CODE END */
}


/** @fn void spiSetFunctional(spiBASE_t *spi, uint32 port)
*   @brief Change functional behavior of pins at runtime.
*   @param[in] spi   - Spi module base address
*   @param[in] port  - Value to write to PC0 register
*
*   Change the value of the PC0 register at runtime, this allows to
*   dynamically change the functionality of the SPI pins between functional
*   and GIO mode.
*/
void spiSetFunctional(spiBASE_t *spi, uint32 port)
{
/* USER CODE BEGIN (4) */
/* USER CODE END */

    spi->PC0 = port;

/* USER CODE BEGIN (5) */
/* USER CODE END */
}


/** @fn uint32 spiReceiveData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * destbuff)
*   @brief Receives Data using polling method
*   @param[in] spi   		- Spi module base address
*   @param[in] dataconfig_t	- Spi DAT1 register configuration
*   @param[in] blocksize	- number of data
*   @param[in] destbuff		- Pointer to the destination data (16 bit).
*
*   @return flag register value.
*
*   This function transmits blocksize number of data from source buffer using polling method.
*/
uint32 spiReceiveData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * destbuff)
{
/* USER CODE BEGIN (6) */
/* USER CODE END */
/*SAFETYMCUSW 28 D MR:NA <APPROVED> " loop to send data continuously" */
    do
    {
        if((spi->FLG & 0x000000FFU) !=0U)
        {
          break;
        }
        /*SAFETYMCUSW 51 S MR:12.3 <APPROVED> "Needs shifting for 32-bit value" */
        spi->DAT1 = ((uint32)(dataconfig_t->DFSEL)   << 24U) |
                    ((uint32)(dataconfig_t->CSNR)    << 16U) |
                    ((uint32)(dataconfig_t->WDEL)    << 26U) |
                    ((uint32)(dataconfig_t->CS_HOLD) << 28U) |
                    (0x00000000U);
		/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
        while((spi->FLG & 0x00000100U) != 0x00000100U)
        { 
        } /* Wait */
	    /*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Valid non NULL input parameters are only allowed in this driver" */
        *destbuff = (uint16)spi->BUF;
	    destbuff++;
	    blocksize--;
    }while(blocksize > 0U);

/* USER CODE BEGIN (7) */
/* USER CODE END */

    return (spi->FLG & 0xFFU);
}


/** @fn uint32 spiGetData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * destbuff)
*   @brief Receives Data using interrupt method
*   @param[in] spi   		- Spi module base address
*   @param[in] dataconfig_t	- Spi DAT1 register configuration
*   @param[in] blocksize	- number of data
*   @param[in] destbuff		- Pointer to the destination data (16 bit).
*
*   @return flag register value.
*
*   This function transmits blocksize number of data from source buffer using interrupt method.
*/
void spiGetData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * destbuff)
{
	 uint32 index = spi == spiREG1 ? 0U :(spi==spiREG2 ? 1U : 2U);

/* USER CODE BEGIN (8) */
/* USER CODE END */

     g_spiPacket_t[index].rx_length = blocksize;
     g_spiPacket_t[index].rxdata_ptr   = destbuff;
     g_spiPacket_t[index].g_spiDataFormat = *dataconfig_t;
     g_spiPacket_t[index].rx_data_status = SPI_PENDING;

     spi->INT0 |= 0x0100U;

/* USER CODE BEGIN (9) */
/* USER CODE END */
}


/** @fn uint32 spiTransmitData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff)
*   @brief Transmits Data using polling method
*   @param[in] spi   		- Spi module base address
*   @param[in] dataconfig_t	- Spi DAT1 register configuration
*   @param[in] blocksize	- number of data
*   @param[in] srcbuff		- Pointer to the source data ( 16 bit).
*
*   @return flag register value.
*
*   This function transmits blocksize number of data from source buffer using polling method.
*/
uint32 spiTransmitData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff)
{

    volatile uint32 SpiBuf;
    uint32 Chip_Select_Hold = 0U;

/* USER CODE BEGIN (10) */
/* USER CODE END */
/*SAFETYMCUSW 28 D MR:NA <APPROVED> " loop to send data continuously" */
    do
    {
        if((spi->FLG & 0x000000FFU) !=0U)
        {
           break;
        }
          
        if(blocksize < 2U)
        {
           Chip_Select_Hold = 0U;
        }
        else
        {
           Chip_Select_Hold = (uint32)dataconfig_t->CS_HOLD << 28U;
        }

        /*SAFETYMCUSW 51 S MR:12.3 <APPROVED> "Needs shifting for 32-bit value" */
		/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Valid non NULL input parameters are only allowed in this driver" */
        spi->DAT1 = ((uint32)(dataconfig_t->DFSEL) << 24U) |
                     ((uint32)(dataconfig_t->CSNR)  << 16U) |
                     ((uint32)(dataconfig_t->WDEL)  << 26U) |
                     (Chip_Select_Hold)                     |
                     (*srcbuff);
		srcbuff++;
		/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
        while((spi->FLG & 0x00000100U) != 0x00000100U)
        { 
        } /* Wait */
        SpiBuf = (uint16)spi->BUF;
    
	    blocksize--;
    }while(blocksize > 0U);

/* USER CODE BEGIN (11) */
/* USER CODE END */

    return (spi->FLG & 0xFFU);
}


/** @fn void spiSendData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff)
*   @brief Transmits Data using interrupt method
*   @param[in] spi   		- Spi module base address
*   @param[in] dataconfig_t	- Spi DAT1 register configuration
*   @param[in] blocksize	- number of data
*   @param[in] srcbuff		- Pointer to the source data ( 16 bit).
*
*   @return flag register value.
*
*   This function transmits blocksize number of data from source buffer using interrupt method.
*/
void spiSendData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff)
{
     uint32 index = spi == spiREG1 ? 0U :(spi==spiREG2 ? 1U : 2U);

/* USER CODE BEGIN (12) */
/* USER CODE END */

     g_spiPacket_t[index].tx_length = blocksize;
     g_spiPacket_t[index].txdata_ptr   = srcbuff;
     g_spiPacket_t[index].g_spiDataFormat = *dataconfig_t;
     g_spiPacket_t[index].tx_data_status = SPI_PENDING;

     spi->INT0 |= 0x0200U;

/* USER CODE BEGIN (13) */
/* USER CODE END */
}


/** @fn uint32 spiTransmitAndReceiveData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff, uint16 * destbuff)
*   @brief Transmits and Receive Data using polling method
*   @param[in] spi   		- Spi module base address
*   @param[in] dataconfig_t	- Spi DAT1 register configuration
*   @param[in] blocksize	- number of data
*   @param[in] srcbuff		- Pointer to the source data ( 16 bit).
*   @param[in] destbuff		- Pointer to the destination data ( 16 bit).
*
*   @return flag register value.
*
*   This function transmits and receives blocksize number of data from source buffer using polling method.
*/
uint32 spiTransmitAndReceiveData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff, uint16 * destbuff)
{

    uint32 Chip_Select_Hold = 0U;

/* USER CODE BEGIN (14) */
/* USER CODE END */
/*SAFETYMCUSW 28 D MR:NA <APPROVED> " loop to send data continuously" */
    do
    {
        if((spi->FLG & 0x000000FFU) !=0U)
        {
           break;
        }
          
        if(blocksize < 2U)
        {
           Chip_Select_Hold = 0U;
        }
        else
        {
           Chip_Select_Hold = (uint32)(dataconfig_t->CS_HOLD) << 28U;
        }       

        /*SAFETYMCUSW 51 S MR:12.3 <APPROVED> "Needs shifting for 32-bit value" */
		/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Valid non NULL input parameters are only allowed in this driver" */
        spi->DAT1 = ((uint32)(dataconfig_t->DFSEL) << 24U) |
                   ((uint32)(dataconfig_t->CSNR)  << 16U) |
                   ((uint32)(dataconfig_t->WDEL)  << 26U) |
                   (Chip_Select_Hold)                     |
                   (*srcbuff);
	    srcbuff++;
	    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
        while((spi->FLG & 0x00000100U) != 0x00000100U)
        { 
        } /* Wait */
	    /*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Valid non NULL input parameters are only allowed in this driver" */
        *destbuff = (uint16)spi->BUF;
	    destbuff++;
    
        blocksize--;
		
    }while(blocksize > 0U);

/* USER CODE BEGIN (15) */
/* USER CODE END */

    return (spi->FLG & 0xFFU);
}

/* USER CODE BEGIN (16) */
/* USER CODE END */

/** @fn void spiSendAndGetData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff, uint16 * destbuff)
*   @brief Initiate SPI Transmits and receive Data using Interrupt mode.
*   @param[in] spi   		- Spi module base address
*   @param[in] dataconfig_t	- Spi DAT1 register configuration
*   @param[in] blocksize	- number of data
*   @param[in] srcbuff		- Pointer to the source data ( 16 bit).
*   @param[in] destbuff		- Pointer to the destination data ( 16 bit).
*
*   Initiate SPI Transmits and receive Data using Interrupt mode..
*/
void spiSendAndGetData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint16 * srcbuff, uint16 * destbuff)
{

/* USER CODE BEGIN (17) */
/* USER CODE END */

    uint32 index = spi == spiREG1 ? 0U :(spi==spiREG2 ? 1U : 2U);

    g_spiPacket_t[index].tx_length       = blocksize;
    g_spiPacket_t[index].rx_length       = blocksize;
    g_spiPacket_t[index].txdata_ptr      = srcbuff;
    g_spiPacket_t[index].rxdata_ptr      = destbuff;
    g_spiPacket_t[index].g_spiDataFormat = *dataconfig_t;
    g_spiPacket_t[index].tx_data_status  = SPI_PENDING;
    g_spiPacket_t[index].rx_data_status  = SPI_PENDING;

    spi->INT0 |= 0x0300U;

/* USER CODE BEGIN (18) */
/* USER CODE END */
}

/** @fn SpiDataStatus_t SpiTxStatus(spiBASE_t *spi)
*   @brief Get the status of the SPI Transmit data block.
*   @param[in] spi   		- Spi module base address
*
*   @return Spi Transmit block data status.
*
*   Get the status of the SPI Transmit data block.
*/
SpiDataStatus_t SpiTxStatus(spiBASE_t *spi)
{

/* USER CODE BEGIN (19) */
/* USER CODE END */

    uint32 index = spi == spiREG1 ? 0U :(spi==spiREG2 ? 1U : 2U);
	return(g_spiPacket_t[index].tx_data_status);
}

/* USER CODE BEGIN (20) */
/* USER CODE END */

/** @fn SpiDataStatus_t SpiRxStatus(spiBASE_t *spi)
*   @brief Get the status of the SPI Receive data block.
*   @param[in] spi   		- Spi module base address
*
*   @return Spi Receive block data status.
*
*   Get the status of the SPI Receive data block.
*/
SpiDataStatus_t SpiRxStatus(spiBASE_t *spi)
{

/* USER CODE BEGIN (21) */
/* USER CODE END */

	uint32 index = spi == spiREG1 ? 0U :(spi==spiREG2 ? 1U : 2U);
	return(g_spiPacket_t[index].rx_data_status);
}

/* USER CODE BEGIN (22) */
/* USER CODE END */

/** @fn void spiEnableLoopback(spiBASE_t *spi, loopBackType_t Loopbacktype)
*   @brief Enable Loopback mode for self test
*   @param[in] spi        - spi module base address
*   @param[in] Loopbacktype  - Digital or Analog
*
*   This function enables the Loopback mode for self test.
*/
void spiEnableLoopback(spiBASE_t *spi, loopBackType_t Loopbacktype)
{
/* USER CODE BEGIN (23) */
/* USER CODE END */
    
    /* Clear Loopback incase enabled already */
    spi->IOLPKTSTCR = 0U;
    
    /* Enable Loopback either in Analog or Digital Mode */
    spi->IOLPKTSTCR = 0x00000A00U
                       | (Loopbacktype << 1U);
    
/* USER CODE BEGIN (24) */
/* USER CODE END */
}

/* USER CODE BEGIN (25) */
/* USER CODE END */

/** @fn void spiDisableLoopback(spiBASE_t *spi)
*   @brief Enable Loopback mode for self test
*   @param[in] spi        - spi module base address
*
*   This function disable the Loopback mode.
*/
void spiDisableLoopback(spiBASE_t *spi)
{
/* USER CODE BEGIN (26) */
/* USER CODE END */
    
    /* Disable Loopback Mode */
    spi->IOLPKTSTCR = 0x00000500U;
    
/* USER CODE BEGIN (27) */
/* USER CODE END */
}

/* USER CODE BEGIN (28) */
/* USER CODE END */

/** @fn spiEnableNotification(spiBASE_t *spi, uint32 flags)
*   @brief Enable interrupts
*   @param[in] spi   - spi module base address
*   @param[in] flags - Interrupts to be enabled, can be ored value of:
*/
void spiEnableNotification(spiBASE_t *spi, uint32 flags)
{
/* USER CODE BEGIN (29) */
/* USER CODE END */

    spi->INT0 = (spi->INT0 & 0xFFFF0000U) | flags;

/* USER CODE BEGIN (30) */
/* USER CODE END */
}

/* USER CODE BEGIN (31) */
/* USER CODE END */

/** @fn spiDisableNotification(spiBASE_t *spi, uint32 flags)
*   @brief Enable interrupts
*   @param[in] spi   - spi module base address
*   @param[in] flags - Interrupts to be enabled, can be ored value of:
*/
void spiDisableNotification(spiBASE_t *spi, uint32 flags)
{
/* USER CODE BEGIN (32) */
/* USER CODE END */

    spi->INT0 = (spi->INT0 & (~(flags)));

/* USER CODE BEGIN (33) */
/* USER CODE END */
}

/** @fn void spi1GetConfigValue(spi_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*	@param[in] *config_reg: pointer to the struct to which the initial or current 
*                           value of the configuration registers need to be stored
*	@param[in] type: 	whether initial or current value of the configuration registers need to be stored
*						- InitialValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*						- CurrentValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') 
*   of the configuration registers to the struct pointed by config_reg
*
*/

void spi1GetConfigValue(spi_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
        config_reg->CONFIG_GCR1  = SPI1_GCR1_CONFIGVALUE;
        config_reg->CONFIG_INT0  = SPI1_INT0_CONFIGVALUE;
        config_reg->CONFIG_LVL   = SPI1_LVL_CONFIGVALUE;
        config_reg->CONFIG_PC0   = SPI1_PC0_CONFIGVALUE;
        config_reg->CONFIG_PC1   = SPI1_PC1_CONFIGVALUE;
        config_reg->CONFIG_PC6   = SPI1_PC6_CONFIGVALUE;
        config_reg->CONFIG_PC7   = SPI1_PC7_CONFIGVALUE;
        config_reg->CONFIG_PC8   = SPI1_PC8_CONFIGVALUE;
        config_reg->CONFIG_DELAY = SPI1_DELAY_CONFIGVALUE;
        config_reg->CONFIG_FMT0  = SPI1_FMT0_CONFIGVALUE;
        config_reg->CONFIG_FMT1  = SPI1_FMT1_CONFIGVALUE;
        config_reg->CONFIG_FMT2  = SPI1_FMT2_CONFIGVALUE;
        config_reg->CONFIG_FMT3  = SPI1_FMT3_CONFIGVALUE;
	}
	else
	{
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Register read back support" */
        config_reg->CONFIG_GCR1  = spiREG1->GCR1;
        config_reg->CONFIG_INT0  = spiREG1->INT0;
        config_reg->CONFIG_LVL   = spiREG1->LVL;
        config_reg->CONFIG_PC0   = spiREG1->PC0;
        config_reg->CONFIG_PC1   = spiREG1->PC1;
        config_reg->CONFIG_PC6   = spiREG1->PC6;
        config_reg->CONFIG_PC7   = spiREG1->PC7;
        config_reg->CONFIG_PC8   = spiREG1->PC8;
        config_reg->CONFIG_DELAY = spiREG1->DELAY ;
        config_reg->CONFIG_FMT0  = spiREG1->FMT0;
        config_reg->CONFIG_FMT1  = spiREG1->FMT1;
        config_reg->CONFIG_FMT2  = spiREG1->FMT2;
        config_reg->CONFIG_FMT3  = spiREG1->FMT3;
	}
}






