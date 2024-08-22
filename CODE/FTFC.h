#ifndef FTFC_H_
#define FTFC_H_

#include <stdint.h>
#include <string.h>

enum FERCNFG_BIT
{
    DFDIE = 1,                         /*Double Bit Fault Detect Interrupt Enable*/
    FDFD = 5                           /*Force Double Bit Fault Detect*/
};

enum FERSTAT_BIT
{
    DFDIF = 1                          /*Double Bit Fault Detect Interrupt Flag*/
};

enum FCSESTAT_BIT
{
    BSY = 0,                           /*Busy*/
    SB,                                /*Secure Boot*/
    BIN,                               /*Secure Boot Initialization*/
    BFN,                               /*Secure Boot Finished*/
    BOK,                               /*Secure Boot OK*/
    RIN,                               /*Random Number Generator Initialized*/
    EDB,                               /*External Debug*/
    IDB                                /*Internal Debug*/
};

enum FDPROT_BIT
{
    DPROT = 0                           /*Data Flash Region Protect*/
};

enum FEPROT_BIT
{
    EPROT = 0                           /*EEPROM Region Protect*/
};

enum FPROT_BIT
{
    PROT = 0                           /*Program Flash Region Protect*/
};

enum FCCOB_BIT
{
    CCOBn = 0                          /*CCOBn*/
};

enum FOPT_BIT
{
    OPT = 0                            /*Nonvolatile Option*/
}; 

enum FSEC_BIT
{
    SEC = 0,                           /*Flash Security*/
    FSLACC = 2,                        /*Factory Failure Analysis Access Code*/
    MEEN = 4,                          /*Mass Erase Enable Bits*/
    KEYEN = 6                          /*Backdoor Key Security Enable*/
};

enum FCNFG_BIT
{
    EEERDY = 0,                        /*This flag indicates if the EEPROM backup data has been copied to the FlexRAM and is therefore available for read access*/
    RAMRDY,                            /*RAM Ready*/
    ERSSUSP = 4,                       /*Erase Suspend*/
    ERSAREQ,                           /*Erase All Request*/
    RDCOLLIE,                          /*Read Collision Error Interrupt Enable*/
    CCIE                               /*Command Complete Interrupt Enable*/
};

enum FSTAT_BIT
{
    MGSTAT0 = 0,                       /*Memory Controller Command Completion Status Flag*/
    FPVIOL = 4,                        /*Flash Protection Violation Flag*/
    ACCERR,                            /*Flash Access Error Flag*/
    RDCOLERR,                          /*FTFC Read Collision Error Flag*/
    CCIF                               /*Command Complete Interrupt Flag*/
}; 

typedef struct
{
    /*Flash Status Register*/
    volatile uint8_t FSTAT; 

    /*Flash Configuration Register*/
    volatile uint8_t FCNFG;

    /*Flash Security Register*/
    volatile uint8_t FSEC;

    /*Flash Option Register*/
    volatile uint8_t FOPT;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOB3;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOB2;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOB1;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOB0;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOB7;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOB6;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOB5;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOB4;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOBB;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOBA;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOB9;

    /*Flash Common Command Object Registers */
    volatile uint8_t FCCOB8;

    /*Program Flash Protection Registers*/
    volatile uint8_t FPROT3;

    /*Program Flash Protection Registers*/
    volatile uint8_t FPROT2;

    /*Program Flash Protection Registers*/
    volatile uint8_t FPROT1;

    /*Program Flash Protection Registers*/
    volatile uint8_t FPROT0;

    /*Dummy data*/
    volatile uint8_t RESERVED_0[2];

    /*EEPROM Protection Register*/
    volatile uint8_t FEPROT;

    /*Data Flash Protection Register*/
    volatile uint8_t FDPROT;

    /*Dummy data*/
    volatile uint8_t RESERVED_1[20];

    /*Flash CSEc Status Register */
    volatile uint8_t FCSESTAT; 

    /*Dummy data*/
    volatile uint8_t RESERVED_2;

    /*Flash Error Status Register*/
    volatile uint8_t FERSTAT;

    /*Flash Error Configuration Register*/
    volatile uint8_t FERCNFG;
}FTFC_REGISTER; 

#define FTFC_BASE_ADDR      (0x40020000)
#define FTFC                ((FTFC_REGISTER*) FTFC_BASE_ADDR)

#define FLASH_DATE_START_ADDRESS 						(uint32_t) (0x14000000)
#define FLASH_TIME_START_ADDRESS 						(uint32_t) (0x14000008)
#define FLASH_DATE_ALARM_START_ADDRESS 					(uint32_t) (0x14000010)
#define FLASH_TIME_ALARM_START_ADDRESS 					(uint32_t) (0x14000018)

/**
 * @def SETRAM
 * @brief Command code to set the RAM for FTFC operations.
 *
 * This command is used to set up the RAM for specific FTFC operations.
 * The value `0x81` is the command code for setting the RAM.
 */
#define SETRAM                  0X81

/**
 * @def PGMPART
 * @brief Command code to program the partition for FTFC.
 *
 * This command is used to program the partition for the FTFC module.
 * The value `0x80` is the command code for programming the partition.
 */
#define PGMPART                 0X80

/**
 * @def ERALL
 * @brief FTFC (Flash Memory) command code for erasing all blocks.
 *
 * This define represents the command code `0x44` used in the FTFC module
 * of the S32K144 microcontroller to erase all blocks of flash memory.
 */
#define ERALL                   0x44

/**
 * @def FTFC_OK
 * @brief Indicates a successful FTFC operation.
 *
 * This value is returned by FTFC functions to indicate that the operation
 * was completed successfully. The value `0x01` signifies success.
 */
