#include "UNIT_TEST.h"

void ut_clear_error_flash(void)
{
	clear_error_flash(); 
	
	int state; 
	if ( ((*FTFC).FSTAT & ((1u << FPVIOL) | (1u < ACCERR))) != 0)
	{
		state = FAILED; 
	}
	else
	{
	  state = PASSED; 
	}
}


int ut_enable_pcc(char PORT)
{
  static int  state = FAILED; 
  switch (PORT)
  {
  case 'A':
  {
    if ( ((*PCC).PCC_PORTA & ENABLE_PCC_PORT_MASK) != 0)
    {
      state = PASSED;
    }
    break;
  }
  case 'B':
   {
    if ( ((*PCC).PCC_PORTB & ENABLE_PCC_PORT_MASK) != 0)
    {
      state = PASSED;
    }
    break;
  }
  case 'C':
   {
    if ( ((*PCC).PCC_PORTC & ENABLE_PCC_PORT_MASK) != 0)
    {
      state = PASSED;
    }
    break;
  }
  case 'D':
   {
    if ( ((*PCC).PCC_PORTD & ENABLE_PCC_PORT_MASK) != 0)
    {
      state = PASSED;
    }
    break;
  }
  case 'E':
  {
    if ( ((*PCC).PCC_PORTE & ENABLE_PCC_PORT_MASK) != 0)
    {
      state = PASSED;
    }
    break;
  }
  case 'L': 
  {
    if ( ( (*PCC).PCC_LPIT & ENABLE_PCC_LPIT_MASK) != 0)
    {
      state = PASSED;
    }
    else
    {
      state = FAILED;
    }

    if (((*PCC).PCC_LPIT & (6u<< PCS_PCC)) != 0)
    {
      state = PASSED;
    }
    else
    {
      state = FAILED;
    }
    break;
  }
  default: 
    break;
  }

  return state; 
}

int ut_port_set_up(char PORT, unsigned int PORT_SET_UP, char PORT_DIRECTION, unsigned int PULL_SELECTION, unsigned int ENABLE_INTERRUPT)
{
  static int state = FAILED; 
  switch (PORT)
  {
  case 'A':
  {
    if (PORT_DIRECTION == 'I')
    {
      if (((*GPIOA).PDDR & 1u << PORT_SET_UP) == 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (( (*PORTA).PORT_PCR[PORT_SET_UP] & SET_PE_MASK) != 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (((*PORTA).PORT_PCR[PORT_SET_UP] & SET_PS_MASK) == 0)
      {
        state = PASSED;
      }
      else
      {
        state = FAILED; 
      }

      state = (PULL_SELECTION) ? !state : state; 

      if (((*PORTA).PORT_PCR[PORT_SET_UP] >> 16u) == (DISABLE_INTERRUPT >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTA).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_RISING_EDGE >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTA).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_FALLING_EDGE >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTA).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_BOTH_EDGE >> 16u))
      {
        state = PASSED;
      }
      else
      {
        state = FAILED; 
      }
    }
    else
    {
      if (((*GPIOA).PDDR & 1u << PORT_SET_UP) != 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (( (*PORTA).PORT_PCR[PORT_SET_UP] & SET_PE_MASK) == 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }
    }
    break;
  }
  case 'B': 
  {
    if (PORT_DIRECTION == 'I')
    {
      if (((*GPIOB).PDDR & 1u << PORT_SET_UP) == 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (( (*PORTB).PORT_PCR[PORT_SET_UP] & SET_PE_MASK) != 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (((*PORTB).PORT_PCR[PORT_SET_UP] & SET_PS_MASK) == 0)
      {
        state = PASSED;
      }
      else
      {
        state = FAILED; 
      }

      state = (PULL_SELECTION) ? !state : state; 

      if (((*PORTB).PORT_PCR[PORT_SET_UP] >> 16u) == (DISABLE_INTERRUPT >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTB).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_RISING_EDGE >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTB).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_FALLING_EDGE >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTB).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_BOTH_EDGE >> 16u))
      {
        state = PASSED;
      }
      else
      {
        state = FAILED; 
      }
    }
    else
    {
      if (((*GPIOB).PDDR & 1u << PORT_SET_UP) != 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (( (*PORTB).PORT_PCR[PORT_SET_UP] & SET_PE_MASK) == 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }
    }
    break;
  }
  case 'C':
  {
    if (PORT_DIRECTION == 'I')
    {
      if (((*GPIOC).PDDR & 1u << PORT_SET_UP) == 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (( (*PORTC).PORT_PCR[PORT_SET_UP] & SET_PE_MASK) != 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (((*PORTC).PORT_PCR[PORT_SET_UP] & SET_PS_MASK) == 0)
      {
        state = PASSED;
      }
      else
      {
        state = FAILED; 
      }

      state = (PULL_SELECTION) ? !state : state; 

      if (((*PORTC).PORT_PCR[PORT_SET_UP] >> 16u) == (DISABLE_INTERRUPT >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTC).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_RISING_EDGE >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTC).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_FALLING_EDGE >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTC).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_BOTH_EDGE >> 16u))
      {
        state = PASSED;
      }
      else
      {
        state = FAILED; 
      }
    }
    else
    {
      if (((*GPIOC).PDDR & 1u << PORT_SET_UP) != 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (( (*PORTC).PORT_PCR[PORT_SET_UP] & SET_PE_MASK) == 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }
    }
    break;
  } 
  case 'D': 
  {
    if (PORT_DIRECTION == 'I')
    {
      if (((*GPIOD).PDDR & 1u << PORT_SET_UP) == 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (( (*PORTD).PORT_PCR[PORT_SET_UP] & SET_PE_MASK) != 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (((*PORTD).PORT_PCR[PORT_SET_UP] & SET_PS_MASK) == 0)
      {
        state = PASSED;
      }
      else
      {
        state = FAILED; 
      }

      state = (PULL_SELECTION) ? !state : state; 

      if (((*PORTD).PORT_PCR[PORT_SET_UP] >> 16u) == (DISABLE_INTERRUPT >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTD).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_RISING_EDGE >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTD).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_FALLING_EDGE >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTD).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_BOTH_EDGE >> 16u))
      {
        state = PASSED;
      }
      else
      {
        state = FAILED; 
      }
    }
    else
    {
      if (((*GPIOD).PDDR & 1u << PORT_SET_UP) != 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (( (*PORTD).PORT_PCR[PORT_SET_UP] & SET_PE_MASK) == 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }
    }
    break;
  }
  case 'E': 
  {
    if (PORT_DIRECTION == 'I')
    {
      if (((*GPIOE).PDDR & 1u << PORT_SET_UP) == 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (( (*PORTE).PORT_PCR[PORT_SET_UP] & SET_PE_MASK) != 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (((*PORTE).PORT_PCR[PORT_SET_UP] & SET_PS_MASK) == 0)
      {
        state = PASSED;
      }
      else
      {
        state = FAILED; 
      }

      state = (PULL_SELECTION) ? !state : state; 

      if (((*PORTE).PORT_PCR[PORT_SET_UP] >> 16u) == (DISABLE_INTERRUPT >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTE).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_RISING_EDGE >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTE).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_FALLING_EDGE >> 16u))
      {
        state = PASSED;
      }
      else if (((*PORTE).PORT_PCR[PORT_SET_UP] >> 16u) == (INTERRUPT_BOTH_EDGE >> 16u))
      {
        state = PASSED;
      }
      else
      {
        state = FAILED; 
      }
    }
    else
    {
      if (((*GPIOE).PDDR & 1u << PORT_SET_UP) != 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }

      if (( (*PORTE).PORT_PCR[PORT_SET_UP] & SET_PE_MASK) == 0)
      {
        state = PASSED; 
      }
      else
      {
        state = FAILED;
      }
    }
    break;
  }
  default:
    break;
  }

  return state; 

}

