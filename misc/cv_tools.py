#!/usr/bin/env python

"""
Selections of computer vision tools/methods
"""

import numpy as np
import cv2

def sobel_thresh(img, orient='x', sobel_kernel=3, thresh=(0,255), gray=False):
	"""Applying sobel operator for edge detection"""
	if not gray:
		gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	else:
		gray = img
	if orient == 'x':
		sobel = cv2.Sobel(gray,cv2.CV_64F,1,0,ksize=sobel_kernel)
	elif orient == 'y':
		sobel = cv2.Sobel(gray,cv2.CV_64F,0,1,ksize=sobel_kernel)
	abs_sobel = np.absolute(sobel)
	scaled_sobel = np.uint8(255*abs_sobel/np.max(abs_sobel))
	grad_binary = np.zeros_like(scaled_sobel)
	grad_binary[(scaled_sobel >= thresh[0])&(scaled_sobel <= thresh[1])] = 1
	return grad_binary

def increase_brightness(img, value=30):
	"""Increase image brightness by increase V channel of HSV"""
	hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
	h, s, v = cv2.split(hsv)
	lim = 255 - value
	v[v > lim] = 255
	v[v <= lim] += value
	final_hsv = cv2.merge((h, s, v))
	img = cv2.cvtColor(final_hsv, cv2.COLOR_HSV2BGR)
	return img

def white_balance(img):
	"""Adjust while balance of image"""
	result = cv2.cvtColor(img, cv2.COLOR_BGR2LAB)
	avg_a = np.average(result[:, :, 1])
	avg_b = np.average(result[:, :, 2])
	result[:, :, 1] = result[:, :, 1] - ((avg_a - 128) * (result[:, :, 0] / 255.0) * 1.1)
	result[:, :, 2] = result[:, :, 2] - ((avg_b - 128) * (result[:, :, 0] / 255.0) * 1.1)
	result = cv2.cvtColor(result, cv2.COLOR_LAB2BGR)
	return result

def histogram_equalization(image, gray=False):
	"""Apply histogram equalization"""
	if not gray:
		img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	else: 
		img = image
	equ = cv2.equalizeHist(img)
	return equ

def canny(img, low_threshold, high_threshold):
    """Applies the Canny transform"""
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    return cv2.Canny(gray, low_threshold, high_threshold)

def gaussian_blur(img, kernel_size):
    """Applies a Gaussian Noise kernel"""
    return cv2.GaussianBlur(img, (kernel_size, kernel_size), 0)
