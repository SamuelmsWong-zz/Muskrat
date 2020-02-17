import numpy as np
import math
import cv2 # OpenCV works in BGR
from telnetlib import Telnet
import time
# import imutils
print("imported")

# Reduce all colour copmonents until only one component is left
def floorColours(img, width, height):
	tmp = np.zeros((imHeight, imWidth, 3), dtype=np.uint8)
	for colnum in range(width):
		for rownum in range(height):
			# A little bubble sort
			cols = img[rownum, colnum]
			big = 0
			mid = 0
			if cols[1] > cols[big]:
				mid, big = big, 1
			else:
				mid = 1
			if cols[2] > cols[big]:
				mid, big = big, 2
			elif cols[2] > cols[mid]:
				mid = 2
			tmp[rownum, colnum, big] = cols[big]-cols[mid]
	return tmp

# Get pythagorean distance
def L2distance(point1, point2):
	return math.sqrt((point1[0] - point2[0])**2 + (point1[1] - point2[1])**2)

# Converts a list of 12 10bit ( < 1024) pixel locations
# into a 15-long 8bit character stream
def locationsTo15characters(nums):
	# stick the 10 numbers together into one big 120bit number
	amalgamation = 0
	for i in range(len(nums)):
		amalgamation |= int(nums[i]) << ((11-i)*10) # int is very important, to ensure that it can go up to 120 bits
	# split up into chunks of 8 and return as bytearray
	return bytearray([(amalgamation >> ((14-i)*8) & 255) for i in range(15)])



# Run
printstuff = True
cap = cv2.VideoCapture(1) # 0 for built in webcam, 1 for external cam
print("Captured video feed")
ArduinoIP = "192.168.137.62" # COPY AND PASTE IP ADDRESS HERE WHEN ARDY HAS CONNECTED----------*
maskidentifiers = ["p", "q", "r", "s", "t", "u"]
TABLE = 2 # 2 or 3------------------------------------------------------------------------
# Key checkpoints to visit. HARDCODED. Table2 spawn point is off camera, at (68, 520)
checkpoints2 = [(65, 479), (56, 289), (105, 282), (93, 73), (338, 274)]
checkpoints3 = [(537, 0), (536, 225), (499, 225), (497, 436), (247, 224)]
checkpoints = [checkpoints2, checkpoints3]

# identifier colour for check points
identifier = np.array([0, 255, 0])


# threshold for detecting border pixels
thresholdRed = 50 # should be 40-60 to remove brown wood
thresholdGreen = 20 # should be 20-40 cos victims are hardly green
thresholdBlue = 30 # should be 40-60 cos blue is can go quite high

# the number of contour pixels required to be confident of a decently sized blob
# increasing this gives more room for a lower threshold
confidenceRed = 30 # red and blue dots can be star shaped to increase surface area for contour pixels
confidenceGreen = 20 # these are more round and so require lower confidence/number of contours pixels
confidenceBlue = 30
# Since we have a low green threshold but also a low required
# confidence for victim detection, we are relying heavily on the
# fact that there are no other green objects in the camera feed

area_confidenceRed = 100 # red and blue dots are solid shapes with large enclosed area
area_confidenceGreen = 25 # these are smaller but nonetheless have much higher area than blobs of noise
area_confidenceBlue = 100


locationsRed = []
locationsGreen = []
locationsBlue = []

# backup coordinates if none are detected (should not be needed)
bluestorage = [(80, 430)]
greenstorages = [(0, 0), (0, 0), (0, 0), (0, 0)]
redstorage = [(87, 430)]

