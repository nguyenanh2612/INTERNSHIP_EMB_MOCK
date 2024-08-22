#ifndef LPSPI_H_
#define LPSPI_H_

#include <stdint.h>
#include "PCC.h"
#include "PORT.h"

enum CHANNEL
{
    CHANNEL0_SPI = 0, 
    CHANNEL1_SPI,
    CHANNEL2_SPI
};

enum RDR_BIT
{
    DATA_RDR = 0
};

enum RSR_BIT
{
    SOF = 0,                        /*Start Of Frame*/ 
    RXEMPTY                         /*RX FIFO Empty*/
};

enum TDR_BIT
{
    DATA_TDR = 0                        
};

enum TCR_BIT
{
    FRAMESZ = 0,                    /*Frame Size*/
    WIDTH = 16,                     /*Transfer Width*/
    TXMSK = 18,                     /*Transmit Data Mask*/
    RXMSK,                          /*Receive Data Mask*/
    CONTC,                          /*Continuing Command*/
    CONT,                           /*Continuous Transfer*/
    BYSW,                           /*Byte Swap*/
    LSBF,                           /*LSB First*/
    PCS_TCR = 24,                   /*Peripheral Chip Select*/
    PRESCALE = 27,                  /*Prescaler Value*/
    CPHA = 30,                      /*Clock Phase*/
    CPOL,                           /*Clock Polarity*/
};

enum FSR_BIT
{
    TXCOUNT = 0,                    /*Transmit FIFO Count*/
    RXCOUNT = 16                    /*Receive FIFO Count*/
};  

enum FCR_BIT
{
    TXWATER_SPI = 0,                    /*Transmit FIFO Watermark*/
    RXWATER_SPI = 16                    /*Receive FIFO Watermark*/
};

enum CCR_BIT
{
    SCKDIV = 0,                     /*SCK Divider*/
    DBT = 8,                        /*Delay Between Transfers*/
    PCSSCK = 16,                    /*PCS-to-SCK Delay*/
    SCKPCS = 24                     /*SCK-to-PCS Delay*/
};

enum DMR_BIT
{
    DMR0 = 0,                       /*Match 0 value*/
    DMR1 = 0                        /*Match 1 value*/
};

enum CFGR1_BIT
{
    MASTER = 0,                     /*Master Mode*/
    SAMPLE,                         /*Sample Point*/
    AUTOPCS,                        /*Automatic PCS*/
    NOSTALL,                        /*No Stall*/
    PCSPOL = 8,                     /*Peripheral Chip Select Polarity*/
    MATCFG_SPI = 16,                    /*Match Configuration*/
    PINCFG = 24,                    /*Pin Configuration*/
    OUTCFG = 26,                    /*Output Configuration*/
    PCSCFG                          /*Peripheral Chip Select Configuration*/
};

enum CFGGR0_BIT
{
    HREN = 0,                       /*Host Request Enable*/
    HRPOL,                          /*Host Request Polarity*/
    HRSEL,                          /*Host Request Select*/
    CIRFIFO = 8,                    /*Circular FIFO Enable*/
    RDMO                            /*Receive Data Match Only*/
};

enum DER_BIT
{
    TDDE = 0,                       /*Transmit Data DMA Enable*/
    RDDE                            /*Receive Data DMA Enable*/
};

enum IER_BIT
{
    TDIE = 0,                       /*Transmit Data Interrupt Enable*/
    RDIE,                           /*Receive Data Interrupt Enable*/
    WCIE = 8,                       /*Word Complete Interrupt Enable*/
    FCIE,                           /*Frame Complete Interrupt Enable*/
    TCIE_SPI,                           /*Transfer Complete Interrupt Enable*/
    TEIE,                           /*Transmit Error Interrupt Enable*/
    REIE,                           /*Receive Error Interrupt Enable*/
    DMIE                            /*Data Match Interrupt Enable*/
};

