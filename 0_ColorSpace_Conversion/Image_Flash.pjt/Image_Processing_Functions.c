#include "DSP2833x_Device.h"
#include <string.h>
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"
#include "stdlib.h"
//#include "complex.h"    /* Standard Library of Complex Numbers */

#define img_width 960		//320*3
#define img_height 20
#define repeat 12 

extern unsigned int data[img_height][img_width];
extern Uint16* DestAddr; 
extern Uint16 A0;

Uint32 count=0;
float WnR[10][10];
float WnI[10][10];
float dataR0[10][10];
float dataI0[10][10];

float dataR1[10][10];
float dataI1[10][10];

float dataR2[10][10];
float dataI2[10][10];

extern void Send_Image_Name(char name[]);
extern void Wait_For_Start(void);
extern void Read_FLASH(Uint16** S_addr);


void Input_Image();
void CMY_Image(char component);
void NTSC(char component);
void HSI(char component);
void YCbCr(char component);
void HSV(char component);
//double DFT(double U, double V);
void DFT_Image();
int dec_binary_check(int n ,int Bit_Plane);
float max(float a, float b);
float min(float a, float b);
void finddata12();
void initWn(void);

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


int dec_binary_check(int n ,int Bit_Plane)
{
int a[10],i;
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

void HSI(char component)
{
	int i,j,k,avg;
	float pi=3.14;
	float H,S,I;
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
	
	else if(component=='I')
	{
		Send_Image_Name("Output_Intensity_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else if(component=='T')
	{
		Send_Image_Name("HSI_Image");
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
							H=360.0-H;
						}
						H= (float)(H)*255.0/360.0;
						S= 1-((3.0*min(min(R,G),B))/(R+G+B));
						
						I=(R+G+B)/3;
						
						S=S*255.0;
						I=I*255.0;
						
						
						
						
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
				else if((j%3==0) && component=='I')
				{
						avg=I;
						SciaRegs.SCITXBUF=(char)avg;				// send single character
			 			while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty				
				
				}
				
				else if((j%3==0) && component=='T')
				{
						
						avg=I;
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

/*
double DFT(double U, double V)
{
	double Fuv_img=0;
	double Fuv_real=0;
	double img_part;
	double real_part;
	double PI=3.141592653589793;
	double M=img_height*repeat;
	double N=img_width;
	double val;
	int i,j,k,x,y;
	int avg;
	DestAddr = &A0;
	Read_FLASH(&DestAddr);
		
		for(i=U;i<(8+U);i++)
		{
			for(j=V;j<(24+V);j+=3)
			{
				//if(j%3==0)
				{
				val=(U*x)/M + (V*y)/N;
				real_part=cos(2*PI*val);
				img_part =(-1)*sin(2*PI*val);
				avg=0.3*(float)data[i][j+2]+0.59*(float)data[i][j+1]+0.11*(float)data[i][j];
				Fuv_img += avg * img_part;
				Fuv_real += avg * real_part;	
				y++;
				}
			}
			x++;
		}	
	
	if((int)Fuv_img!=0)
	{
		exceedimg++;
	}
	
	val=pow( (pow(Fuv_real,2) + pow(Fuv_img,2)) ,0.5);
	
	if(val>255)
	{
	val=255;
	exceed255++;
	}
	if(val<0)
	{
	val=0;
	exceed0++;
	}
	count++;
	return val;
}
*/


void initWn(void)
{
	int k,n;
	int N=10;
	float PI=3.141592653589793;
	
	for(k=0;k<N;k++)
	{
		for(n=0;n<N;n++)
		{
			WnR[k][n]=cos((2.0*PI*n*k)/N);
			WnI[k][n]=(-1)*sin((2.0*PI*n*k)/N);
		}
	}
}
			


void finddata12()
{
	int i, j, k;
	int N=10;

	// Initializing elements of matrix mult to 0.
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			dataR1[i][j] = 0;
			dataI1[i][j] = 0;
			dataR2[i][j] = 0;
			dataI2[i][j] = 0;
			
		}
	}

	// Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
		for(i = 0; i < N; ++i)
		{
			for(j = 0; j <N; ++j)
			{
				for(k=0; k<N; ++k)
				{
					dataR1[i][j] += dataR0[i][k] * WnR[k][j] + dataI0[i][k] * WnI[k][j] ;
					dataI1[i][j] += dataR0[i][k] * WnI[k][j] + dataI0[i][k] * WnR[k][j];
				}
			}
		}
		
		for(i = 0; i < N; ++i)
		{
			for(j = 0; j <N; ++j)
			{
				for(k=0; k<N; ++k)
				{
					dataR2[i][j] += WnR[i][k] * dataR1[k][j] + WnI[i][k] * dataI1[k][j];
					dataI2[i][j] += WnI[i][k] * dataR1[k][j] + WnR[i][k] * dataI1[k][j];
				}
			}
		}
		
}

void DFT_Image()
{
	int i,j,k,l,m;
	unsigned int avg;
	int N=10;
	initWn();
	
	Wait_For_Start();
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			dataR0[i][j] = 0;
			dataI0[i][j] = 0;
			
		}
	}
	
	Send_Image_Name("DFT_of_Input_Image");
	
	SciaRegs.SCITXBUF=(char)0x43;				// send 'B' for 320*240*1
	while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	DestAddr = &A0;
	
	for(k=0;k<repeat;k++)
	{
		Read_FLASH(&DestAddr);	
		for(i=0;i<img_height;i+=10)
		{
			for(j=0;j<img_width;j+=10)
			{
						if(j%3==0)
						{
						for(l=0;l<N;l++)
						{
							for(m=0;m<N;m++)
							{
								dataR0[l][m]=data[i+l][j+m*3];
								dataI0[l][m]=0;
							}
						}
						finddata12();
						
						for(l=0;l<N;l++)
						{
							for(m=0;m<N;m++)
							{
								avg=log(1+sqrt( pow(dataR2[l][m],2)+ pow(dataI2[l][m],2)));
								//avg=(int)sqrt( pow(dataR0[l][m],2));
								//avg=dataR0[l][m];
								//if(avg>3)
								//avg=255;
								SciaRegs.SCITXBUF=(char)avg;				// send single character
			 					while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
			 					count++;
							}
						}
						}
						
			}
		}
		Wait_For_Start();	
	}
	GpioDataRegs.GPCCLEAR.bit.GPIO83 = 1;
}


void HSV(char component)
{
	int i,j,k,avg;
	float pi=3.14;
	float H,S,V;
	float R,G,B;
	float C;
	DestAddr = &A0;
	Wait_For_Start();
	
	
	if(component=='H')
	{
		Send_Image_Name("HSV_Hue_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	else if(component=='S')
	{
		Send_Image_Name("HSV_Saturation_Comp");
		SciaRegs.SCITXBUF=(char)0x42;				// send 'B' for 320*240*1
		while ( SciaRegs.SCICTL2.bit.TXEMPTY == 0); 	//wait for TX -empty
	}
	
	else if(component=='V')
	{
		Send_Image_Name("HSV_Value_Comp");
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
						C=max(max(R,G),B)-min(min(R,G),B);
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
						V = max(max(R,G),B);
						
						if(B<=G)
						{
							H=H;
						}
						else if(B>G)
						{
							H=360.0-avg;
						}
						H= (float)(H)*255.0/360.0;
						
						if(V!=0)
						{
							S = C/V;
						}
						else
						{
							S=0;
						}
						//S= 1-((3.0*min(min(R,G),B))/(R+G+B));
						
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


