#ifndef UNIT_TEST_H_
#define UNIT_TEST_H_

#include <stdint.h> 

#include "EMB_MOCK.h"

#define PASSED 1
#define FAILED 0 

void ut_clear_error_flash(void); 
int ut_enable_pcc(char PORT);
int ut_port_set_up(char PORT, unsigned int PORT_SET_UP, char PORT_DIRECTION, unsigned int PULL_SELECTION, unsigned int ENABLE_INTERRUPT);
int ut_enable_module_clock_lpit(void); 
int ut_enable_interrupt_lpit(int channel);

int ut_set_up_port_uart(int channel); 
int ut_set_baudrate(int channel); 
#endif 