 /**
 * StepperServoCAN
 *
 * Copyright (c) 2020 Makerbase.
 * Copyright (C) 2018 MisfitTech LLC.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <www.gnu.org/licenses/>.
 *
 */

#include "flash.h"
#include "stm32f10x_flash.h"

//clear whole page and write uint16_t data into selected address
/*
 *	flashAddr:
 *	ptrData:
 *	size: uint16_t size
*/

void Flash_ProgramPage(uint32_t flashAddr, uint16_t *ptrData, uint16_t size)
{	
	FLASH_Unlock();
	
	FLASH_ErasePage(flashAddr);
	Flash_ProgramSize(flashAddr, ptrData, size);
}


//write uint16_t data into selected address
/*
 *	flashAddr:
 *	ptrData:
 *	size:
*/
void Flash_ProgramSize(uint32_t flashAddr, uint16_t* ptrData, uint16_t size)
{
	uint32_t i;
	
	FLASH_Unlock(); 
	
	for(i=0; i<size; i++)
	{
		if(FLASH_WaitForLastOperation(FLASH_WAIT_TIMEOUT) != FLASH_COMPLETE)
		{
			FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		}	
		FLASH_ProgramHalfWord(flashAddr, (*ptrData));
		flashAddr += 2U;
		ptrData += 1;
	}
	
	FLASH_Lock();
}

//read uint16_t data
uint16_t Flash_readHalfWord(uint32_t address)
{
  return (*(__IO uint16_t*)address); 
}

//read uint32_t data
uint32_t Flash_readWord(uint32_t address)
{
  return (*(__IO uint32_t*)address); 
}

