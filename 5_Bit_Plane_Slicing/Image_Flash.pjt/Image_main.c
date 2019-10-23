#include "DSP2833x_Device.h"
#include <string.h>
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//########### Global Variables ###########################################
#define SERIALNUM  		0x00	
#define COMMANDSEND  	0x56
#define COMMANDREPLY  	0x76
#define COMMANDEND    	0x00

#define CMD_GETVERSION  0x11
#define CMD_RESET       0x26
#define CMD_TAKEPHOTO   0x36
#define CMD_READBUFF    0x32
#define CMD_GETBUFFLEN  0x34

#define FBUF_CURRENTFRAME  		0x00
#define FBUF_NEXTFRAME  		0x01
#define FBUF_STOPCURRENTFRAME  	0x00

#define img_width 960		//320*3
#define img_height 20
#define repeat 12 


unsigned int data[img_height][img_width];
unsigned int image_len=0;
int status=0,ksy=0;

// External Function prototypes
extern void InitSysCtrl(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void InitFlash(void);


extern void Init_Flash_PHOTO(void);
extern void Update_FLASH(Uint16** D_addr);
extern void Read_FLASH(Uint16** S_addr);

void Input_Image();
extern void MonoChrome_Image(char component);
extern void Gray_Image(char component) ;
extern void Threshold_Image(char component, unsigned int threshold);
extern void Bit_Plane_Slicing(char component, int Bit_Plane);
extern void CMY_Image(char component);
extern void Filter(char type);
extern void HSV(char component);
extern void Inverse_Threshold_Image(char component, unsigned int threshold);
extern void Negation_Gray(char component);
extern void Gray_Image_Quantization(char component, int No_of_bits);
extern void Image_Sampling(int sampling_factor, char type_of_op_image);
extern void histogram_equalization(char component);
extern void Contrast_Stretching(char component, float UT, float LT, float SLOPE_L,float SLOPE_M,float SLOPE_N);
extern void Edge_Detection(char type);
extern void NTSC(char component);
extern void YCbCr(char component);
//extern void Get_JPEG_Image(void);
//extern void Send_JPEG_Image(void);
//extern void Wait_For_Start(void);

// external symbols for section ramfuncs
extern unsigned int  RamfuncsLoadStart;
extern unsigned int  RamfuncsLoadEnd;
extern unsigned int  RamfuncsRunStart;
extern Uint16* SourceAddr;
extern Uint16* DestAddr; 
extern Uint16 A0;
// Prototype statements for functions found within this file.
void Gpio_select(void);
void SCIA_init(void);
void SCIB_init(void);
void Flash_Write_Image(void);
void Wait_For_Start(void);
void Error_LED(void);
void Reset_Camera(void);
void Get_Version(void);
void Set_Photo_Size(void);
void Take_Photo(void);
void Get_Buffer_Length(void);
void Read_Buffer(void);
int Check_Reply(char reply[], int b);
void Get_JPEG_Image(void);
void Send_JPEG_Image(void);
void Send_Image_Name(char name[]);
interrupt void cpu_timer0_isr(void); // Prototype for Timer 0 Interrupt Service Routine

// global variables


 
//###########################################################################
//						main code									
//###########################################################################
void main(void)
{
	int No_Of_Images=10;
	InitSysCtrl();					// Basic Core Initialization

	 // Copy time critical code and Flash setup code to RAM
   	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, &RamfuncsLoadEnd - &RamfuncsLoadStart);
	InitFlash();					// Speed up FLASH memory 
	
	EALLOW;
   	SysCtrlRegs.WDCR= 0x00AF;		// Re-enable watchdog 
   	EDIS;							// 0x00E8  to disable the Watchdog , Prescaler = 1
   									// 0x00AF  enable the Watchdog, Prescaler = 64
	
	Gpio_select();	

	InitPieCtrl();		// extern function Call to init PIE-unit (DSP2833x_PieCtrl.c)
	
	InitPieVectTable(); // extern function call to init PIE vector table (DSP2833x_PieVect.c )
	
	// re-map PIE - entry for Timer 0 Interrupt & ADC
	EALLOW;  
   	PieVectTable.TINT0 = &cpu_timer0_isr;
   	EDIS;   
	
	SCIA_init();  // Initalize SCI-A 
	SCIB_init();  // Initalize SCI-B    
	
	InitCpuTimers();	// Function in: DSP2833x_CpuTimers.c	
	
	
	// Configure CPU-Timer 0 to interrupt every 50 ms:
	// 150MHz CPU Freq, 50000 µseconds interrupt period
    ConfigCpuTimer(&CpuTimer0, 150, 200000);	// DSP2833x_CpuTimers.c

	// Enable PIE: Group 1 interrupts
   	PieCtrlRegs.PIEIER1.bit.INTx7 = 1; // TINT0
	//PieCtrlRegs.PIEIER1.bit.INTx6 = 1; // ADC
	
	// Enable CPU INT1 which is connected to CPU-Timer 0:
    IER = 1;
    
	// Enable global Interrupts and higher priority real-time debug events:
   	EINT;   // Enable Global interrupt INTM
   	ERTM;   // Enable Global realtime interrupt DBGM
   	
   	CpuTimer0Regs.TCR.bit.TSS = 0;		// Start T0
   	GpioDataRegs.GPCSET.bit.GPIO80 = 1;
   	GpioDataRegs.GPCSET.bit.GPIO81 = 1;
	GpioDataRegs.GPCSET.bit.GPIO82 = 1;
	GpioDataRegs.GPCSET.bit.GPIO83 = 1;
	
	Init_Flash_PHOTO();		
	
	Get_JPEG_Image();
	
	Send_Image_Name("Original_Image");
	Send_JPEG_Image();
		
	Wait_For_Start();
	Flash_Write_Image();
	
	SciaRegs.SCITXBUF=(char)No_Of_Images;				// send 'A' for 320*240*3
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	
	Input_Image();
	Gray_Image('Y');
	Bit_Plane_Slicing('Y', 7);
	Bit_Plane_Slicing('Y', 6);
	Bit_Plane_Slicing('Y', 5);
	Bit_Plane_Slicing('Y', 4);
	Bit_Plane_Slicing('Y', 3);
	Bit_Plane_Slicing('Y', 2);
	Bit_Plane_Slicing('Y', 1);
	Bit_Plane_Slicing('Y', 0);
	/*
	Filter('L');
	Filter('H');
	Filter('B');
	Filter('O');
	
	Edge_Detection('O');
	Edge_Detection('R');
	Edge_Detection('P');
	Edge_Detection('S');
	
	Contrast_Stretching('Y', 200, 100, 0.5,2,0.5);
	Gray_Image('Y');
	histogram_equalization('Y');
	Gray_Image('X');
	histogram_equalization('X');
	
	
	Image_Sampling(1, 'C');
	Image_Sampling(2, 'C');
	Image_Sampling(4, 'C');
	Image_Sampling(8, 'C');
	
	
	Image_Sampling(1, 'G');
	Image_Sampling(2, 'G');
	Image_Sampling(4, 'G');
	Image_Sampling(8, 'G');
	
	Gray_Image_Quantization('X', 8);
	Gray_Image_Quantization('X', 7);
	Gray_Image_Quantization('X', 6);
	Gray_Image_Quantization('X', 5);
	Gray_Image_Quantization('X', 4);
	Gray_Image_Quantization('X', 3);
	Gray_Image_Quantization('X', 2);
	Gray_Image_Quantization('X', 1);
	Gray_Image_Quantization('X', 0);
	
	Gray_Image('B');
	Negation_Gray('B');
	Gray_Image('R');
	Negation_Gray('R');
	Gray_Image('G');
	Negation_Gray('G');
	Gray_Image('A');
	Negation_Gray('A');
	Gray_Image('Y');
	Negation_Gray('Y');
	Gray_Image('X');
	Negation_Gray('X');
	Gray_Image('N');
	Negation_Gray('N');
	
	Threshold_Image('B', 127);
	Inverse_Threshold_Image('B', 127);
	Threshold_Image('R', 127);
	Inverse_Threshold_Image('R', 127);
	Threshold_Image('G', 127);
	Inverse_Threshold_Image('G', 127);
	Threshold_Image('A', 127);
	Inverse_Threshold_Image('A', 127);
	Threshold_Image('Y', 127);
	Inverse_Threshold_Image('Y', 127);
	Threshold_Image('X', 127);
	Inverse_Threshold_Image('X', 127);
	Threshold_Image('N', 127);
	Inverse_Threshold_Image('N', 127);
	*/
	/*
	HSV('H');
	HSV('S');
	HSV('V');
	HSV('T');
	
	
	Filter('L');
	Filter('H');
	Filter('B');
	Filter('O');
	
	Bit_Plane_Slicing('H', 7);
	Bit_Plane_Slicing('H', 6);
	Bit_Plane_Slicing('H', 5);
	Bit_Plane_Slicing('H', 4);
	Bit_Plane_Slicing('H', 3);
	Bit_Plane_Slicing('H', 2);
	Bit_Plane_Slicing('H', 1);
	Bit_Plane_Slicing('H', 0);
	
	MonoChrome_Image('B');
	MonoChrome_Image('R');
	MonoChrome_Image('G');
	
	Gray_Image('B');
	Gray_Image('R');
	Gray_Image('G');
	Gray_Image('A');
	Gray_Image('H');
	Gray_Image('X');
	Gray_Image('N');
	
	Threshold_Image('B', 127);
	Threshold_Image('R', 127);
	Threshold_Image('G', 127);
	Threshold_Image('A', 127);
	Threshold_Image('H', 127);
	Threshold_Image('X', 127);
	Threshold_Image('N', 127);
	
	CMY_Image('C');
	CMY_Image('M');
	CMY_Image('Y');
	CMY_Image('T');
	*/
	
	


} 	

