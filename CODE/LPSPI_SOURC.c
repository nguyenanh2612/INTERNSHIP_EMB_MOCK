#include "LPSPI.h"

void enable_pcc_spi(int channel,unsigned int clockSource)
{
    switch (channel)
    {
    case CHANNEL0_SPI: 
    {
        enable_PCC_PORT('B');
        enable_PCC_PORT('A');
        (*PORTA).PORT_PCR[15]|= (ALTERNATIVE3 << MUX);          /*MUX: ALT3, PCS*/
        (*PORTB).PORT_PCR[2]|= (ALTERNATIVE3 << MUX);           /*MUX: ALT3, SCK*/
        (*PORTB).PORT_PCR[3]|= (ALTERNATIVE3 << MUX);           /*MUX: ALT3, SIN*/
        (*PORTB).PORT_PCR[1]|= (ALTERNATIVE3 << MUX);           /*MUX: ALT3, SOUT*/

        (*PCC).PCC_LPSPI0 |= (1U << CGC) | (clockSource << PCS_PCC); 
        break;
    }
    case CHANNEL1_SPI: 
    {
        enable_PCC_PORT('B');
        (*PORTB).PORT_PCR[17]|= (ALTERNATIVE3 << MUX);           /*MUX: ALT3, PCS*/
        (*PORTB).PORT_PCR[14]|= (ALTERNATIVE3 << MUX);           /*MUX: ALT3, SCK*/
        (*PORTB).PORT_PCR[15]|= (ALTERNATIVE3 << MUX);           /*MUX: ALT3, SIN*/
        (*PORTB).PORT_PCR[16]|= (ALTERNATIVE3 << MUX);           /*MUX: ALT3, SOUT*/

        (*PCC).PCC_LPSPI1 |= (1 << CGC) | (clockSource << PCS_PCC);
        break;
    }
    case CHANNEL2_SPI:
    {
        enable_PCC_PORT('C');
        enable_PCC_PORT('E');
        (*PORTE).PORT_PCR[13]|= (ALTERNATIVE3 << MUX);           /*MUX: ALT3, PCS*/
        (*PORTC).PORT_PCR[15]|= (ALTERNATIVE3 << MUX);           /*MUX: ALT3, SCK*/
        (*PORTC).PORT_PCR[0]|= (ALTERNATIVE3 << MUX);            /*MUX: ALT3, SIN*/
        (*PORTC).PORT_PCR[1]|= (ALTERNATIVE3 << MUX);            /*MUX: ALT3, SOUT*/

        (*PCC).PCC_LPSPI2 |= (1 << CGC) | (clockSource << PCS_PCC);
        break;
    }
    default:
        break;
    }
}

