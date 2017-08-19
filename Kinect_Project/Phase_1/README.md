# Phase 1

This is Phase 1 of Kinect project. It accomplishes a few functionalities: 
* get access to Kinect camera
* measure the depth and receive the data
* display images and distance with OpenCV

The distance measurement is quite simple in that the center point of the image was selected. So only this point' data will be returned from buffer. To illuminate the exact position of measurement, the center point is highlighted inside the image output by OpenCV. However, the depth reliable range is 0.5m to 4.5m, which is declared at the beginning of output. Therefore, the distance beyond that range might be inaccurate. Some testing images are attached.