void Gpio_select(void)
{
	EALLOW;
	GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 1;	// SCIRXDA
	GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 1;	// SCITXDA	
	
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;	// SCIRXDB
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;	// SCITXDB	
	
	GpioCtrlRegs.GPCMUX2.all = 0;			// GPIO87 ... GPIO80 = General Purpose I/O
	//------------------ Set GPIO as output------------------------------------------//
	GpioCtrlRegs.GPCDIR.bit.GPIO80 = 1;	// peripheral explorer: LED3 at GPIO80
	GpioCtrlRegs.GPCDIR.bit.GPIO81 = 1;	// peripheral explorer: LED4 at GPIO81
	GpioCtrlRegs.GPCDIR.bit.GPIO82 = 1;	// peripheral explorer: LED5 at GPIO82
	GpioCtrlRegs.GPCDIR.bit.GPIO83 = 1;	// peripheral explorer: LED1 at GPIO83
	EDIS;
}


#pragma CODE_SECTION(cpu_timer0_isr, "ramfuncs");
interrupt void cpu_timer0_isr(void)
{
	CpuTimer0.InterruptCount++;				// increment time counter
	if(CpuTimer0.InterruptCount > 1000)  	// 65000 * 100ms = 2 sec
	{
		CpuTimer0.InterruptCount =0;
	}
	EALLOW;
	SysCtrlRegs.WDKEY = 0x55;			// Service watchdog #1
	SysCtrlRegs.WDKEY = 0xAA;			// Service watchdog #2
	EDIS;
 	// Acknowledge this interrupt to receive more interrupts from group 1
   	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}



