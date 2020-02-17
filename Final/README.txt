Written by
	Mihai Ilas, mai32@cam.ac.uk, Lab Group 85
	and Samuel Wong, smsw2@cam.ac.uk, Lab Group 90
Jan-Feb 2020
This Arduino program is written to be run on the Team L102 Muskrat robot in the the Cambridge Engineering Part1B IDP project, with an Arudino Uno Wifi Rev2.
It runs a blocked code structure where control of each section of the mission breaks away from the main loop and is given to "overarching" functions that each run their own loop, calling hardware interfacing functions when required.

Note that code for an older strategy can be found in the OldWithWifi folder in the root directory, which shows use of image processing, wifi serial connection, and coordinate system location and orientation methods.
