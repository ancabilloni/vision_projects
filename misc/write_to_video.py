#!/usr/bin/env python

import cv2
# cap = cv2.VideoCapture("/path/to/your_video.mp4")
cap = cv2.VideoCapture(0) #Try out with your webcam
save_as = "/your/video/folder"

fourcc = cv2.VideoWriter_fourcc(*'mp4v') # set video extension type
video_writer = cv2.VideoWriter(save_as + '/output.mp4', fourcc, 20.0, (640,480)) # path_name, video type, frame rate, (image_width, image_height)
# Note: image_width and image_height must match the image information that feed to video writer

while (cap.isOpened()):
	_, frame = cap.read()
	if frame is None:
		break
	else:
		image = frame # apply any processing here to frame if desire
		video_writer.write(image)
	cv2.imshow('frame', image)
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
cap.release()
video_writer.release()
cv2.destroyAllWindows()