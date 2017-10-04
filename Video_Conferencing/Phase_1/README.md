# Phase 1 (Face detection using Haar Cascades)

This phase is intended to realise the face-detection and eye-detection with Haar Cascades, which is an effective object detection method proposed by Paul Viola and Michael Jones in 2001. It is a machine learning based approach where a cascade function is trained from a lot of positive and negative images and then can be applied to detect objects in other images. In this phase, there are two implementations of such algorithm (C++ and Python). The running speed for C++ is much slower than that for Python and it is pity for lack of GPU accerlation. However, in Python implementation, the recognition result is not so satisfactory that it mistook nose for eyes. Further improvement is necessary for both accuracy and speed.

Dependencies:
* OpenCV 3.2.0
* NumPy 1.13

External device:
* Logitech Web-cam C270
