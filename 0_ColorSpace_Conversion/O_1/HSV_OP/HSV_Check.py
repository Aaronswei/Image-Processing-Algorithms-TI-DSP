import numpy as np
import cv2
from numpy import array


from PIL import Image
image = cv2.imread("Input_Image.jpg")


hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
arr=array(hsv)
image1=Image.fromarray(arr)
image1.save("Output_HSV_PY_Check.jpg")
cv2.imwrite('Output_Hue_PY_Check.jpg', arr[:,:,0])
cv2.imwrite('Output_Sat_PY_Check.jpg', arr[:,:,1])
cv2.imwrite('Output_Val_PY_Check.jpg', arr[:,:,2])
cv2.waitKey(0)
cv2.destroyAllWindows()