int ut_enable_module_clock_lpit(void)
{
  static int state = FAILED; 
  if( ( (*LPIT).MCR & ((1u << DBG_EN) | (1u << M_CEN))) != 0)
  {
    state = PASSED; 
  }

  return state; 
}

int ut_enable_interrupt_lpit(int channel)
{
  static int state = FAILED; 
  if(((*LPIT).MIER & (1u << channel)) != 0 )
  {
    state = PASSED;
  }

  return state; 
}

int ut_set_up_port_uart(int channel)
{
	int state = FAILED; 
	switch (channel)
	{
	case LUART_CHANNEL0: 
	{
		if((( (*PCC).PCC_LPUART0 & (ENABLE_PCC_LUART_MASK)) != 0) && (((*PCC).PCC_LPUART0 & (SOSCDIV2_CLOCK << PCS_PCC)) != 0))
			state = PASSED; 
		else 
			state = FAILED; 

		state = ut_enable_pcc('B'); 

		if((((*PORTB).PORT_PCR[0] & (PORT_MUX_MASK_CHIP_SPECIFIC_LPUART)) != 0) && (((*PORTB).PORT_PCR[1] & (PORT_MUX_MASK_CHIP_SPECIFIC_LPUART)) != 0) )
		{
			state = PASSED;
		}
		else 
		{
			state = FAILED;
		}

		break; 
	}
	case LUART_CHANNEL1: 
	{
		if((( (*PCC).PCC_LPUART1 & (ENABLE_PCC_LUART_MASK)) != 0) && (((*PCC).PCC_LPUART1 & (SOSCDIV2_CLOCK << PCS_PCC)) != 0))
			state = PASSED; 
		else 
			state = FAILED; 

		state = ut_enable_pcc('C'); 

		if((((*PORTC).PORT_PCR[6] & (PORT_MUX_MASK_CHIP_SPECIFIC_LPUART)) != 0) && (((*PORTC).PORT_PCR[7] & (PORT_MUX_MASK_CHIP_SPECIFIC_LPUART)) != 0) )
		{
			state = PASSED;
		}
		else 
		{
			state = FAILED;
		}

		break; 
	}
	case LUART_CHANNEL2: 
	{
		if((( (*PCC).PCC_LPUART2 & (ENABLE_PCC_LUART_MASK)) != 0) && (((*PCC).PCC_LPUART2 & (SOSCDIV2_CLOCK << PCS_PCC)) != 0))
			state = PASSED; 
		else 
			state = FAILED; 

		state = ut_enable_pcc('E'); 

		if((((*PORTE).PORT_PCR[12] & (PORT_MUX_MASK_CHIP_SPECIFIC_LPUART)) != 0) && (((*PORTE).PORT_PCR[17] & (PORT_MUX_MASK_CHIP_SPECIFIC_LPUART)) != 0) )
		{
			state = PASSED;
		}
		else 
		{
			state = FAILED;
		}
		break; 
	}
	default:
		break;
	}

	return state; 
}