void spi_init_master(int channel)
{
    switch (channel)
    {
    case CHANNEL0_SPI:
    {
        (*LPSPI0).CR = 0;                           /* Disable module for configuration */

        (*LPSPI0).IER = 0;                          /* Interrupts disable */

        (*LPSPI0).DER = 0;                          /* DMA disable */

        (*LPSPI0).CFGR0 = 0;                        /* Defaults: */
                                                    /* RDM0=0: rec'd data to FIFO as normal */
                                                    /* CIRFIFO=0; Circular FIFO is disabled */
                                                    /* HRSEL, HRPOL, HREN=0: Host request disabled */

        /* Configurations: master mode*/
        (*LPSPI0).CFGR1 |= (1u << MASTER)           /*MASTER = 1: Master mode*/
                        | (1u << NOSTALL);          /*NOSTALL = 1: No stall if Tx FIFO empty or Rx FIFO full*/
                                                    /* PCSCFG=0: PCS[3:2] are enabled */
                                                    /* OUTCFG=0: Output data retains last value when CS negated */
                                                    /* PINCFG=0: SIN is input, SOUT is output */
                                                    /* MATCFG=0: Match disabled */
                                                    /* PCSPOL=0: PCS is active low */
                                                    /* AUTOPCS=0: does not apply for master mode */
                                                    /* SAMPLE=0: input data sampled on SCK edge */
		
        /* Transmit cmd: PCS3, 16bits, prescale func'l clk by 1. */
        (*LPSPI0).TCR = 0x00000000; 
		uint32_t temp = (15u << FRAMESZ) | (3u << PCS_TCR);
        (*LPSPI0).TCR = temp;                       /* CPOL=0: SCK inactive state is low */
                                                    /* CPHA=0: Change data on SCK lead'g, capture on lead'g edge*/
                                                    /* PRESCALE=0: Functional clock divided by 0**2 = 1 */
                                                    /* PCS=3: Transfer using PCS3 */
                                                    /* LSBF=0: Data is transferred MSB first */
                                                    /* BYSW=0: Byte swap disabled */
                                                    /* CONT, CONTC=0: Continuous transfer disabled */
                                                    /* RXMSK=0: Normal transfer: rx data stored in rx FIFO */
                                                    /* TXMSK=0: Normal transfer: data loaded from tx FIFO */
                                                    /* WIDTH=0: Single bit transfer */
                                                    /* FRAMESZ=15: # bits in frame = 15+1=16 */

        (*LPSPI0).CCR |= (0u << SCKPCS) | (1u << PCSSCK) | (0u << DBT) | (1u << SCKDIV);

        (*LPSPI0).FCR |= (3u << TXWATER_SPI);           /* RXWATER=0: Rx flags set when Rx FIFO >0 */
                                                    /* TXWATER=3: Tx flags set when Tx FIFO <= 3 */
        /* Enable module for operation */
        (*LPSPI0).CR  |= (1u << DBGEN)              /* DBGEN=1: module enabled in debug mode */
                      | (1u << MEN);                /* MEN=1: Module is enabled */
                                                    /* DOZEN=0: module enabled in Doze mode */
                                                    /* RST=0: Master logic not reset */
        break; 
    } 
    case CHANNEL1_SPI: 
    {
        (*LPSPI1).CR = 0;                           /* Disable module for configuration */

        (*LPSPI1).IER = 0;                          /* Interrupts disable */

        (*LPSPI1).DER = 0;                          /* DMA disable */

        (*LPSPI1).CFGR0 = 0;                        /* Defaults: */
                                                    /* RDM0=0: rec'd data to FIFO as normal */
                                                    /* CIRFIFO=0; Circular FIFO is disabled */
                                                    /* HRSEL, HRPOL, HREN=0: Host request disabled */

        /* Configurations: master mode*/
        (*LPSPI1).CFGR1 |= (1u << MASTER)           /*MASTER = 1: Master mode*/
                        | (1u << NOSTALL);          /*NOSTALL = 1: No stall if Tx FIFO empty or Rx FIFO full*/
                                                    /* PCSCFG=0: PCS[3:2] are enabled */
                                                    /* OUTCFG=0: Output data retains last value when CS negated */
                                                    /* PINCFG=0: SIN is input, SOUT is output */
                                                    /* MATCFG=0: Match disabled */
                                                    /* PCSPOL=0: PCS is active low */
                                                    /* AUTOPCS=0: does not apply for master mode */
                                                    /* SAMPLE=0: input data sampled on SCK edge */
		
        /* Transmit cmd: PCS3, 16bits, prescale func'l clk by 1. */
        (*LPSPI1).TCR = 0x00000000; 
		uint32_t temp = (15u << FRAMESZ) | (3u << PCS_TCR);
        (*LPSPI1).TCR = temp;                       /* CPOL=0: SCK inactive state is low */
                                                    /* CPHA=0: Change data on SCK lead'g, capture on lead'g edge*/
                                                    /* PRESCALE=0: Functional clock divided by 0**2 = 1 */
                                                    /* PCS=3: Transfer using PCS3 */
                                                    /* LSBF=0: Data is transferred MSB first */
                                                    /* BYSW=0: Byte swap disabled */
                                                    /* CONT, CONTC=0: Continuous transfer disabled */
                                                    /* RXMSK=0: Normal transfer: rx data stored in rx FIFO */
                                                    /* TXMSK=0: Normal transfer: data loaded from tx FIFO */
                                                    /* WIDTH=0: Single bit transfer */
                                                    /* FRAMESZ=15: # bits in frame = 15+1=16 */

        (*LPSPI1).CCR |= (0u << SCKPCS) | (1u << PCSSCK) | (0u << DBT) | (0u << SCKDIV);

        (*LPSPI1).FCR |= (3u << TXWATER_SPI);           /* RXWATER=0: Rx flags set when Rx FIFO >0 */
                                                    /* TXWATER=3: Tx flags set when Tx FIFO <= 3 */
        /* Enable module for operation */
        (*LPSPI1).CR  |= (1u << DBGEN)              /* DBGEN=1: module enabled in debug mode */
                      | (1u << MEN);                /* MEN=1: Module is enabled */
                                                    /* DOZEN=0: module enabled in Doze mode */
                                                    /* RST=0: Master logic not reset */
        break; 
    }
    case CHANNEL2_SPI:
    {
        {
        (*LPSPI2).CR = 0;                           /* Disable module for configuration */

        (*LPSPI2).IER = 0;                          /* Interrupts disable */

        (*LPSPI2).DER = 0;                          /* DMA disable */

        (*LPSPI2).CFGR0 = 0;                        /* Defaults: */
                                                    /* RDM0=0: rec'd data to FIFO as normal */
                                                    /* CIRFIFO=0; Circular FIFO is disabled */
                                                    /* HRSEL, HRPOL, HREN=0: Host request disabled */

        /* Configurations: master mode*/
        (*LPSPI2).CFGR1 |= (1u << MASTER)           /*MASTER = 1: Master mode*/
                        | (1u << NOSTALL);          /*NOSTALL = 1: No stall if Tx FIFO empty or Rx FIFO full*/
                                                    /* PCSCFG=0: PCS[3:2] are enabled */
                                                    /* OUTCFG=0: Output data retains last value when CS negated */
                                                    /* PINCFG=0: SIN is input, SOUT is output */
                                                    /* MATCFG=0: Match disabled */
                                                    /* PCSPOL=0: PCS is active low */
                                                    /* AUTOPCS=0: does not apply for master mode */
                                                    /* SAMPLE=0: input data sampled on SCK edge */
		
        /* Transmit cmd: PCS3, 16bits, prescale func'l clk by 1. */
        (*LPSPI2).TCR = 0x00000000; 
		uint32_t temp = (15u << FRAMESZ) | (3u << PCS_TCR);
        (*LPSPI2).TCR = temp;                       /* CPOL=0: SCK inactive state is low */
                                                    /* CPHA=0: Change data on SCK lead'g, capture on lead'g edge*/
                                                    /* PRESCALE=0: Functional clock divided by 0**2 = 1 */
                                                    /* PCS=3: Transfer using PCS3 */
                                                    /* LSBF=0: Data is transferred MSB first */
                                                    /* BYSW=0: Byte swap disabled */
                                                    /* CONT, CONTC=0: Continuous transfer disabled */
                                                    /* RXMSK=0: Normal transfer: rx data stored in rx FIFO */
                                                    /* TXMSK=0: Normal transfer: data loaded from tx FIFO */
                                                    /* WIDTH=0: Single bit transfer */
                                                    /* FRAMESZ=15: # bits in frame = 15+1=16 */

        (*LPSPI2).CCR |= (0u << SCKPCS) | (1u << PCSSCK) | (0u << DBT) | (1u << SCKDIV);

        (*LPSPI2).FCR |= (3u << TXWATER_SPI);           /* RXWATER=0: Rx flags set when Rx FIFO >0 */
                                                    /* TXWATER=3: Tx flags set when Tx FIFO <= 3 */
        /* Enable module for operation */
        (*LPSPI2).CR  |= (1u << DBGEN)              /* DBGEN=1: module enabled in debug mode */
                      | (1u << MEN);                /* MEN=1: Module is enabled */
                                                    /* DOZEN=0: module enabled in Doze mode */
                                                    /* RST=0: Master logic not reset */
        break; 
    }
    }
    default:
        break;
    }
}

