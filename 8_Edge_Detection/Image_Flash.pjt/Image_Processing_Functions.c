#include "DSP2833x_Device.h"
#include <string.h>
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"
#include "stdlib.h"
//#include "complex.h"    /* Standard Library of Complex Numbers */

#define img_width 960		//320*3
#define img_height 20
#define repeat 12 

Uint32 count=0;
Uint32 exceed0=0;
Uint32 exceed255=0;
Uint32 count_check=0;
extern unsigned int data[img_height][img_width];
extern Uint16* DestAddr; 
extern Uint16 A0;
float n_PDF_CDF_LSK_RF[256];

extern void Send_Image_Name(char name[]);
extern void Wait_For_Start(void);
extern void Read_FLASH(Uint16** S_addr);


void Input_Image();

void MonoChrome_Image(char component);
void Gray_Image(char component);
void Negation_Gray(char component);
void Threshold_Image(char component, unsigned int threshold);
void Inverse_Threshold_Image(char component, unsigned int threshold);
void Bit_Plane_Slicing(char component, int Bit_Plane);
void CMY_Image(char component);
void NTSC(char component);
void HSV(char component);
void YCbCr(char component);
void Filter(char type);
void Edge_Detection(char type);
void Gray_Image_Quantization(char component, int No_of_bits);
void Image_Sampling(int sampling_factor, char type_of_op_image);
void histogram_equalization(char component);
void Contrast_Stretching(char component, float UT, float LT, float SLOPE_L,float SLOPE_M,float SLOPE_N);

int dec_binary_check(int n ,int Bit_Plane);
float max(float a, float b);
float min(float a, float b);
float contrast_stretch_calc(float r,float UT, float LT, float SLOPE_L,float SLOPE_M,float SLOPE_N);

void Input_Image() 
{
	int i,j,k;
	DestAddr = &A0;
	Wait_For_Start();
	Send_Image_Name("Input_Image");
	
	
	
	SciaRegs.SCITXBUF=(char)0x41;				// send 'A' for 320*240*3
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				SciaRegs.SCITXBUF=(char)data[i][j];				// send single character
		 		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					
			}
		}
		Wait_For_Start();	
	}
}

void MonoChrome_Image(char component) 
{
	int i,j,k;
	int comp_select;
	
	DestAddr = &A0;
	Wait_For_Start();
	
	if(component=='R')
	{
		Send_Image_Name("Output_Red_Monochrome_Image");
		comp_select=2;
	}
	else if(component=='G')
	{
		Send_Image_Name("Output_Green_Monochrome_Image");
		comp_select=1;
	}
	
	else if(component=='B')
	{
		Send_Image_Name("Output_Blue_Monochrome_Image");
		comp_select=0;
	}
	else
	{
		return;
	}
	
	SciaRegs.SCITXBUF=(char)0x41;				// send 'A' for 320*240*3
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if((j-comp_select)%3==0)
				{
				SciaRegs.SCITXBUF=(char)data[i][j];				// send single character
		 		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
				}
				else
				{
					SciaRegs.SCITXBUF=(char)0;				// send single character
		 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
				}	
			}
		}
		Wait_For_Start();	
	}
}



