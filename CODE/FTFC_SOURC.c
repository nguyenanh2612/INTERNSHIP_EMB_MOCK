#include "FTFC.h"
#include "PCC.h"

void clear_error_flash(void)
{
		/*Wait previous command complete*/
    while(~(*FTFC).FSTAT & (1u << CCIF)) 
    {}
		
		/*Clear protec violation error*/
    if ( (*FTFC).FSTAT & (1u << FPVIOL))
    {
        (*FTFC).FSTAT |= (1u << FPVIOL);
    }
	
		/*Clear access error*/
    if ( (*FTFC).FSTAT & (1u << ACCERR))
    {
        (*FTFC).FSTAT |= (1u << ACCERR);
    }
}

void program_partition(void)
{
    clear_error_flash(); 
		/*Send command partition*/
    (*FTFC).FCCOB0 = PGMPART; 
    (*FTFC).FCCOB1 = 0x00; 
    (*FTFC).FCCOB2 = 0x00; 
    (*FTFC).FCCOB3 = 0x00; 
	
		/*set data size code */
    (*FTFC).FCCOB4 = 0x02;

		/*set data flash and eeprom back up size*/
    (*FTFC).FCCOB5 = 0x03; 

		/*CLear flag*/
    (*FTFC).FSTAT |= (1u << CCIF);

    /*wait completetion*/
    while (!((*FTFC).FSTAT & (1u << CCIF))); 
    
}

void set_flexram_to_emulated_eeprom(void)
{
    clear_error_flash(); 
		/*Send command set flexRam*/
    (*FTFC).FCCOB0 = SETRAM; 
		/*Make FlexRAM available for emulated EEPROM*/
    (*FTFC).FCCOB1 = 0x00; 

    /*CLear flag*/
    (*FTFC).FSTAT |= (1u << CCIF);

    /*wait completetion*/
    while (!((*FTFC).FSTAT & (1u << CCIF))); 
}   

void clear_command_block_eeprom(void)
{
    clear_error_flash();
    (*FTFC).FCCOB0 = ERALL; 

    /*CLear flag*/
    (*FTFC).FSTAT |= (1u << CCIF);

    /*wait completetion*/
    while (!((*FTFC).FSTAT & (1u << CCIF))); 
}

void write_char(uint32_t *address, uint32_t data)
{
    while(~(*FTFC).FSTAT & (1u << CCIF))
    {}

    *address = data;
}

void read_char(uint32_t *address, uint32_t *data)
{
    while(~(*FTFC).FSTAT & (1u << CCIF))
    {}

    *data = *address; 
}

void write_date_to_flash(char date[8])
{
	uint32_t data[2]; // Buffer to hold data to be written

  /* Convert date array to two 32-bit values*/
  data[0] = (date[0] << 24) | (date[1] << 16) | (date[2] << 8) | date[3];
  data[1] = (date[4] << 24) | (date[5] << 16) | (date[6] << 8) | date[7];
	
	uint32_t flash_address_date = FLASH_DATE_START_ADDRESS; 
	
	// Write data to flash
    for (int i = 0; i < 2; i++) 
    {
        // Program flash
        write_char((uint32_t *) flash_address_date, data[i]);

        // Increment address
        flash_address_date += 4;
    }

}

void write_time_to_flash(char time[6])
{
	uint32_t data[2]; // Buffer to hold data to be written

    // Convert time array to two 32-bit values
    data[0] = (time[0] << 24) | (time[1] << 16) | (time[2] << 8) | time[3];
    data[1] = (time[4] << 24) | (time[5] << 16) | 0x00; // Time is 6 bytes, so last byte is zero
	
	  uint32_t flash_address_time = FLASH_TIME_START_ADDRESS;

    // Write data to flash
    for (int i = 0; i < 2; i++) 
    {
        // Program flash
        write_char((uint32_t *)flash_address_time, data[i]);

        // Increment address
        flash_address_time += 4;
    }
}

