import cv2
import numpy as np
from matplotlib import pyplot as plt


img = cv2.imread('Output_Gray_Image_Y.jpg',0)
#hist = cv2.calcHist([img],[0],None,[256],[0,256])

plt.hist(img.ravel(),256,[0,256])
plt.ylabel('Number of pixels')
plt.xlabel('Gray Levels')
plt.show()