void SCIA_init(void)
{    
	SciaRegs.SCICCR.all =0x0007;   	// 1 stop bit,  No loopback 
                                   	// NO parity,8 char bits,
                                   	// async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  	// enable TX, RX, internal SCICLK, 
                                   	// Disable RX ERR, SLEEP, TXWAKE
	
	// SYSCLOCKOUT = 150MHz; LSPCLK = 1/4 = 37.5 MHz
	// BRR = (LSPCLK / (38400 x 8)) -1
	// BRR = 121(0x0079)  gives 38400 Baud
	SciaRegs.SCIHBAUD    = 0x00;		// Highbyte
	SciaRegs.SCILBAUD    = 0x09;	// Lowbyte

	//SciaRegs.SCICTL2.bit.TXINTENA = 1; 		// enable SCI-A Tx-ISR
	//SciaRegs.SCICTL2.bit.RXBKINTENA = 1; 	// enable SCI_A Rx-ISR
	
	//SciaRegs.SCIFFTX.all = 0xC060;	// bit 15 = 1 : relinquish from Reset
									// bit 14 = 1 : Enable FIFO
									// bit 6 = 1 :  CLR TXFFINT-Flag
									// bit 5 = 1 :  enable TX FIFO match
									// bit 4-0 :  TX-ISR, if TX FIFO is 0(empty) 
	//SciaRegs.SCIFFCT.all = 0x0000;	// Set FIFO transfer delay to 0
	
	//SciaRegs.SCIFFRX.all = 0xE061;	// Rx interrupt level = 5
	
	SciaRegs.SCICTL1.all = 0x0023;	// Relinquish SCI from Reset 
}  