enum SR_BIT
{
    TDF =0,                         /*Transmit Data Flag*/
    RDF,                            /*Receive Data Flag*/
    WCF = 8,                        /*Word Complete Flag*/
    FCF,                            /*Frame Complete Flag*/
    TCF,                            /*Transfer Complete Flag*/
    TEF,                            /*Transmit Error Flag*/
    REF,                            /*Receive Error Flag*/
    DMF,                            /*Data Match Flag*/
    MBF = 24                        /*Module Busy Flag*/
};

enum CR_BIT
{
    MEN = 0,                        /*Module Enable*/
    RST,                            /*Software Reset*/
    DOZEN,                          /*Doze Mode Enable*/                
    DBGEN,                          /*Debug Enable*/
    RTF = 8,                        /*Reset Transmit FIFO*/
    RRF                             /*Reset Receive FIFO*/
}; 

typedef struct 
{
    /*Version ID Register */
    volatile uint32_t   VERID; 

    /*Parameter Register */
    volatile uint32_t   PARAM; 

    /*Dummy data*/
    volatile uint32_t   RESERVED_0[2];

    /*Control Register  */
    volatile uint32_t   CR;

    /*Status Register */
    volatile uint32_t   SR;

    /*Interrupt Enable Register*/
    volatile uint32_t   IER;
    
    /*DMA Enable Register */
    volatile uint32_t   DER;

    /*Configuration Register 0 */
    volatile uint32_t   CFGR0;

    /*Configuration Register 1*/
    volatile uint32_t   CFGR1;

    /*Dummy data*/
    volatile uint32_t   RESERVED_1[2];

    /*Data Match Register 0*/
    volatile uint32_t   DMR0;
    
    /*Data Match Register 1*/
    volatile uint32_t   DMR1;

    /*Dummy data*/
    volatile uint32_t   RESERVED_2[2];

    /*Clock Configuration Register*/
    volatile uint32_t   CCR;

    /*Dummy data*/
    volatile uint32_t   RESERVED_3[5];

    /*FIFO Control Register*/
    volatile uint32_t   FCR;

    /*FIFO Status Register */
    volatile uint32_t   FSR;

    /*Transmit Command Register*/
    volatile uint32_t   TCR;

    /*Transmit Data Register */
    volatile uint32_t   TDR;

    /*Dummy data*/
    volatile uint32_t   RESERVED_4[2];

    /*Receive Status Register*/
    volatile uint32_t   RSR;

    /*Receive Data Register*/
    volatile uint32_t   RDR; 
}LPSPI_TYPE ;

#define LPSPI0_BASE_ADDR   (0x4002C000)
#define LPSPI0             ((LPSPI_TYPE*) LPSPI0_BASE_ADDR)

#define LPSPI1_BASE_ADDR   (0x4002D000)
#define LPSPI1             ((LPSPI_TYPE*) LPSPI1_BASE_ADDR)

#define LPSPI2_BASE_ADDR   (0x4002E000)
#define LPSPI2             ((LPSPI_TYPE*) LPSPI2_BASE_ADDR)

/**
 * @brief Configures and enables the Peripheral Clock Control (PCC) for a specified SPI channel.
 * 
 * This function sets up the clock source and enables the Peripheral Clock Control (PCC) for the specified
 * SPI channel. It configures the appropriate pins for the SPI functionality based on the channel, and
 * sets the clock source for the SPI module.
 * 
 * @param channel The SPI channel to be configured. This should be one of the predefined SPI channel constants:
 *        - `CHANNEL0_SPI`
 *        - `CHANNEL1_SPI`
 *        - `CHANNEL2_SPI`
 * @param clockSource The clock source to be used for the SPI module. This value is used to select the clock
 *        source from the available options.
 * 
 * @note The function configures the appropriate port and pin multiplexers for SPI functionality based on the
 *       selected channel. It also enables the clock for the specified SPI channel by setting the appropriate
 *       bits in the PCC register.
 * 
 * @see CHANNEL0_SPI
 * @see CHANNEL1_SPI
 * @see CHANNEL2_SPI
 * @see PCC
 * @see PORT
 * @see SPI
 */
