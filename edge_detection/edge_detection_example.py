#!/usr/bin/env python

""" 
Edge detection with Sobel operator on webcam
"""

from cv_tools import sobel_thresh
import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while (cap.isOpened()):
	_, frame = cap.read()
	sobel_x = sobel_thresh(frame, orient='x', sobel_kernel=9, thresh=(30,100))
	sobel_y = sobel_thresh(frame, orient='y', sobel_kernel=9, thresh=(30,100))
	sobel = np.zeros_like(sobel_x)
	sobel[(sobel_x==1)|(sobel_y==1)] = 255
	mask_sobel = np.dstack((sobel, sobel, sobel))
	cv2.imshow('frame', np.hstack((frame,mask_sobel)))
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
	# time.sleep(0.01)
	cv2.waitKey(20)
cap.release()
cv2.destroyAllWindows()