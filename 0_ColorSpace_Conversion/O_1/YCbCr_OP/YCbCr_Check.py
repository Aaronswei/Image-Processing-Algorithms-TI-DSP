import numpy as np
import cv2
from numpy import array
import colorsys

from PIL import Image
Im = cv2.imread("Input_Image.jpg")

ycbcr=cv2.cvtColor(Im, cv2.COLOR_BGR2YCR_CB)
arrycbcr=array(ycbcr)
cv2.imwrite('Output_Y_PY_Check.jpg', arrycbcr[:,:,0])
cv2.imwrite('Output_Cb_PY_Check.jpg', arrycbcr[:,:,1])
cv2.imwrite('Output_Cr_PY_Check.jpg', arrycbcr[:,:,2])
cv2.imwrite('Output_YCbCr_PY_Check.jpg', ycbcr)
cv2.waitKey(0)
cv2.destroyAllWindows()