void SCIB_init(void)
{    
   	ScibRegs.SCICCR.all =0x0007;   	// 1 stop bit,  No loopback 
                                   	// NO parity,8 char bits,
                                   	// async mode, idle-line protocol
	ScibRegs.SCICTL1.all =0x0003;  	// enable TX, RX, internal SCICLK, 
                                   	// Disable RX ERR, SLEEP, TXWAKE
	
	// SYSCLOCKOUT = 150MHz; LSPCLK = 1/4 = 37.5 MHz
	// BRR = (LSPCLK / (38400 x 8)) -1
	// BRR = 121(0x0079)  gives 38400 Baud
	ScibRegs.SCIHBAUD    = 0x00;		// Highbyte
	ScibRegs.SCILBAUD    = 0x79;		// Lowbyte

	//ScibRegs.SCICTL2.bit.TXINTENA = 1; 		// enable SCI-A Tx-ISR
	//ScibRegs.SCICTL2.bit.RXBKINTENA = 1; 	// enable SCI_A Rx-ISR
	/*
	ScibRegs.SCIFFTX.all = 0xC060;	// bit 15 = 1 : relinquish from Reset
									// bit 14 = 1 : Enable FIFO
									// bit 6 = 1 :  CLR TXFFINT-Flag
									// bit 5 = 1 :  enable TX FIFO match
									// bit 4-0 :  TX-ISR, if TX FIFO is 0(empty) 
	ScibRegs.SCIFFCT.all = 0x0000;	// Set FIFO transfer delay to 0
	
	ScibRegs.SCIFFRX.all = 0xE061;	// Rx interrupt level = 5
	*/
	ScibRegs.SCICTL1.all = 0x0023;	// Relinquish SCI from Reset 
}


void Flash_Write_Image(void)
{
	Uint16 i,j,k;
	
	for(k=0;k<repeat;k++)
	{
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;)
			{
				if(SciaRegs.SCIRXST.bit.RXRDY==1)
				{
					data[i][j] = SciaRegs.SCIRXBUF.bit.RXDT;
					j++;
				}
			}
		}
		Update_FLASH(&SourceAddr);
		Wait_For_Start();	
	}
}


void Get_JPEG_Image(void)
{	
	Wait_For_Start();
   	Reset_Camera();
   	Get_Version();	
    //Set_Photo_Size();
	Take_Photo();
	Get_Buffer_Length();	
	Read_Buffer();
}

void Send_JPEG_Image(void)
{
	Uint16 i,j,k=0;
	
	SciaRegs.SCITXBUF=(char)(image_len & 0x00ff);			// send lower Byte length
 	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); //wait for TX -empty
	SciaRegs.SCITXBUF=(char)(image_len >> 8);			// send Higher byte length
 	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); //wait for TX -empty
	
	for(i=0;i<img_height;i++)
	{
		for(j=0;j<img_width;j++)
		{
			SciaRegs.SCITXBUF=(char)data[i][j];			// send single character
 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); //wait for TX -empty
 			k++;
 			if(k>=image_len) break;
		}
		if(k>=image_len) break;
	}	
}	


void Send_Image_Name(char name[])
{
	int n,i;
	n=strlen(name);
	
	
	SciaRegs.SCITXBUF=(char)n;			// send single character
 	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); //wait for TX -empty
	
	for(i=0;i<n;i++)
	{
		SciaRegs.SCITXBUF=name[i];			// send single character
 		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); //wait for TX -empty
	}
}