void enable_pcc_spi(int channel, unsigned int clockSource); 

/**
 * @brief Initializes the SPI module in master mode for the specified SPI channel.
 * 
 * This function configures and enables the SPI module in master mode for the selected SPI channel. 
 * It sets up the SPI module's control registers, interrupt, DMA, and configuration settings for master operation.
 * 
 * @param channel The SPI channel to be initialized. This should be one of the predefined SPI channel constants:
 *        - `CHANNEL0_SPI`
 *        - `CHANNEL1_SPI`
 *        - `CHANNEL2_SPI`
 * 
 * @note The function performs the following configurations:
 *       - Disables the SPI module for configuration.
 *       - Disables interrupts and DMA.
 *       - Configures the SPI module for master mode.
 *       - Sets the frame size, data order, and clock settings.
 *       - Enables the SPI module for operation.
 * 
 * @note The configuration settings include:
 *       - Frame size of 16 bits.
 *       - No stall if Tx FIFO is empty or Rx FIFO is full.
 *       - Data is transferred MSB first.
 *       - Clock polarity (CPOL) and phase (CPHA) are set to 0.
 *       - Prescale of functional clock by 1.
 * 
 * @see CHANNEL0_SPI
 * @see CHANNEL1_SPI
 * @see CHANNEL2_SPI
 * @see LPSPI
 */
void spi_init_master(int channel); 

/**
 * @brief Transmits data over the specified SPI channel.
 * 
 * This function transmits a 16-bit data frame over the selected SPI channel. The data frame is composed of an 8-bit address
 * followed by an 8-bit data value. The function waits for the Transmit Data FIFO (TDF) to be empty before loading the data into
 * the Transmit Data Register (TDR).
 * 
 * @param channel The SPI channel to use for transmission. This should be one of the predefined SPI channel constants:
 *        - `CHANNEL0_SPI`
 *        - `CHANNEL1_SPI`
 *        - `CHANNEL2_SPI`
 * @param address The 8-bit address to be transmitted.
 * @param data The 8-bit data to be transmitted.
 * 
 * @note The function performs the following actions:
 *       - Waits until the Transmit Data FIFO (TDF) is empty.
 *       - Loads the 16-bit data frame (address and data) into the Transmit Data Register (TDR) of the selected SPI channel.
 * 
 * @see CHANNEL0_SPI
 * @see CHANNEL1_SPI
 * @see CHANNEL2_SPI
 * @see LPSPI
 */
void spi_transmit(int channel,uint8_t address,uint8_t data);

/**
 * @brief Receives data from the specified SPI channel.
 * 
 * This function reads a 16-bit data frame from the selected SPI channel. The function waits until the Receive Data FIFO (RDF)
 * is full before reading the data from the Receive Data Register (RDR). After reading the data, it clears the Receive Data Flag (RDF).
 * 
 * @param channel The SPI channel to use for reception. This should be one of the predefined SPI channel constants:
 *        - `CHANNEL0_SPI`
 *        - `CHANNEL1_SPI`
 *        - `CHANNEL2_SPI`
 * 
 * @return The received 16-bit data frame from the SPI channel. This includes both the address and data that were received.
 * 
 * @note The function performs the following actions:
 *       - Waits until the Receive Data FIFO (RDF) is full.
 *       - Reads the 16-bit data frame from the Receive Data Register (RDR) of the selected SPI channel.
 *       - Clears the Receive Data Flag (RDF).
 * 
 * @see CHANNEL0_SPI
 * @see CHANNEL1_SPI
 * @see CHANNEL2_SPI
 * @see LPSPI
 */
uint16_t spi_receive(int channel);
#endif