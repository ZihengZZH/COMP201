# Phase 5 

This phase is a milestone because it achieves stereo calibration, disparity map and point cloud.
Reference can be found [here](https://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html)
However, the results turned out unpleasing that, e.g., baseline error (4cm - 10cm)

Dependencies:
* OpenCV 3.2.0
* PCL 1.8.1

External devices:
* Logitech Web-cam C920 * 2

NOTES
--
Maybe it is time to move on to next significant phase "synthesised view" because the previous phases might be adjusted.
And more importantly, synthesised view is vital the video conferencing project.

Examples on Disparity Map
--
ALGORITHM SGBM (num=144, SAD=3)

![L](https://github.com/ZihengZZH/Project_Cpp/blob/master/Video_Conferencing/Phase_5/test_L.png)
![R](https://github.com/ZihengZZH/Project_Cpp/blob/master/Video_Conferencing/Phase_5/test_R.png)
![dis](https://github.com/ZihengZZH/Project_Cpp/blob/master/Video_Conferencing/Phase_5/dist.png)