void Wait_For_Start(void)
{
	char start = '0';
	
	while((int)start != 0x53)			//wait till 'S' is received
	{
		if(SciaRegs.SCIRXST.bit.RXRDY==1)
		{
			start = SciaRegs.SCIRXBUF.bit.RXDT;
		}
	}
	
	SciaRegs.SCITXBUF=start;				// send single character
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
}


void Error_LED(void)
{
	while(1)
	{
		GpioDataRegs.GPCTOGGLE.bit.GPIO80 = 1;
		DELAY_US(500000);
	}
}


void Reset_Camera(void)
{
	int resetcommand[] = {COMMANDSEND, SERIALNUM, CMD_RESET, COMMANDEND};
	int n = sizeof(resetcommand)/sizeof(resetcommand[0]);
	int index=0;
	char reply[71];
	status=0;
		
	while(index < n)
	{		
		ScibRegs.SCITXBUF=(char)resetcommand[index++];			// send single character
 		while ( ScibRegs.SCICTL2.bit.TXEMPTY == 0); 			//wait for TX -empty		
	}
	index=0;
	while(index<71)
	{
		if(ScibRegs.SCIRXST.bit.RXRDY==1)
		{
			reply[index] = ScibRegs.SCIRXBUF.bit.RXDT;
			index++;
		}
	}
	
	status = Check_Reply(reply, CMD_RESET);
	if(status==0)
	{
		Error_LED();
	}
}


void Get_Version(void)
{
	int getversioncommand[] = {COMMANDSEND, SERIALNUM, CMD_GETVERSION, COMMANDEND};
	int n = sizeof(getversioncommand)/sizeof(getversioncommand[0]);
	int index=0;
	char reply[16];
	status=0;
		
	while(index < n)
	{		
		ScibRegs.SCITXBUF=(char)getversioncommand[index++];			// send single character
 		while ( ScibRegs.SCICTL2.bit.TXEMPTY == 0); 				//wait for TX -empty			
	}
	index=0;
	while(index<16)
	{
		if(ScibRegs.SCIRXST.bit.RXRDY==1)
		{
			reply[index] = ScibRegs.SCIRXBUF.bit.RXDT;
			index++;
		}
	}
	
	status = Check_Reply(reply, CMD_GETVERSION);
	if(status==0)
	{
		Error_LED();
	}
}


void Take_Photo(void)
{
	int takephotocommand[] = {COMMANDSEND, SERIALNUM, CMD_TAKEPHOTO, 0x01, FBUF_STOPCURRENTFRAME};
	int n = sizeof(takephotocommand)/sizeof(takephotocommand[0]);
	int index=0;
	char reply[5];
	status=0;
		
	while(index < n)
	{
		ScibRegs.SCITXBUF=(char)takephotocommand[index++];			// send single character
 		while ( ScibRegs.SCICTL2.bit.TXEMPTY == 0); 				//wait for TX -empty		
	}
	index=0;
	while(index<5)
	{
		if(ScibRegs.SCIRXST.bit.RXRDY==1)
		{
			reply[index] = ScibRegs.SCIRXBUF.bit.RXDT;
			index++;
		}
	}
	
	status = Check_Reply(reply, CMD_TAKEPHOTO);
	if(status==0)
	{
		Error_LED();
	}
}


void Get_Buffer_Length(void)
{
	int getbufflencommand[] = {COMMANDSEND, SERIALNUM, CMD_GETBUFFLEN, 0x01, FBUF_CURRENTFRAME};
	int n = sizeof(getbufflencommand)/sizeof(getbufflencommand[0]);
	int index=0;
	char reply[9];
	status=0;
		
	while(index < n)
	{		
		ScibRegs.SCITXBUF=(char)getbufflencommand[index++];			// send single character
 		while ( ScibRegs.SCICTL2.bit.TXEMPTY == 0); 				//wait for TX -empty		
	}
	index=0;
	while(index<9)
	{
		if(ScibRegs.SCIRXST.bit.RXRDY==1)
		{
			reply[index] = ScibRegs.SCIRXBUF.bit.RXDT;
			index++;
		}
	}
	
	if(Check_Reply(reply, CMD_GETBUFFLEN) & reply[4] == (char)0x4)
	{
		image_len = (int)reply[5];
        image_len = image_len << 8;
        image_len = image_len + (int)reply[6];
        image_len = image_len << 8;
        image_len = image_len + (int)reply[7];
        image_len = image_len << 8;
        image_len = image_len + (int)reply[8];
                        
		status = 1;
	}
	
	if(status==0)
	{
		Error_LED();
	}
}


