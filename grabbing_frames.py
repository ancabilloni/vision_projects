#!/usr/bin/env python

import cv2
cap = cv2.VideoCapture('path/to/your/video/project_video.mp4')
save_as = "/path/to/your/save_folder"
count = 0

while (cap.isOpened()):
	_, frame = cap.read()
	if frame is None:
		break
	else:
		cv2.imwrite(save_as + "/frame%d.jpg" % count, frame)
		count += 1
	cv2.imshow('frame', frame)
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
cap.release()
cv2.destroyAllWindows()