void read_date_from_flash(char date[8])
{
    uint32_t data[2]; // Buffer to hold data read from flash
    uint32_t flash_address_date = FLASH_DATE_START_ADDRESS;

    // Read data from flash
    for (int i = 0; i < 2; i++) 
    {
        // Read flash
        read_char((uint32_t *)flash_address_date, &data[i]);

        // Increment address
        flash_address_date += 4;
    }

    // Convert the two 32-bit values to an 8-byte date array
    date[0] = (data[0] >> 24) & 0xFF;
    date[1] = (data[0] >> 16) & 0xFF;
    date[2] = (data[0] >> 8) & 0xFF;
    date[3] = data[0] & 0xFF;
    date[4] = (data[1] >> 24) & 0xFF;
    date[5] = (data[1] >> 16) & 0xFF;
    date[6] = (data[1] >> 8) & 0xFF;
    date[7] = data[1] & 0xFF;
		
		for(int j = 0;  j < 8; j++)
		{
			if (date[j] < '0' || date[j] > '9')
			{
				memset(date, '0', 8); 
				break; 
			}
		}
}

void read_time_from_flash(char time[6])
{
    uint32_t data[2]; // Buffer to hold data read from flash
    uint32_t flash_address_time = FLASH_TIME_START_ADDRESS;

    // Read data from flash
    for (int i = 0; i < 2; i++) 
    {
        // Read flash
        read_char((uint32_t *)flash_address_time, &data[i]);

        // Increment address
        flash_address_time += 4;
    }

    // Convert the two 32-bit values to a 6-byte time array
    time[0] = (data[0] >> 24) & 0xFF;
    time[1] = (data[0] >> 16) & 0xFF;
    time[2] = (data[0] >> 8) & 0xFF;
    time[3] = data[0] & 0xFF;
    time[4] = (data[1] >> 24) & 0xFF;
    time[5] = (data[1] >> 16) & 0xFF;
		
	for(int j = 0;  j < 6; j++)
	{
		if (time[j] < '0' || time[j] > '9')
		{
			memset(time, '0', 6); 
			break; 
		}
	}
}

void write_time_alarm_to_flash(char time[6])
{
    uint32_t data[2]; // Buffer to hold data to be written

    // Convert time array to two 32-bit values
    data[0] = (time[0] << 24) | (time[1] << 16) | (time[2] << 8) | time[3];
    data[1] = (time[4] << 24) | (time[5] << 16) | 0x00; // Time is 6 bytes, so last byte is zero
	
	uint32_t flash_address_time = FLASH_TIME_ALARM_START_ADDRESS;

    // Write data to flash
    for (int i = 0; i < 2; i++) 
    {
        // Program flash
        write_char((uint32_t *)flash_address_time, data[i]);

        // Increment address
        flash_address_time += 4;
    }
}

void read_time_alarm_from_flash(char time[6])
{
    uint32_t data[2]; // Buffer to hold data read from flash
    uint32_t flash_address_time = FLASH_TIME_ALARM_START_ADDRESS;

    // Read data from flash
    for (int i = 0; i < 2; i++) 
    {
        // Read flash
        read_char((uint32_t *)flash_address_time, &data[i]);

        // Increment address
        flash_address_time += 4;
    }

    // Convert the two 32-bit values to a 6-byte time array
    time[0] = (data[0] >> 24) & 0xFF;
    time[1] = (data[0] >> 16) & 0xFF;
    time[2] = (data[0] >> 8) & 0xFF;
    time[3] = data[0] & 0xFF;
    time[4] = (data[1] >> 24) & 0xFF;
    time[5] = (data[1] >> 16) & 0xFF;
		
	for(int j = 0;  j < 6; j++)
	{
		if (time[j] < '0' || time[j] > '9')
		{
			memset(time, '0', 6); 
			break; 
		}
	}
}