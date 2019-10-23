import serial 
import time
from PIL import Image
import io
import cv2
import numpy as np


def Get_Image_Name():
        while s.inWaiting()==0:
                pass
        name_len = ord(s.read(1))
        print str(name_len)+"Got name length"
        while s.inWaiting()<=name_len :
                pass
        name = s.read(name_len)
        return name

def Send_Start():
        s.write('S')
        while s.inWaiting()==0:
                pass                
        response = s.read(1)
        return response

def Get_JPEG_Image():
        while s.inWaiting()==0:
                pass
        a = s.read(1)
        
        while s.inWaiting()==0:
                pass
        b = s.read(1)

        image_len = ord(b)
        image_len = image_len << 8
        image_len = image_len + ord(a)
        print image_len
        r=""
        addr=0        
        while(addr<image_len):
                r +=s.read(1)
                addr=addr+1

        print "Receive image of size "+str(len(r))
        photo = list(r)
        return photo

def Send_Decompress_Image(img):
        height,width,component = img.shape
        repeat = (width*height*component)/19200

        b=0
        for r in range(0,repeat):
            a = b
            b = b + (height/repeat)
            for row in range(a,b):
                for pixel in img[row]:
                    for value in pixel:
                        if value==249:
                                value=248
                        elif value==250:
                                value=251
                        s.write(chr(value))
            print Send_Start()+"Send part "+str(r)
            

def Get_Color_Output_Image(img):
        height,width,component = img.shape
        repeat = (width*height*component)/19200
        
        img1 = np.zeros((height,width,component))
        b=0
        for r in range(0,repeat):
            a = b
            b = b + (height/repeat)
            for i in range(a,b):
                for j in range(0,width):
                    for k in  range(0,component):
                        img1[i][j][k] = ord(s.read(1))
            print Send_Start()+"Received part "+str(r)
        return img1


def Get_DFT_Output_Image(img):
        height,width,component = img.shape
        repeat = (width*height*component)/19200
        img1 = np.zeros((height,width))
        b=0
        for r in range(0,repeat):
                for k in range(2):
                        a = b
                        b = b + 10
                        for block in range(32):
                                for col in range(a,b):
                                        c = 10*block
                                        d = c+10
                                        for row in range(c,d):
                                                while s.inWaiting()==0:
                                                        pass   
                                                img1[col][row] = ord(s.read(1))
                                        
                print Send_Start()+"Received part "+str(r)
        return img1

def Get_BW_Output_Image(img):
        height,width,component = img.shape
        repeat = (width*height*component)/19200
        img1 = np.zeros((height,width))
        b=0
        for r in range(0,repeat):
            a = b
            b = b + (height/repeat)
            for i in range(a,b):
                for j in range(0,width):
                        while s.inWaiting()==0:
                                pass   
                        img1[i][j] = ord(s.read(1))
            print Send_Start()+"Received part "+str(r)
        return img1
        
def Get_Output_Image(img):
        print Send_Start()+"Send Receive Command"
        output_image_name = Get_Image_Name()+".jpg"
        print output_image_name
        while s.inWaiting()==0:
                pass
        cmd = s.read(1)
        if cmd == 'A':
                print "Received 320*240*3 command"
                Output_Image = Get_Color_Output_Image(img)
                
        elif cmd =='B':
                print "Recived 320*240*1 command"
                Output_Image = Get_BW_Output_Image(img)
        elif cmd =='C':
                print "Recived DFT 320*240*1 command"
                Output_Image = Get_DFT_Output_Image(img)

        cv2.imwrite(output_image_name,Output_Image)
        print output_image_name +  "saved"

BAUD = 460800
PORT = "/dev/ttyUSB1"
TIMEOUT=0.5

s = serial.Serial( PORT, baudrate=BAUD, timeout = TIMEOUT )
          
print Send_Start()+"Communication Started "

img_name = Get_Image_Name()+".bmp"
print "Image file name = "+img_name
photo = Get_JPEG_Image()


image = Image.open(io.BytesIO(bytearray(photo)))
image.save(img_name)
img=cv2.imread("PC_Image.jpg")#change parameter to img_name to send image captured by camera
print Send_Start()+"Send Start of Image"
Send_Decompress_Image(img)
print "Done Image Send"

while s.inWaiting()==0:
        pass
No_Of_Images = ord(s.read(1))

Image_received =0
while Image_received < No_Of_Images :
        Get_Output_Image(img)
        Image_received +=1
        
print "Well Done"
cv2.waitKey(0)
cv2.destroyAllWindows()

