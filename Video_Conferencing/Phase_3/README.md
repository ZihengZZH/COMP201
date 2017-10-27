# Phase 3 (Disparity map)

This phase is intended to produce a disparity map with a pair of stereo inputs. The algorithms implemented in OpenCV contains StereoBM and StereoSGBM, which are not perfect anyway. The produced disparity map's quality remains unknown when applied for further point cloud generation. A little test has been conducted and more modification is necessary.

Dependencies:
* OpenCV 3.2.0

External devices:
* Logitech Web-cam C920 * 2