#define FTFC_OK 			    0x01 

/**
 * @def FTFC_ERROR
 * @brief Indicates a failed FTFC operation.
 *
 * This value is returned by FTFC functions to indicate that an error occurred
 * during the operation. The value `0x00` signifies an error.
 */
#define FTFC_ERROR 				0x00 

/**
 * @brief Clears flash error flags in the FTFC module.
 *
 * This function clears any flash protection violation (FPVIOL) and access error (ACCERR) flags 
 * in the FTFC module by checking the status and then writing to the FSTAT register to clear them.
 * The function first waits for any ongoing command to complete by monitoring the Command Complete Interrupt Flag (CCIF).
 *
 * @note This function should be called after a flash operation to ensure that any errors are cleared.
 */
void clear_error_flash(void); 

/**
 * @brief Programs the partition for the FTFC module.
 *
 * This function programs the partition of the FTFC (Flash Memory) module. It first clears any 
 * existing flash errors, then sets up the FCCOB registers with the appropriate command and parameters 
 * to program the partition. The function waits for the operation to complete before returning.
 *
 * @note The partitioning operation is critical and should be handled carefully to avoid unintended 
 * modifications to the flash memory.
 */
void program_partition(void); 

/**
 * @brief Sets FlexRAM to emulate EEPROM.
 *
 * This function clears any existing flash errors, sets the appropriate commands 
 * for the FlexRAM to operate as emulated EEPROM, and waits for the operation to complete.
 */
void set_flexram_to_emulated_eeprom(void); 

/**
 * @brief Clears the command block in the EEPROM using the FTFC module.
 *
 * This function initiates a command to erase all blocks in the EEPROM 
 * by setting the appropriate FTFC registers on the S32K144 microcontroller.
 */
void clear_command_block_eeprom(void); 


/**
 * @brief Writes a character to a specific address in flash memory.
 *
 * This function waits for the Command Complete Interrupt Flag (CCIF) to be set,
 * indicating that the FTFC module is ready, and then writes the provided data 
 * to the specified flash memory address.
 *
 * @param address Pointer to the flash memory address where the data will be written.
 * @param data The data to be written to the specified flash memory address.
 */
void write_char_to_flash(uint32_t *address, uint32_t data); 

/**
 * @brief Reads a character from a specific address in flash memory.
 *
 * This function waits for the Command Complete Interrupt Flag (CCIF) to be set,
 * indicating that the FTFC module is ready, and then reads the data from the
 * specified flash memory address into the provided data pointer.
 *
 * @param address Pointer to the flash memory address from which the data will be read.
 * @param data Pointer to where the read data will be stored.
 */
void read_char_from_flash(uint32_t *address, uint32_t *data);

/**
 * @brief Writes a date array to flash memory.
 * 
 * This function writes an 8-byte date array to the flash memory starting at a predefined address.
 * The date array should be in the format DDMMYYYY, where:
 * - DD is the day,
 * - MM is the month,
 * - YYYY is the year.
 * 
 * The date array is divided into two 32-bit values for storage in flash memory.
 * 
 * @param date A pointer to an 8-byte array containing the date to be written to flash.
 * 
 * @note The flash memory address for date storage is defined by `FLASH_DATE_START_ADDRESS`.
 */
void write_date_to_flash(char date[8]);

/**
 * @brief Writes a time array to flash memory.
 * 
 * This function writes a 6-byte time array to the flash memory starting at a predefined address.
 * The time array should be in the format HHMMSS, where:
 * - HH is the hours,
 * - MM is the minutes,
 * - SS is the seconds.
 * 
 * The time array is divided into two 32-bit values for storage in flash memory.
 * Since the time is 6 bytes long, the last byte is set to zero.
 * 
 * @param time A pointer to a 6-byte array containing the time to be written to flash.
 * 
 * @note The flash memory address for time storage is defined by `FLASH_TIME_START_ADDRESS`.
 */
void write_time_to_flash(char time[6]);

/**
 * @brief Reads a date from flash memory.
 * 
 * This function reads an 8-byte date from flash memory starting at a predefined address.
 * The date is expected to be in the format DDMMYYYY and is returned in the provided array.
 * 
 * @param date A pointer to an 8-byte array where the read date will be stored.
 * 
 * @note The flash memory address for date storage is defined by `FLASH_DATE_START_ADDRESS`.
 */
void read_date_from_flash(char date[8]);

/**
 * @brief Reads a time from flash memory.
 * 
 * This function reads a 6-byte time from flash memory starting at a predefined address.
 * The time is expected to be in the format HHMMSS and is returned in the provided array.
 * 
 * @param time A pointer to a 6-byte array where the read time will be stored.
 * 
 * @note The flash memory address for time storage is defined by `FLASH_TIME_START_ADDRESS`.
 */
void read_time_from_flash(char time[6]);

/**
 * @brief Writes the time alarm data to flash memory.
 *
 * This function takes a 6-byte array representing the time alarm and
 * writes it to the flash memory of the S32K144 microcontroller.
 * The time is split into two 32-bit values before being written to flash.
 *
 * @param time A 6-byte array containing the time alarm data in the format HHMMSS.
 */
void write_time_alarm_to_flash(char time[6]);

/**
 * @brief Reads the time alarm data from flash memory.
 *
 * This function reads a 6-byte time alarm stored in flash memory of the 
 * S32K144 microcontroller and converts it into a time array. The function
 * also verifies that each byte in the array is a valid numeric character.
 * If any invalid characters are found, the entire time array is reset to '0'.
 *
 * @param time A 6-byte array where the time alarm data (in the format HHMMSS) will be stored.
 */
void read_time_alarm_from_flash(char time[6]);

#endif 