# Process image --> should output 6 pixel locations, theoretically 10 bit numbers
with Telnet(ArduinoIP, 23) as tn:
	while True:
		locationsRed = []
		locationsGreen = []
		locationsBlue = []

		# Get image --> np array
		ret, pix = cap.read()
		if not(ret):
			print("Load img did not work!!!!!!")

		imWidth = len(pix[0])
		imHeight = len(pix)

		# Get main tunnel and surroundings mask
		with open("masks/"+maskidentifiers[TABLE-2]+"maskarrayex.bin","rb") as f:
			maskNormal = np.array(list(f.read())).reshape((imHeight, imWidth, 1)).astype(np.uint8)
		# Get triage area mask for red
		with open("masks/"+maskidentifiers[TABLE]+"maskarrayex.bin","rb") as f:
			maskRed = np.array(list(f.read())).reshape((imHeight, imWidth)).astype(np.uint8)
		# Get mask to liit green detection to only the cave
		with open("masks/"+maskidentifiers[TABLE+2]+"maskarrayex.bin","rb") as f:
			maskGreen = np.array(list(f.read())).reshape((imHeight, imWidth)).astype(np.uint8)

		# Apply main tunnel and surroundings mask
		pix[:,:,:3] *= maskNormal

		pixfloored = floorColours(pix, imWidth, imHeight)
		pixBlue, pixGreen, pixRed = cv2.split(pixfloored)

		# Apply red and green masks
		pixGreen *= maskGreen
		pixRed *= maskRed
		# Threshold
		ret,pixBlue = cv2.threshold(pixBlue,thresholdBlue,255,0)
		ret,pixGreen = cv2.threshold(pixGreen,thresholdGreen,255,0)
		ret,pixRed = cv2.threshold(pixRed,thresholdRed,255,0)
		# Fit countours
		contoursBlue, hierarchy = cv2.findContours(pixBlue,cv2.RETR_LIST,cv2.CHAIN_APPROX_NONE)
		contoursGreen, hierarchy = cv2.findContours(pixGreen,cv2.RETR_LIST,cv2.CHAIN_APPROX_NONE)
		contoursRed, hierarchy = cv2.findContours(pixRed,cv2.RETR_LIST,cv2.CHAIN_APPROX_NONE)

		# get centres using first and zeroth moments of area
		for c in contoursBlue:
			if len(c) > confidenceBlue and len(c)<80 and cv2.contourArea(c) > area_confidenceBlue:
				# calculate moments for each contour
				M = cv2.moments(c)
				# calculate x,y coordinate of center
				if M["m00"] != 0:
					cX = int(M["m10"] / M["m00"])
					cY = int(M["m01"] / M["m00"])
					locationsBlue.insert(0, (cX,cY))
			# colour these contours in
			for p in c:
				pix[p[0][1], p[0][0]] = np.array([255, 0, 0])
		for c in contoursGreen:
				print(cv2.contourArea(c))
				if len(c) > confidenceGreen and cv2.contourArea(c) > area_confidenceGreen:
					# calculate moments for each contour
					M = cv2.moments(c)
					# calculate x,y coordinate of center
					if M["m00"] != 0:
						cX = int(M["m10"] / M["m00"])
						cY = int(M["m01"] / M["m00"])
					locationsGreen.insert(0, (cX,cY))
			# colour these contours in
				for p in c:
					pix[p[0][1], p[0][0]] = np.array([0, 255, 0])
		for c in contoursRed:
			if len(c) > confidenceRed and len(c)<80 and cv2.contourArea(c) > area_confidenceRed:
				# calculate moments for each contour
				M = cv2.moments(c)
				# calculate x,y coordinate of center
				if M["m00"] != 0:
					cX = int(M["m10"] / M["m00"])
					cY = int(M["m01"] / M["m00"])
					locationsRed.insert(0, (cX,cY))
			# colour these contours in
			for p in c:
				pix[p[0][1], p[0][0]] = np.array([0, 0, 255])

		# colour in centres
		for (y, x) in locationsBlue:
			pix[x, y] = 255 - np.array([255, 0, 0])
		for (y, x) in locationsGreen:
			pix[x, y] = 255 - np.array([0, 255, 0])
		for (y, x) in locationsRed:
			pix[x, y] = 255 - np.array([0, 0, 255])


		if printstuff:
			print("Number of Blues:", len(locationsBlue))
			print([list(i) for i in locationsBlue])
			print("Number of Reds:", len(locationsRed))
			print([list(i) for i in locationsRed])
			print("Number of Greens:", len(locationsGreen))
			print([list(i) for i in locationsGreen])

		# check for correct number of blue centres identified and act accordingly
		if len(locationsBlue) == 0:
			if printstuff:
				print("0 blue centres were found!!!")
			locationsBlue = bluestorage
		elif len(locationsBlue) == 1:
			locationsBlue = [locationsBlue[0]]
		else:
			if printstuff:
				print("{} blue centres were found!!! The first one will be used".format(len(locationsBlue)))
			locationsBlue = [locationsBlue[0]]

		# check for correct number of red centres identified and act accordingly
		if len(locationsRed) == 0:
			if printstuff:
				print("0 red centres were found!!!")
			locationsRed = redstorage
		elif len(locationsRed) == 1:
			locationsRed = [locationsRed[0]]
		else:
			if printstuff:
				print("{} red centres were found!!! The closest one to the blue centre will be used".format(len(locationsRed)))
			closest = 0
			for i in range(len(locationsRed)):
				if L2distance(locationsRed[i], locationsBlue[0]) < L2distance(locationsRed[closest], locationsBlue[0]):
					closest = i
			locationsRed = [locationsRed[0]]

		# check for correct number of green centres identified and act accordingly
		if len(locationsGreen) == 0:
			if printstuff:
				print("0 green centres were found!!!")
			locationsGreen = greenstorages
		elif len(locationsGreen) > 4:
			if printstuff:
				print("{} green centres were found!!!".format(len(locationsGreen)))
		else:
			greenstorages = locationsGreen[:]

		# update storage data
		bluestorage = [locationsBlue[0]]
		redstorage = [locationsRed[0]]
		alllocations = [locationsBlue[0]] + [locationsRed[0]] + (locationsGreen + [(0, 0), (0, 0), (0, 0), (0, 0)])[:4]

		# format into a list of 12 data points
		alllocations = np.array(alllocations)
		alllocations = list(alllocations.reshape(alllocations.shape[0]*alllocations.shape[1]))
		
		# colour in checkpoints
		for checkpoint in checkpoints[TABLE-2]:
			pix[checkpoint[1], checkpoint[0]] = identifier

		# mark lines or centres to for visual pruposes
		pix[:, alllocations[0]] = np.array([255, 0, 0])
		pix[alllocations[1], :] = np.array([255, 0, 0])
		pix[:, alllocations[2]] = np.array([0, 0, 255])
		pix[alllocations[3], :] = np.array([0, 0, 255])
		pix[:, alllocations[4]] = np.array([0, 255, 0])
		pix[alllocations[5], :] = np.array([0, 255, 0])
		pix[:, alllocations[6]] = np.array([0, 255, 0])
		pix[alllocations[7], :] = np.array([0, 255, 0])
		pix[:, alllocations[8]] = np.array([0, 255, 0])
		pix[alllocations[9], :] = np.array([0, 255, 0])
		pix[:, alllocations[10]] = np.array([0, 255, 0])
		pix[alllocations[11], :] = np.array([0, 255, 0])

		# write output image
		cv2.imwrite("output.png",pix)


		# Convert to bytearray
		characters = locationsTo15characters(list(alllocations))

		# Send
		tn.write(bytearray([255]) + characters)
		print("DATA HAS BEEN SENT, WAITING FOR NEXT")

		# Get most recent request
		received = tn.read_until(bytearray("hello","ascii"), timeout=7)
		if printstuff:
			if received[-5:] == bytearray("hello","ascii"):
				print("\nRequest received", received, "leftover data is: ", tn.read_very_lazy())
				pass
			else:
				print("Handshake not received. Continuing anyway.")