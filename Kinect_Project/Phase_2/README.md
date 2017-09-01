# Phase 2
This is Phase 2 of Kinect project. It takes long time to investigate appropriate algorithm to achieve such functionality. Luckily, here is a module, PCL recognition module in Point Cloud Library and basically, it accomplishes a few functionalities:
* load two point clouds
* extract key points from both point clouds
* describe both features
* group correspondence
* acquire absolute orientation
* verify hypothesis

This is achieved by built-in module in PCL, which algorithm is complicated to comprehend so there are two additional documentations in this folder. The exact explanation to each part of program is commented inside for reference. Speaking of running time, to set thread number enables program to run in parallel fashion but running time is still prolix. Therefore, this algorithm or implementation should be modified or at least fastened to fit into final design. Since the output is 3D point cloud, test image and video are supplemented for showing the interaction. 

Here is a list of libraries and dependencies:
* PCL 1.8.1
* Boost 1.6.5
* VTK 8.0.0
* FLANN
* Eigen3
* Qhull
* OpenNI 2.2
* OpenGL 3.3

Note this program operates in x64 mode, instead of Win32(x86).
