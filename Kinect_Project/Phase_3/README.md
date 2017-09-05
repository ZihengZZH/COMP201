# Phase 3
This is Phase 3 of Kinect project. Since the algorithm taken in last phase is not appropriate for complex model, it is necessary to explore some other algorithms. There is an algorithm called standard RANSAC pose estimation loop, which is intended to avoid verification of pose hypotheses that are likely to be wrong. This is implemented in the PCL class SampleConsensusPrerejective that treats Kinect input as object and IFC input as scene. Some supporting material will be given in this folder. The general process of this algorithm:
* Load object and scene
* Downsample
* Estimate normals for scene
* Estimate features (FPFH)
* Perform alignment
* Obtain translation vector & rotation matrix

The libraries and dependencies are equivalent to previous phase.



Reference:
[1] A. G. Buch, D. Kraft, J.-K. Kämäräinen, H. G. Petersen and N. Krüger. Pose Estimation using Local Structure-Specific Shape and Appearance Context. International Conference on Robotics and Automation (ICRA), 2013.