void Gray_Image(char component) 
{
	int i,j,k;
	int comp_select;
	unsigned int avg;
	
	DestAddr = &A0;
	Wait_For_Start();
	
	if(component=='R')
	{
		Send_Image_Name("Output_Gray_Image_R");
		comp_select=2;
	}
	else if(component=='G')
	{
		Send_Image_Name("Output_Gray_Image_G");
		comp_select=1;
	}
	
	else if(component=='B')
	{
		Send_Image_Name("Output_Gray_Image_B");
		comp_select=0;
	}
	else if(component=='A')
	{
		Send_Image_Name("Output_Gray_Image_Avg");
		comp_select=0;
	}
	else if(component=='Y')
	{
		Send_Image_Name("Output_Gray_Image_Y");
		comp_select=0;	
	}
	else if(component=='X')  //Using maX Component
	{
		Send_Image_Name("Output_Gray_Image_maX");
		comp_select=0;	
	}
	else if(component=='N')  //Using miN Component
	{
		Send_Image_Name("Output_Gray_Image_miN");
		comp_select=0;	
	}
	else
	{
		return;
	}
	
	SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if((j-comp_select)%3==0)
				{
					if(component=='A')
					{
						avg=(data[i][j]+data[i][j+1]+data[i][j+2])/3;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
					
					else if(component=='Y')
					{
						avg= 0.11*(float)data[i][j]+0.59*(float)data[i][j+1]+0.3*(float)data[i][j+2];
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else if(component=='X')
					{
						avg= max(max(data[i][j],data[i][j+1]),data[i][j+2]);
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else if(component=='N')
					{
						avg= min(min(data[i][j],data[i][j+1]),data[i][j+2]);
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else
					{
						SciaRegs.SCITXBUF=(char)data[i][j];				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
				}
				
			}
		}
		Wait_For_Start();	
	}
}
void Negation_Gray(char component) 
{
	int i,j,k;
	int comp_select;
	unsigned int avg;
	
	DestAddr = &A0;
	Wait_For_Start();
	
	if(component=='R')
	{
		Send_Image_Name("Output_Negation_Gray_Image_R");
		comp_select=2;
	}
	else if(component=='G')
	{
		Send_Image_Name("Output_Negation_Gray_Image_G");
		comp_select=1;
	}
	
	else if(component=='B')
	{
		Send_Image_Name("Output_Negation_Gray_Image_B");
		comp_select=0;
	}
	else if(component=='A')
	{
		Send_Image_Name("Output_Negation_Gray_Image_Avg");
		comp_select=0;
	}
	else if(component=='Y')
	{
		Send_Image_Name("Output_Negation_Gray_Image_Y");
		comp_select=0;	
	}
	else if(component=='X')  //Using maX Component
	{
		Send_Image_Name("Output_Negation_Gray_Image_maX");
		comp_select=0;	
	}
	else if(component=='N')  //Using miN Component
	{
		Send_Image_Name("Output_Negation_Gray_Image_miN");
		comp_select=0;	
	}
	else
	{
		return;
	}
	
	SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if((j-comp_select)%3==0)
				{
					if(component=='A')
					{
						avg=(data[i][j]+data[i][j+1]+data[i][j+2])/3;
						SciaRegs.SCITXBUF=(char)(255-avg);				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
					
					else if(component=='Y')
					{
						avg= 0.11*(float)data[i][j]+0.59*(float)data[i][j+1]+0.3*(float)data[i][j+2];
						SciaRegs.SCITXBUF=(char)(255-avg);				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else if(component=='X')
					{
						avg= max(max(data[i][j],data[i][j+1]),data[i][j+2]);
						SciaRegs.SCITXBUF=(char)(255-avg);				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else if(component=='N')
					{
						avg= min(min(data[i][j],data[i][j+1]),data[i][j+2]);
						SciaRegs.SCITXBUF=(char)(255-avg);				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else
					{
						SciaRegs.SCITXBUF=(char)(255-data[i][j]);				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
				}
				
			}
		}
		Wait_For_Start();	
	}
}
void Threshold_Image(char component, unsigned int threshold) 
{
	int i,j,k;
	int comp_select;
	unsigned int avg;
	
	DestAddr = &A0;
	Wait_For_Start();
	
	if(component=='R')
	{
		Send_Image_Name("Output_Threshold_Image_R");
		comp_select=2;
	}
	else if(component=='G')
	{
		Send_Image_Name("Output_Threshold_Image_G");
		comp_select=1;
	}
	
	else if(component=='B')
	{
		Send_Image_Name("Output_Threshold_Image_B");
		comp_select=0;
	}
	else if(component=='A')
	{
		Send_Image_Name("Output_Threshold_Image_Avg");
		comp_select=0;
	}
	
	else if(component=='Y')
	{
		Send_Image_Name("Output_Threshold_Image_Y");
		comp_select=0;
	}
	else if(component=='X')
	{
		Send_Image_Name("Output_Threshold_Image_maX");
		comp_select=0;
	}
	else if(component=='N')
	{
		Send_Image_Name("Output_Threshold_Image_miN");
		comp_select=0;
	}
	else
	{
		return;
	}
	
	SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if((j-comp_select)%3==0)
				{
					if(component=='A')
					{
							avg=(data[i][j]+data[i][j+1]+data[i][j+2])/3;
							if(avg<threshold)
							{
								SciaRegs.SCITXBUF=(char)0;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
						
							if(avg>=threshold)
							{
								SciaRegs.SCITXBUF=(char)255;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
					}
					
					else if(component=='Y')
					{
							avg= 0.11*(float)data[i][j]+0.59*(float)data[i][j+1]+0.3*(float)data[i][j+2];
							if(avg<threshold)
							{
								SciaRegs.SCITXBUF=(char)0;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
						
							if(avg>=threshold)
							{
								SciaRegs.SCITXBUF=(char)255;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
					}
					else if(component=='X')
					{
							avg= max(max(data[i][j],data[i][j+1]),data[i][j+2]);
							if(avg<threshold)
							{
								SciaRegs.SCITXBUF=(char)0;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
						
							if(avg>=threshold)
							{
								SciaRegs.SCITXBUF=(char)255;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
					}
					
					else if(component=='N')
					{
							avg= min(min(data[i][j],data[i][j+1]),data[i][j+2]);
							if(avg<threshold)
							{
								SciaRegs.SCITXBUF=(char)0;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
						
							if(avg>=threshold)
							{
								SciaRegs.SCITXBUF=(char)255;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
					}
					else
					{
							if(data[i][j]<threshold)
							{
								SciaRegs.SCITXBUF=(char)0;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
						
							if(data[i][j]>=threshold)
							{
								SciaRegs.SCITXBUF=(char)255;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
					
					
					}
				}
				
			}
		}
		Wait_For_Start();	
	}
}


void Inverse_Threshold_Image(char component, unsigned int threshold) 
{
	int i,j,k;
	int comp_select;
	unsigned int avg;
	
	DestAddr = &A0;
	Wait_For_Start();
	
	if(component=='R')
	{
		Send_Image_Name("Output_Inverse_Threshold_Image_R");
		comp_select=2;
	}
	else if(component=='G')
	{
		Send_Image_Name("Output_Inverse_Threshold_Image_G");
		comp_select=1;
	}
	
	else if(component=='B')
	{
		Send_Image_Name("Output_Inverse_Threshold_Image_B");
		comp_select=0;
	}
	else if(component=='A')
	{
		Send_Image_Name("Output_Inverse_Threshold_Image_Avg");
		comp_select=0;
	}
	
	else if(component=='Y')
	{
		Send_Image_Name("Output_Inverse_Threshold_Image_Y");
		comp_select=0;
	}
	else if(component=='X')
	{
		Send_Image_Name("Output_Inverse_Threshold_Image_maX");
		comp_select=0;
	}
	else if(component=='N')
	{
		Send_Image_Name("Output_Inverse_Threshold_Image_miN");
		comp_select=0;
	}
	else
	{
		return;
	}
	
	SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if((j-comp_select)%3==0)
				{
					if(component=='A')
					{
							avg=(data[i][j]+data[i][j+1]+data[i][j+2])/3;
							if(avg<threshold)
							{
								SciaRegs.SCITXBUF=(char)255;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
						
							if(avg>=threshold)
							{
								SciaRegs.SCITXBUF=(char)0;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
					}
					
					else if(component=='Y')
					{
							avg= 0.11*(float)data[i][j]+0.59*(float)data[i][j+1]+0.3*(float)data[i][j+2];
							if(avg<threshold)
							{
								SciaRegs.SCITXBUF=(char)255;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
						
							if(avg>=threshold)
							{
								SciaRegs.SCITXBUF=(char)0;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
					}
					else if(component=='X')
					{
							avg= max(max(data[i][j],data[i][j+1]),data[i][j+2]);
							if(avg<threshold)
							{
								SciaRegs.SCITXBUF=(char)255;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
						
							if(avg>=threshold)
							{
								SciaRegs.SCITXBUF=(char)0;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
					}
					
					else if(component=='N')
					{
							avg= min(min(data[i][j],data[i][j+1]),data[i][j+2]);
							if(avg<threshold)
							{
								SciaRegs.SCITXBUF=(char)255;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
						
							if(avg>=threshold)
							{
								SciaRegs.SCITXBUF=(char)0;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
					}
					else
					{
							if(data[i][j]<threshold)
							{
								SciaRegs.SCITXBUF=(char)255;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
						
							if(data[i][j]>=threshold)
							{
								SciaRegs.SCITXBUF=(char)0;				// send single character
				 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
							}
					
					
					}
				}
				
			}
		}
		Wait_For_Start();	
	}
}







void CMY_Image(char component) 
{
	int i,j,k;
	int comp_select;
	//unsigned int avg;
	
	DestAddr = &A0;
	Wait_For_Start();
	
	if(component=='C')
	{
		Send_Image_Name("Output_CyanComp");
		comp_select=2;
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else if(component=='M')
	{
		Send_Image_Name("Output_MagentaComp");
		comp_select=1;
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	
	else if(component=='Y')
	{
		Send_Image_Name("Output_YComp");
		comp_select=0;
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else if(component=='T')
	{
		Send_Image_Name("CMY_Image");
		comp_select=0;
		SciaRegs.SCITXBUF=(char)0x41;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else
	{
		return;
	}
		
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if(component=='T')
				{
					
					
						SciaRegs.SCITXBUF=(char)(255-data[i][j]);				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
				
				}
				else if((j-comp_select)%3==0)
				{
					
					
						SciaRegs.SCITXBUF=(char)(255-data[i][j]);				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
				
				}
				
			}
		}
		Wait_For_Start();	
	}
}

void Bit_Plane_Slicing(char component, int Bit_Plane)
{
int i,j,k;
	int comp_select;
	unsigned int avg;
	
	DestAddr = &A0;
	Wait_For_Start();
	
	if(component=='R')
	{
		char text[] = "Bit_Plane_R";
		text[11] = Bit_Plane + '0';
		text[12]='\0';
		Send_Image_Name(text);
		comp_select=2;
	}
	else if(component=='G')
	{
		char text[] = "Bit_Plane_G";
		text[11] = Bit_Plane + '0';
		text[12]='\0';
		Send_Image_Name(text);
		comp_select=1;
	}
	
	else if(component=='B')
	{
		char text[] = "Bit_Plane_B";
		text[11] = Bit_Plane + '0';
		text[12]='\0';
		Send_Image_Name(text);
		comp_select=0;
	}
	else if(component=='A')
	{
		char text[] = "Bit_Plane_A";
		text[11] = Bit_Plane + '0';
		text[12]='\0';
		Send_Image_Name(text);
		SciaRegs.SCITXBUF=(char)255;				// send single character
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
		
		comp_select=0;
	}
	else if(component=='Y')
	{
		char text[] = "Bit_Plane_Y";
		text[11] = Bit_Plane + '0';
		text[12]='\0';
		Send_Image_Name(text);
		comp_select=0;
	}
	else if(component=='X')
	{
		char text[] = "Bit_Plane_X";
		text[11] = Bit_Plane + '0';
		text[12]='\0';
		Send_Image_Name(text);
		comp_select=0;
	}
	else if(component=='N')
	{
		char text[] = "Bit_Plane_N";
		text[11] = Bit_Plane + '0';
		text[12]='\0';
		Send_Image_Name(text);
		comp_select=0;
	}
	else
	{
		return;
	}
	
	SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if((j-comp_select)%3==0)
				{
					if(component=='A')
					{
						avg=(data[i][j]+data[i][j+1]+data[i][j+2])/3;
						if(dec_binary_check(avg ,Bit_Plane)==1)
						{
						SciaRegs.SCITXBUF=(char)255;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
						else
						{
							SciaRegs.SCITXBUF=(char)0;				// send single character
			 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
					}
					
					else if(component=='Y')
					{
						avg= 0.11*(float)data[i][j]+0.59*(float)data[i][j+1]+0.3*(float)data[i][j+2];
						if(dec_binary_check(avg ,Bit_Plane)==1)
						{
						SciaRegs.SCITXBUF=(char)255;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
						else
						{
							SciaRegs.SCITXBUF=(char)0;				// send single character
			 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
					}
					else if(component=='X')
					{
						avg= max(max(data[i][j],data[i][j+1]),data[i][j+2]);
						if(dec_binary_check(avg ,Bit_Plane)==1)
						{
						SciaRegs.SCITXBUF=(char)255;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
						else
						{
							SciaRegs.SCITXBUF=(char)0;				// send single character
			 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
					}
					else if(component=='N')
					{
						avg= min(min(data[i][j],data[i][j+1]),data[i][j+2]);
						if(dec_binary_check(avg ,Bit_Plane)==1)
						{
						SciaRegs.SCITXBUF=(char)255;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
						else
						{
							SciaRegs.SCITXBUF=(char)0;				// send single character
			 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
					}
					else
					{
						if(dec_binary_check(data[i][j] ,Bit_Plane)==1)
						{
						SciaRegs.SCITXBUF=(char)255;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
						else
						{
							SciaRegs.SCITXBUF=(char)0;				// send single character
			 				while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
					}
				}
				
			}
		}
		Wait_For_Start();	
	}
	
}

int dec_binary_check(int n ,int Bit_Plane)
{
int a[10],i;
for(i=0;i<10;i++)
{
	a[i]=0;
}
for(i=0;n>0;i++)    
{    
a[i]=n%2;    
n=n/2;    
}    
return a[Bit_Plane];
}	

float max(float a, float b)
{
	if(a>b)
	return a;
	
	else
	return b;
}


float min(float a, float b)
{
	if(a<b)
	return a;
	
	else
	return b;
}


void Filter(char type)
{
	int Mask[3][3];
	int Neighbor[3][3];
	int avg,l,m,i,j,k;
	int im_width= 960;		
	int im_height= 20;
	int rpeat= 14 ;
	int temp[9],temp_i=0,temp_j=0,temp_k=0;
	int max=-650;
	int pos;
	count=0;
	Wait_For_Start(); 
	 
	

	if(type=='H')			//HPF
	{
		//(0,-1,0,  -1,4,-1,  0,-1,0)
		//(-1,-2,-1, -2,12,-2,  -1,-2,-1)
		
	Mask[0][0]=-1;
	Mask[0][1]=-1;
	Mask[0][2]=-1;
	
	Mask[1][0]=-1;
	Mask[1][1]=8;
	Mask[1][2]=-1;
	
	Mask[2][0]=-1;
	Mask[2][1]=-1;
	Mask[2][2]=-1; 
	Send_Image_Name("Output_High_Pass_Filter"); 
	}
	else if(type=='L') //Averaging LPF Used
	{
	Mask[0][0]=1;
	Mask[0][1]=1;
	Mask[0][2]=1;
	
	Mask[1][0]=1;
	Mask[1][1]=1;
	Mask[1][2]=1;
	
	Mask[2][0]=1;
	Mask[2][1]=1;
	Mask[2][2]=1;
	Send_Image_Name("Output_Averaging_LPF"); 
	}
	else if(type=='B')  //High Boost=HPF+Background 
	{
	Mask[0][0]=-1;
	Mask[0][1]=-1;
	Mask[0][2]=-1;
	
	Mask[1][0]=-1;
	Mask[1][1]=9;
	Mask[1][2]=-1;
	
	Mask[2][0]=-1;
	Mask[2][1]=-1;
	Mask[2][2]=-1;
	Send_Image_Name("Output_High_Boost_Filter"); 
	}
	else if(type=='O')  //Blank Mask
	{
	
	Send_Image_Name("Output_Order_Statistic_LPF"); 
	}
	
	SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	 	
	DestAddr = &A0;
	for(l=0;l<3;l++)
	{
		for(m=0;m<3;m++)
		{
			Neighbor[l][m]=0;
			
		}
	}
	
	
	
		for(k=0;k<rpeat;k++)  
		{
				
				if(k==0)
				{
					Read_FLASH(&DestAddr);
					i=0	;
					GpioDataRegs.GPCCLEAR.bit.GPIO82 = 1;
				}
				else
				{
					DestAddr=DestAddr-1280;
					Read_FLASH(&DestAddr);
					i=1;
					GpioDataRegs.GPCSET.bit.GPIO82 = 1;
				}
			
				for(;i<(im_height-1);i++)
				{
					for(j=0;j<im_width;j++)
					{
						count++;
						
						
						if(j%3==0)
						{
									for(l=0;l<3;l++)
									{
										for(m=0;m<3;m++)
										{
											if(  ((i+l-1)<0) || ((i+l-1)>=img_height) || ((j+2*m-2)<0) || ((j+2*m-2)>=img_width)  )
											{
											Neighbor[l][m]=0;
											}
											else
											{
											avg=0.11*(float)(data[i+l-1][j+2*m-2])+0.59*(float)(data[i+l-1][j+2*m-1])+0.3*(float)(data[i+l-1][j+2*m]);
											Neighbor[l][m]=avg;						
											//Neighbor[l][m]=data[i+l-1][j+2*m-2];
											}
										}
									}
										if(type=='O')
										{
											temp_k=0;
											for ( temp_i=0; temp_i<3 ; temp_i++)
											{
												for ( temp_j=0; temp_j<3; temp_j++)
												{
													temp[temp_k]=Neighbor[temp_i][temp_j];
													temp_k++;
												}
											}
											
											for(temp_i=0;temp_i<9;temp_i++)
											{
												max=temp[temp_i];
												for(temp_j=temp_i;temp_j<9;temp_j++)
												{
													if(temp[temp_j]>max)
													{
														max=temp[temp_j];
														pos=temp_j;
													}
														
												}
												temp[pos]=temp[temp_i];
												temp[temp_i]=max;
												
											}
											avg=temp[5];
											
										
										}
									
									else
									{	
									avg=(float)(Mask[0][0]*Neighbor[0][0]+Mask[0][1]*Neighbor[0][1]+Mask[0][2]*Neighbor[0][2]+Mask[1][0]*Neighbor[1][0]+Mask[1][1]*Neighbor[1][1]+Mask[1][2]*Neighbor[1][2]+Mask[2][0]*Neighbor[2][0]+Mask[2][1]*Neighbor[2][1]+Mask[2][2]*Neighbor[2][2])/9.0;
									}
									
									
									if(avg<0)
									{
									avg=0;
									exceed0++;
									}
									
									if(avg>255)
									{
									avg=255;
									exceed255++;
									}
									
									SciaRegs.SCITXBUF=(char)avg;				// send single character
							 		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
						if(count%19200==0)
						{
							Wait_For_Start();	
						}
						if(count>=230400)
						break;
					}
					if(count>=230400)
					break;
				}
				if(count>=230400)
				break;
				
		}
	
}	
	
void HSV(char component)
{
	int i,j,k,avg;
	float pi=3.14;
	float H,S,V;
	float R,G,B;
	DestAddr = &A0;
	Wait_For_Start();
	
	
	if(component=='H')
	{
		Send_Image_Name("Output_Hue_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else if(component=='S')
	{
		Send_Image_Name("Output_Saturation_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	
	else if(component=='V')
	{
		Send_Image_Name("Output_Value_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else if(component=='T')
	{
		Send_Image_Name("HSV_Image");
		SciaRegs.SCITXBUF=(char)0x41;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else
	{
		return;
	}
		
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
						
						R=data[i][j+2];
						G=data[i][j+1];
						B=data[i][j];
						R=R/255.0;
						G=G/255.0;
						B=B/255.0;
						/*
						V = max(max(R,G),B);
						if(V!=0)
						{
							S = V-min(min(R,G),B);
						}
						else
						{
							S=0;
						}
						if(V==R)
						{
							H=(60.0*(G-B))/(V-min(min(R,G),B));
						}
						
						else if(V==G)
						{
							(120+60.0*(B-R))/(V-min(min(R,G),B));
						}
						else if(V==B)
						{
							(240+60.0*(R-G))/(V-min(min(R,G),B));
						}
						if(H<0)
						{
							H=H+360;
						}
						H=H/2.0;
						S=S*255.0;
						V=V*255.0;
						*/
						
						
						
						H=(180.0/pi) * ( acos((0.5*(R-G)+(R-B)) / pow(((R-B)*(R-B)+(R-B)*(G-B)),0.5)) );
						if(B<=G)
						{
							H=H;
						}
						else if(B>G)
						{
							H=360.0-avg;
						}
						H= (float)(H)*255.0/360.0;
						S= 1-((3.0*min(min(R,G),B))/(R+G+B));
						
						V=(R+G+B)/3;
						
						S=S*255.0;
						V=V*255.0;
						
						
						
						
				if((j%3==0) && component=='H' )
				{
						
						
						avg=H;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty				
				
				}
				
				else if((j%3==0) && component=='S' )
				{
						
						
						
						avg=S;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
						while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty				
				
				}
				else if((j%3==0) && component=='V')
				{
						avg=V;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty				
				
				}
				
				else if((j%3==0) && component=='T')
				{
						
						avg=V;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty	
			 			
			 			avg=S;
			 			SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
			 			
			 			avg=H;
			 			SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty	
			 			
			 			
			 	}
				
				}
			}
		Wait_For_Start();	
		}
	
}	





void Gray_Image_Quantization(char component, int No_of_bits) 
{
	int i,j,k;
	//int bit;
	int comp_select;
	unsigned int avg;
	
	DestAddr = &A0;
	Wait_For_Start();
	
	if(component=='R')
	{
		char text[] = "X_Bit_Gray_Image_R";
		text[0] = No_of_bits + '0';
		text[18]='\0';
		Send_Image_Name(text);
		comp_select=2;
	}
	else if(component=='G')
	{
		char text[] = "X_Bit_Gray_Image_G";
		text[0] = No_of_bits + '0';
		text[18]='\0';
		Send_Image_Name(text);
		comp_select=1;
	}
	
	else if(component=='B')
	{
		char text[] = "X_Bit_Gray_Image_B";
		text[0] = No_of_bits + '0';
		text[18]='\0';
		Send_Image_Name(text);
		comp_select=0;
	}
	else if(component=='A')
	{
		char text[] = "X_Bit_Gray_Image_Avg";
		text[0] = No_of_bits + '0';
		text[20]='\0';
		Send_Image_Name(text);
		comp_select=0;
	}
	else if(component=='Y')
	{
		char text[] = "X_Bit_Gray_Image_Y";
		text[0] = No_of_bits + '0';
		text[18]='\0';
		Send_Image_Name(text);
		comp_select=0;	
	}
	else if(component=='X')  //Using maX Component
	{
		char text[] = "X_Bit_Gray_Image_maX";
		text[0] = No_of_bits + '0';
		text[18]='\0';
		Send_Image_Name(text);
		comp_select=0;	
	}
	else if(component=='N')  //Using miN Component
	{
		char text[] = "X_Bit_Gray_Image_miN";
		text[0] = No_of_bits + '0';
		text[18]='\0';
		Send_Image_Name(text);
		comp_select=0;	
	}
	else
	{
		return;
	}
	
	SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if((j-comp_select)%3==0)
				{
					if(component=='A')
					{
						avg=(data[i][j]+data[i][j+1]+data[i][j+2])/3;
						avg=avg>>(8-No_of_bits);
						avg=avg<<(8-No_of_bits);
						
						if(avg>255)
						avg=255;
						
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
					
					else if(component=='Y')
					{
						avg= 0.11*(float)data[i][j]+0.59*(float)data[i][j+1]+0.3*(float)data[i][j+2];
						avg=avg>>(8-No_of_bits);
						avg=avg<<(8-No_of_bits);
						
						if(avg>255)
						avg=255;
						
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else if(component=='X')
					{
						avg= max(max(data[i][j],data[i][j+1]),data[i][j+2]);
						avg=avg>>(8-No_of_bits);
						avg=avg<<(8-No_of_bits);
						
						if(avg>255)
						avg=255;
						
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else if(component=='N')
					{
						avg= min(min(data[i][j],data[i][j+1]),data[i][j+2]);
						avg=avg>>(8-No_of_bits);
						avg=avg<<(8-No_of_bits);
						
						if(avg>255)
						avg=255;
						
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else
					{
						SciaRegs.SCITXBUF=(char)data[i][j];
						avg=avg>>(8-No_of_bits);
						avg=avg<<(8-No_of_bits);
						
						if(avg>255)
						avg=255;
						
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
				}
				
			}
		}
		Wait_For_Start();	
	}
}

void Image_Sampling(int sampling_factor, char type_of_op_image) 
{
	int i,j,k,l;
	int avg;
	
	DestAddr = &A0;
	Wait_For_Start();
	
	
	
	if(type_of_op_image=='G')
	{
		char text[] = "Gray_Image_Sample_Factor_X";
		text[25] = sampling_factor + '0';
		text[26]='\0';
		Send_Image_Name(text);
		SciaRegs.SCITXBUF=(char)0x42;				// send 'A' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
		
	}
	else if(type_of_op_image=='C')
	{
		char text[] = "Color_Image_Sample_Factor_X";
		text[25] = sampling_factor + '0';
		text[26]='\0';
		Send_Image_Name(text);
		SciaRegs.SCITXBUF=(char)0x41;				// send 'A' for 320*240*3
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else
	{
		return;
	}
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if((j%(3*sampling_factor)==0) && (type_of_op_image=='G'))
				{
					for(l=0;l<sampling_factor;l++)
					{
					avg= 0.11*(float)data[i][j]+0.59*(float)data[i][j+1]+0.3*(float)data[i][j+2];
					SciaRegs.SCITXBUF=(char)avg;				// send single character
		 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
				}
				
				if((j%(3*sampling_factor)==0) && (type_of_op_image=='C'))
				{
					for(l=0;l<sampling_factor;l++)
					{
					SciaRegs.SCITXBUF=(char)data[i][j];				// send single character
		 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
		 			SciaRegs.SCITXBUF=(char)data[i][j+1];				// send single character
		 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
		 			SciaRegs.SCITXBUF=(char)data[i][j+2];				// send single character
		 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
				}
					
			}
		}
		Wait_For_Start();	
	}
}

void histogram_equalization(char component)
{
	int L=256;
	float Y;
	int i,j,k;
	int comp_select;
	unsigned int avg;
	count_check=0;
	
	DestAddr = &A0;
	for(i=0;i<L;i++)
	{
		 n_PDF_CDF_LSK_RF[i]=0;
	}
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if(j%3==0)
				{
				Y = 0.11*(float)data[i][j]+0.59*(float)data[i][j+1]+0.3*(float)data[i][j+2];
				
				if(Y>255)
				Y=255;
				
				if(Y<0)
				Y=0;
				
				n_PDF_CDF_LSK_RF[(int)Y]=n_PDF_CDF_LSK_RF[(int)Y]+1; //Calculate Nk
				
				}
					
			}
		}	
	}
	Y=0;
	for(i=0;i<L;i++)  //Calculate Total Nk
	{
		 Y = Y + n_PDF_CDF_LSK_RF[i];
	}
	
	for(i=0;i<L;i++)  //Calculate PDF
	{
		 n_PDF_CDF_LSK_RF[i]=n_PDF_CDF_LSK_RF[i]/Y;
	}
	
	for(i=0;i<L;i++)  //Calculate CDF
	{
		 n_PDF_CDF_LSK_RF[i+1] = n_PDF_CDF_LSK_RF[i] + n_PDF_CDF_LSK_RF[i+1] ;
	}
	
	for(i=0;i<L;i++)  //Calculate (L-1)*CDF
	{
		 n_PDF_CDF_LSK_RF[i] = (L-1)* n_PDF_CDF_LSK_RF[i] ;
	}
	
	for(i=0;i<L;i++)  //Calculate (L-1)*CDF
	{
		 n_PDF_CDF_LSK_RF[i] = (int)(n_PDF_CDF_LSK_RF[i]) ;
	}


	DestAddr = &A0;
	Wait_For_Start();
	//Send_Image_Name("Output_Histogram_Equalized_Y");
	count_check=1;
	comp_select=0;	
	
	if(component=='R')
	{
		Send_Image_Name("Output_Histogram_Equalized_R");
		comp_select=2;
	}
	else if(component=='G')
	{
		Send_Image_Name("Output_Histogram_Equalized_G");
		comp_select=1;
	}
	
	else if(component=='B')
	{
		Send_Image_Name("Output_Histogram_Equalized_B");
		comp_select=0;
	}
	else if(component=='A')
	{
		Send_Image_Name("Output_Histogram_Equalized_Avg");
		comp_select=0;
	}
	else if(component=='Y')
	{
		Send_Image_Name("Output_Histogram_Equalized_Y");
		comp_select=0;	
	}
	else if(component=='X')  //Using maX Component
	{
		Send_Image_Name("Output_Histogram_Equalized_maX");
		comp_select=0;	
	}
	else if(component=='N')  //Using miN Component
	{
		Send_Image_Name("Output_Histogram_Equalized_miN");
		comp_select=0;	
	}
	else
	{
		return;
	}
	count_check=3;
	SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	count_check=4;
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if((j-comp_select)%3==0)
				{
					if(component=='A')
					{
						avg=(data[i][j]+data[i][j+1]+data[i][j+2])/3;
						if(avg>255)
						avg=255;
						avg=n_PDF_CDF_LSK_RF[avg];
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
					
					else if(component=='Y')
					{
						count_check=5;
						avg= 0.11*(float)data[i][j]+0.59*(float)data[i][j+1]+0.3*(float)data[i][j+2];
						if(avg>255)
						avg=255;
						avg=n_PDF_CDF_LSK_RF[avg];
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
			 			count_check=6;
						
					}
					else if(component=='X')
					{
						avg= max(max(data[i][j],data[i][j+1]),data[i][j+2]);
						if(avg>255)
						avg=255;
						avg=n_PDF_CDF_LSK_RF[avg];
						
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else if(component=='N')
					{
						avg= min(min(data[i][j],data[i][j+1]),data[i][j+2]);
						if(avg>255)
						avg=255;
						avg=n_PDF_CDF_LSK_RF[avg];
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else
					{
						SciaRegs.SCITXBUF=(char)data[i][j];				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
				}
				
			}
		}
		Wait_For_Start();	
	}
	
}

void Contrast_Stretching(char component, float UT, float LT, float SLOPE_L,float SLOPE_M,float SLOPE_N)
{
	int i,j,k;
	int comp_select;
	unsigned int avg;
	
	DestAddr = &A0;
	Wait_For_Start();
	
	if(component=='R')
	{
		Send_Image_Name("Contrast_Stretched_Gray_Image_R");
		comp_select=2;
	}
	else if(component=='G')
	{
		Send_Image_Name("Contrast_Stretched_Gray_Image_G");
		comp_select=1;
	}
	
	else if(component=='B')
	{
		Send_Image_Name("Contrast_Stretched_Gray_Image_B");
		comp_select=0;
	}
	else if(component=='A')
	{
		Send_Image_Name("Contrast_Stretched_Gray_Image_Avg");
		comp_select=0;
	}
	else if(component=='Y')
	{
		Send_Image_Name("Contrast_Stretched_Gray_Image_Y");
		comp_select=0;	
	}
	else if(component=='X')  //Using maX Component
	{
		Send_Image_Name("Contrast_Stretched_Gray_Image_maX");
		comp_select=0;	
	}
	else if(component=='N')  //Using miN Component
	{
		Send_Image_Name("Contrast_Stretched_Gray_Image_miN");
		comp_select=0;	
	}
	else
	{
		return;
	}
	
	SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
				if((j-comp_select)%3==0)
				{
					if(component=='A')
					{
						avg=(data[i][j]+data[i][j+1]+data[i][j+2])/3;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
					
					else if(component=='Y')
					{
						avg= 0.11*(float)data[i][j]+0.59*(float)data[i][j+1]+0.3*(float)data[i][j+2];
						avg=contrast_stretch_calc(avg,UT,LT,SLOPE_L,SLOPE_M,SLOPE_N);
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else if(component=='X')
					{
						avg= max(max(data[i][j],data[i][j+1]),data[i][j+2]);
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else if(component=='N')
					{
						avg= min(min(data[i][j],data[i][j+1]),data[i][j+2]);
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						
					}
					else
					{
						SciaRegs.SCITXBUF=(char)data[i][j];				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
					}
				}
				
			}
		}
		Wait_For_Start();	
	}
	
}


float contrast_stretch_calc(float r,float UT, float LT, float SLOPE_L,float SLOPE_M,float SLOPE_N)
{
	if(r<=LT)
	{
		r=SLOPE_L*r;
	}
	else if(r<=UT)
	{
		r=SLOPE_M*(r-LT)+SLOPE_L*LT;
	}
	else
	{
		r=SLOPE_M*(r-UT)+SLOPE_L*LT+SLOPE_M*(UT-LT);
	}
	return r;
}


void Edge_Detection(char type)
{
	int Mask[3][3];
	int Neighbor[3][3];
	int avg,l,m,i,j,k;
	int im_width= 960;		
	int im_height= 20;
	int rpeat= 14 ;
	//int temp[9],temp_i=0,temp_j=0,temp_k=0;
	//int max=-650;
	//int pos;
	count=0;
	Wait_For_Start(); 
	 
	

	if(type=='O')			
	{	
	Mask[0][0]=0;
	Mask[0][1]=0;
	Mask[0][2]=0;
	
	Mask[1][0]=0;
	Mask[1][1]=2;
	Mask[1][2]=-1;
	
	Mask[2][0]=0;
	Mask[2][1]=-1;
	Mask[2][2]=0; 
	Send_Image_Name("Ordinary_Mask_Edge_Image"); 
	}
	else if(type=='R')			
	{	
	Mask[0][0]=0;
	Mask[0][1]=0;
	Mask[0][2]=0;
	
	Mask[1][0]=0;
	Mask[1][1]=1;
	Mask[1][2]=1;
	
	Mask[2][0]=0;
	Mask[2][1]=-1;
	Mask[2][2]=-1; 
	Send_Image_Name("Robert_Mask_Edge_Image"); 
	}
	else if(type=='S') //Averaging LPF Used
	{
	Mask[0][0]=-2;
	Mask[0][1]=-2;
	Mask[0][2]=0;
	
	Mask[1][0]=-2;
	Mask[1][1]=0;
	Mask[1][2]=2;
	
	Mask[2][0]=0;
	Mask[2][1]=2;
	Mask[2][2]=2;
	Send_Image_Name("Sobel_Mask_Edge_Image"); 
	}
	else if(type=='P')  //High Boost=HPF+Background 
	{
	Mask[0][0]=-2;
	Mask[0][1]=-1;
	Mask[0][2]=0;
	
	Mask[1][0]=-1;
	Mask[1][1]=0;
	Mask[1][2]=1;
	
	Mask[2][0]=0;
	Mask[2][1]=1;
	Mask[2][2]=2;
	Send_Image_Name("Prewitt_Mask_Edge_Image"); 
	}
	
	
	SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	 	
	DestAddr = &A0;
	for(l=0;l<3;l++)
	{
		for(m=0;m<3;m++)
		{
			Neighbor[l][m]=0;
			
		}
	}
	
	
	
		for(k=0;k<rpeat;k++)  
		{
				
				if(k==0)
				{
					Read_FLASH(&DestAddr);
					i=0	;
					GpioDataRegs.GPCCLEAR.bit.GPIO82 = 1;
				}
				else
				{
					DestAddr=DestAddr-1280;
					Read_FLASH(&DestAddr);
					i=1;
					GpioDataRegs.GPCSET.bit.GPIO82 = 1;
				}
			
				for(;i<(im_height-1);i++)
				{
					for(j=0;j<im_width;j++)
					{
						count++;
						
						
						if(j%3==0)
						{
									for(l=0;l<3;l++)
									{
										for(m=0;m<3;m++)
										{
											if(  ((i+l-1)<0) || ((i+l-1)>=img_height) || ((j+2*m-2)<0) || ((j+2*m-2)>=img_width)  )
											{
											Neighbor[l][m]=0;
											}
											else
											{
											avg=0.11*(float)(data[i+l-1][j+2*m-2])+0.59*(float)(data[i+l-1][j+2*m-1])+0.3*(float)(data[i+l-1][j+2*m]);
											Neighbor[l][m]=avg;						
											//Neighbor[l][m]=data[i+l-1][j+2*m-2];
											}
										}
									}
									if(type=='O' || type=='R')	
									{	
									avg=(float)(Mask[0][0]*Neighbor[0][0]+Mask[0][1]*Neighbor[0][1]+Mask[0][2]*Neighbor[0][2]+Mask[1][0]*Neighbor[1][0]+Mask[1][1]*Neighbor[1][1]+Mask[1][2]*Neighbor[1][2]+Mask[2][0]*Neighbor[2][0]+Mask[2][1]*Neighbor[2][1]+Mask[2][2]*Neighbor[2][2])/4.0;
									}
									
									else	
									{	
									avg=(float)(Mask[0][0]*Neighbor[0][0]+Mask[0][1]*Neighbor[0][1]+Mask[0][2]*Neighbor[0][2]+Mask[1][0]*Neighbor[1][0]+Mask[1][1]*Neighbor[1][1]+Mask[1][2]*Neighbor[1][2]+Mask[2][0]*Neighbor[2][0]+Mask[2][1]*Neighbor[2][1]+Mask[2][2]*Neighbor[2][2])/9.0;
									}
									
									
									if(avg<0)
									{
									avg=0;
									exceed0++;
									}
									
									if(avg>255)
									{
									avg=255;
									exceed255++;
									}
									
									SciaRegs.SCITXBUF=(char)avg;				// send single character
							 		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
						}
						if(count%19200==0)
						{
							Wait_For_Start();	
						}
						if(count>=230400)
						break;
					}
					if(count>=230400)
					break;
				}
				if(count>=230400)
				break;
				
		}
	
}	


void NTSC(char component)
{
	int i,j,k,avg;
	double Y,I,Q;
	double R,G,B;
	DestAddr = &A0;
	Wait_For_Start();
	
	
	if(component=='Y')
	{
		Send_Image_Name("YIQ_Y_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else if(component=='I')
	{
		Send_Image_Name("YIQ_I_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	
	else if(component=='Q')
	{
		Send_Image_Name("YIQ_Q_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else if(component=='T')
	{
		Send_Image_Name("YIQ_Image");
		SciaRegs.SCITXBUF=(char)0x41;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else
	{
		return;
	}
		
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
						
						R=data[i][j+2];
						G=data[i][j+1];
						B=data[i][j];
						R=R/255.0;
						G=G/255.0;
						B=B/255.0;
						
						Y=0.299*R + 0.587*G + 0.114*B;
						I=0.596*R - 0.274*G - 0.322*B;
						Q=0.211*R - 0.523*G + 0.312*B;
						
						
						Y=Y;
						I=(I+0.5957)/(2*0.5957);
						Q=(Q+0.5226)/(2*0.5226);
						
						Y=255*Y;
						I=255*I;
						Q=255*Q;
						
				if((j%3==0) && component=='Y' )
				{
						
						
						avg=Y;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty				
				
				}
				
				else if((j%3==0) && component=='I' )
				{
						
						
						
						avg=I;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
						while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty				
				
				}
				else if((j%3==0) && component=='Q')
				{
						avg=Q;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty				
				
				}
				
				else if((j%3==0) && component=='T')
				{
						
						avg=Y;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty	
			 			
			 			avg=I;
			 			SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
			 			
			 			avg=Q;
			 			SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty	
			 			
			 			
			 	}
				
				}
			}
		Wait_For_Start();	
		}
	
}	


void YCbCr(char component)
{
	int i,j,k,avg;
	double Y,Cb,Cr;
	double R,G,B;
	DestAddr = &A0;
	Wait_For_Start();
	
	
	if(component=='Y')
	{
		Send_Image_Name("YCbCr_Y_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else if(component=='b')
	{
		Send_Image_Name("YCbCr_b_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	
	else if(component=='r')
	{
		Send_Image_Name("YCbCr_r_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else if(component=='T')
	{
		Send_Image_Name("YCbCr_Image");
		SciaRegs.SCITXBUF=(char)0x41;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else
	{
		return;
	}
		
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);
		for(i=0;i<img_height;i++)
		{
			for(j=0;j<img_width;j++)
			{
						
						R=data[i][j+2];
						G=data[i][j+1];
						B=data[i][j];
						
						Y  =  0.0  + 0.299*R     + 0.587*G     + 0.114*B;
						Cb = 128.0 - 0.1638736*R - 0.331264*G  + 0.5*B;
						Cr = 128.0 + 0.5*R       - 0.418688*G  - 0.081312*B;
						
				if((j%3==0) && component=='Y' )
				{
						
						
						avg=Y;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty				
				
				}
				
				else if((j%3==0) && component=='b' )
				{
						
						
						
						avg=Cb;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
						while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty				
				
				}
				else if((j%3==0) && component=='r')
				{
						avg=Cr;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty				
				
				}
				
				else if((j%3==0) && component=='T')
				{
						
						avg=Y;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty	
			 			
			 			avg=Cr;
			 			SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
			 			
			 			avg=Cb;
			 			SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty	
			 			
			 			
			 	}
				
				}
			}
		Wait_For_Start();	
		}
	
}	







