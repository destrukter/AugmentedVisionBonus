Vision: 
We want to develop an application that tracks an image in a scene and renders a 3d model on top of it. The image and 3d model should be configurable for modular usage. There are libraries like Vuforia (for unity) that already do this, we want to create something similar but as a standalone app. We need to take care of feature detection for the uploaded image, pose estimation, and then real-time rendering to create the augmented experience. We especially want to focus on the modularity of the application. With the app we need to implement all the fundamental building blocks of augmented reality technology. 

Milestones: 
Upload an image and a corresponding fbx file. 
Extract image features. 
Detect image in camera view. 
Track image in camera view. 
Render fbx file on top of tracked image correctly. 
Update model position when camera or image-marker is moved. 

Technologies: 
C++ 
OpenCV 
OGRE3D for rendering 
Eigen for math 
Assimp for model loading(included in OGRE3D)