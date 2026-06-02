#include <opencv2/opencv.hpp>
#include <GLFW/glfw3.h>

class Application {
public:
    void init();
    void start();

private:
    cv::Mat frame;
    bool isRunning = false;
    const std::string windowName = "ARTracker";
    cv::VideoCapture camera;

    GLFWwindow* window = nullptr;
    unsigned int cameraTexture = 0;

    void quit();
    void running();
    void uploadFrameToTexture();
};
