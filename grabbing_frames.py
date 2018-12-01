#!/usr/bin/env python

cap = cv2.VideoCapture('path/to/your/video/project_video.mp4')
save_as = "/path/to/your/save_folder"
date = "11302018"
count = 0

while (cap.isOpened()):
	_, frame = cap.read()
	if frame is None:
		break
	else:
		cv2.imwrite(save_as + "frame%d.jpg" % count, image)
		count += 1
	cv2.imshow('frame', img)
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
cap.release()
cv2.destroyAllWindows()