void spi_transmit(int channel, uint8_t address,uint8_t data )
{
	uint16_t send; 
	send = (address << 8u) | data; 
    switch (channel)
    {
    case CHANNEL0_SPI: 
    {
        while ((*LPSPI0).SR && (1u << TDF) == 0)
        {}
        
        (*LPSPI0).TDR = send;

        break;
    }
    case CHANNEL1_SPI: 
    {
        while ((*LPSPI1).SR && (1u << TDF) == 0)
        {}
        
        (*LPSPI1).TDR = send;

        break;
    }
    case CHANNEL2_SPI: 
    {
        while ((*LPSPI1).SR && (1u << TDF) == 0)
        {}
        
        (*LPSPI1).TDR = send;

        break; 
    }
    default:
        break;
    }
}

uint16_t spi_receive(int channel)
{
    uint16_t receive = 0; 
    
    switch (channel)
    {
    case CHANNEL0_SPI:
    {
        while ((*LPSPI0).SR && (1u << RDF) == 0)
        {}
        
        receive = (*LPSPI0).RDR;

        (*LPSPI0).SR |= (1u << RDF); 

        break; 
    } 
    case CHANNEL1_SPI: 
    {
        while ((*LPSPI1).SR && (1u << RDF) == 0)
        {}
        
        receive = (*LPSPI1).RDR;

        (*LPSPI1).SR |= (1u << RDF);

        break; 
    }
    case CHANNEL2_SPI:
    {
        while ((*LPSPI2).SR && (1u << RDF) == 0)
        {}
        
        receive = (*LPSPI2).RDR;

        (*LPSPI2).SR |= (1u << RDF);

        break; 
    }
    default:
        break;
    }

    return receive; 
}
