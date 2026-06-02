# Vision

We want to develop an application that tracks an image in a scene and renders a 3D model on top of it. Both the image and the 3D model should be configurable to allow modular usage.

While similar solutions already exist (e.g., Vuforia for Unity), the goal here is to build a standalone application with equivalent functionality.

Key technical responsibilities include:
- Feature detection for uploaded images
- Pose estimation
- Real-time rendering for an augmented reality experience

A core focus of the project is **modularity**, ensuring the system can be extended or adapted easily.

Ultimately, the application should implement all fundamental building blocks of augmented reality technology.
<!--
---

# Milestones

1. Upload an image and a corresponding `.fbx` file  
2. Extract image features  
3. Detect image in camera view  
4. Track image in camera view  
5. Render `.fbx` model on top of the tracked image correctly  
6. Update model position when camera or image marker moves  
-->
--- 

# MVPs
1. Load webcam feed, upload marker and extract features
2. Detect marker in scene and draw bounding box
3. Pose extimation and according 3d axis rendering 
4. Upload fbx, render and align cube on marker
5. Render fbx instead of cube and have stable real time tracking

---

# Technologies

- C++
- OpenCV
- OGRE3D (rendering engine)
- Eigen (linear algebra / math)
- Assimp (model loading, included via OGRE3D)
- ImGUI for UI interactions

---

# Requirements

## OpenCV
```bash
sudo apt install -y libopencv-dev
```
## Eigen3
```bash
sudo apt install -y libeigen3-dev
```
## Assimp
```bash
sudo apt install -y libassimp-dev
```
## OGRE3D
```bash
sudo apt install -y libogre-1.12-dev
```

---

# How to Run
```bash
mkdir build && cd build
cmake ..
cmake --build .
./ARTracker
```
