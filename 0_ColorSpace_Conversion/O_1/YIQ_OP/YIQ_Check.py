import numpy as np
import cv2
from numpy import array
import colorsys

from PIL import Image
Im = cv2.imread("Input_Image.jpg")

R=Im[:,:,0];
G=Im[:,:,1];
B=Im[:,:,2];

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

cv2.imwrite('Output_Y_PY_Check.bmp', Y)
cv2.imwrite('Output_1_PY_Check.bmp', I)
cv2.imwrite('Output_Q_PY_Check.bmp', Q)

YIQ=array(Im)
YIQ[:,:,0]=Y
YIQ[:,:,1]=I
YIQ[:,:,2]=Q
cv2.imwrite('Output_YIQ_PY_Check.jpg', YIQ)