void Set_Photo_Size(void)
{
	int setphotosize[] = {COMMANDSEND, SERIALNUM, 0x31, 0x05, 0x04, 0x01, 0x00, 0x19, 0x11};
	int n = sizeof(setphotosize)/sizeof(setphotosize[0]);
	int index=0;
	char reply[5];
	status=0;
		
	while(index < n)
	{	
		ScibRegs.SCITXBUF=(char)setphotosize[index++];			// send single character
 		while ( ScibRegs.SCICTL2.bit.TXEMPTY == 0); 			//wait for TX -empty		
	}
	index=0;
	while(index<5)
	{
		if(ScibRegs.SCIRXST.bit.RXRDY==1)
		{
			reply[index] = ScibRegs.SCIRXBUF.bit.RXDT;
			index++;
		}
	}
	status = Check_Reply(reply, 0x31);
	
	if(status==0)
	{
		Error_LED();
	}
}


void Read_Buffer(void)
{
	int command[] ={COMMANDSEND, SERIALNUM, CMD_READBUFF, 0x0c, FBUF_CURRENTFRAME, 0x0a,0,0,0,0,0,0,0,0,0,0};
	int n = sizeof(command)/sizeof(command[0]);
	int index,error=0;
	char reply[img_width+10];
	int i,data_j=0;	
	int inc = img_width;		//byte to read each time (must be a mutiple of 4)
	Uint32 chunk = 0;
	Uint32 addr = 0;   // the initial offset into the frame buffer
    
    while( addr < image_len )
    {
    	chunk = (image_len - addr) < inc ? (image_len - addr) : inc ;
        
        command[6] = (addr >> 24) & 0xff;
        command[7] = (addr>>16) & 0xff;
        command[8] = (addr>>8 ) & 0xff;
        command[9] = addr & 0xff;
        command [10] = (chunk >> 24) & 0xff;
        command[11] = (chunk>>16) & 0xff;
        command[12] = (chunk>>8 ) & 0xff;
        command[13] =  chunk & 0xff;
        command[14] = 0x10;
        command[15] = 0;
             
        index=0;        		
		while(index < n)
		{			
			ScibRegs.SCITXBUF=(char)command[index++];			// send single character
	 		while ( ScibRegs.SCICTL2.bit.TXEMPTY == 0); 		//wait for TX -empty
		}
		
		index=0;
		CpuTimer0.InterruptCount =0;
		while(index<(5+chunk+5))
		{
			if(ScibRegs.SCIRXST.bit.RXRDY==1)
			{
				reply[index] = ScibRegs.SCIRXBUF.bit.RXDT;
				index++;
			}
			if(CpuTimer0.InterruptCount > 4)
			{
				ksy++;
				error=1;
				break;
			}
		}
		if(error==1)
		{
			error=0;
			continue;
		}
		
		
		status = Check_Reply(reply, CMD_READBUFF);
		if(status==0)
		{
			GpioDataRegs.GPCCLEAR.bit.GPIO82 = 1;
			Error_LED();
		}
		
		//append the data between the header data to photo
	    
		/*index=5;
		while(index < chunk+5)
		{
			SciaRegs.SCITXBUF=reply[index++];			// send single character
	 		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); //wait for TX -empty
		}*/
		
		index=0;
		for(i=5;i<(chunk+5);i++,index++)
		{
			data[data_j][index]=reply[i];
		}
		data_j++;
		
	    addr = addr + chunk;		//advance the offset into the frame buffer
		
    }
	
}


int Check_Reply(char reply[], int b)
{
	if( (int)reply[0] == COMMANDREPLY & (int)reply[1] == SERIALNUM & (int)reply[2] == b & (int)reply[3] == 0x00)
	{
		return 1;
	}
    return 0;
}

//===========================================================================
// End of SourceCode.
//===========================================================================
