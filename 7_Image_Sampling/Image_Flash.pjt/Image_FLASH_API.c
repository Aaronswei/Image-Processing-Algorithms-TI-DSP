//
//      Lab14_FLASH: TMS320F28335
//      (C) Frank Bormann
//
//###########################################################################
//
// FILE:	Lab14_FLASH_API.c
//
// TITLE:	FLASH - API test
//			file covers the Flash - API calls used in Lab14_FLASH
//			Update_FLASH(int);		// writes a single 16 bit word
//			Error();				// stops execution in case od FLASH - Error
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  1.0 | 27 Jul 2008 | F.B. | Prototype   
//	2.2 | 16 Sep 2008 | F.B. | API Version 2.10
//##########################################################################
#include "DSP2833x_Device.h"
#include "Flash2833x_API_Library.h"
#include <stdio.h>  				// defines NULL


#define img_width 960		//320*3
#define img_height 20
#define repeat 12

#define VALID_API_VERSION 0x210		// Version 2.1 for 28335 

extern Uint32 Flash_CPUScaleFactor;
Uint16 A0;
Uint16* SourceAddr;
Uint16* DestAddr; 
void Error(void);
//extern unsigned int data[length_WR];
extern unsigned int data[img_height][img_width];
void Init_Flash_PHOTO(void)
{
	Uint16 i;
	FLASH_ST Flash_Status;
	#pragma DATA_SECTION(A0,"myFlashConstants");
	SourceAddr = &A0;
	DestAddr = &A0; 
	if (SysCtrlRegs.PLLSTS.bit.MCLKSTS == 0)
	{
	// continue only if not in LIMP-Mode
		// copy FLASH - API from FLASHD into RAML0
		/*pSourceAddr = &Flash28_API_LoadStart;
		pDestAddr = &Flash28_API_RunStart;
		for(i = 0; i < (&Flash28_API_LoadEnd-&Flash28_API_LoadStart); i++)
		{
	    	*pDestAddr++ = *pSourceAddr++;
		}
		*/
		memcpy(&Flash28_API_RunStart, &Flash28_API_LoadStart, &Flash28_API_LoadEnd - &Flash28_API_LoadStart);
		Flash_CPUScaleFactor = SCALE_FACTOR;
		Flash_CallbackPtr = NULL;
		
		if (Flash_APIVersionHex() == VALID_API_VERSION)
		{
		// continue only if valid API - Library
			//	DINT;		// ISR's must be disabled, when the ISR is part of FLASH
							// if ISR is allocated in RAM, they can be active ( see lab03)
			// Erase Sector B
			
			i = Flash_Erase(SECTORH,&Flash_Status);
			if (i != STATUS_SUCCESS)Error();
			i = Flash_Erase(SECTORG,&Flash_Status);
			if (i != STATUS_SUCCESS)Error();
			i = Flash_Erase(SECTORF,&Flash_Status);
			if (i != STATUS_SUCCESS)Error();
			i = Flash_Erase(SECTORE,&Flash_Status);
			if (i != STATUS_SUCCESS)Error();
			i = Flash_Erase(SECTORD,&Flash_Status);
			if (i != STATUS_SUCCESS)Error();
			i = Flash_Erase(SECTORC,&Flash_Status);
			if (i != STATUS_SUCCESS)Error();
			i = Flash_Erase(SECTORB,&Flash_Status);
			if (i != STATUS_SUCCESS)Error();
			
			GpioDataRegs.GPCCLEAR.bit.GPIO81 = 1;
			//SourceAddr = &FLASH_Voltage_A0;
			
		}
	}
}

void Update_FLASH(Uint16** D_addr)
{
	Uint16 i,j,k,mod_length;
	FLASH_ST Flash_Status;
	
	for(k=0;k<img_height;k++)
	{
		for(i=0,j=0;i<img_width;i+=3,j++)
		{
			data[k][j] = data[k][i]<<8;
			data[k][j]=data[k][j]+data[k][i+1];
			j++;
			data[k][j]=data[k][i+2];		
		}
	}
	mod_length = (img_width*2)/3;
	if (SysCtrlRegs.PLLSTS.bit.MCLKSTS == 0)		// continue only if not in LIMP-Mode
	{		
		if (Flash_APIVersionHex() == VALID_API_VERSION)			// continue only if valid API - Library
		{
			//	DINT;		// ISR's must be disabled, when the ISR is part of FLASH
			// if ISR is allocated in RAM, they can be active ( see lab03)
			// Program a single 16 bit word into Variable "constant_Voltage_A0"
			for(j=0;j<img_height;j++)
			{
				i = Flash_Program(*D_addr,data[j],mod_length,&Flash_Status);		
				if (i != STATUS_SUCCESS)Error();
				//	EINT;
				*D_addr = *D_addr + mod_length;
			}
			
			
		}
	} 
}


void Read_FLASH(Uint16** S_addr)
{
	Uint16 i,j,mod_length;
	Uint16* ptr;
	ptr = *S_addr;
	// Transfer contents of Current Page to Read Buffer
	//*pDestAddr++ = *pSourceAddr++;
	for(j=0;j<img_height;j++)
	{
		for(i=0;i<img_width;i+=3)
		{
			data[j][i] = *ptr++;
			data[j][i+1] = data[j][i] & 0x00ff;
			data[j][i] = data[j][i] >> 8;
			data[j][i+2] = *ptr++ & 0x00ff;
			/*
			*(D_addr+i+j*img_height) = *S_addr++;
			*(D_addr+i+1+j*img_height) = *(D_addr+i+j*img_height) & 0x00ff;
			*(D_addr+i+j*img_height) = *(D_addr+i+j*img_height)>>8;
			*(D_addr+i+2+j*img_height) = *S_addr++ & 0x00ff; 
			*/
		}
	}
	mod_length = (img_width/3)*2*img_height;
	*S_addr = *S_addr + mod_length;
	
	/*tmp0 = *(D_addr+0);	
	for(i=0;i<mod_length;i++)
	{	
		*(D_addr+i) = tmp0>>8;
		*(D_addr+i+1) = 0x00ff && tmp0;
		tmp0 = *(D_addr+i+1);	
		
	}*/ 
}


void Error(void)
{
	GpioDataRegs.GPCCLEAR.bit.GPIO80 = 1;
	DINT;
	asm(" ESTOP0");	   	  			// Code Execution stops here!!
	while(1);
}
