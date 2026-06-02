#include <opencv2/opencv.hpp>

class Application{
    public:
        void init();
        void start();

    private:
        cv::Mat frame;
        bool isRunning;
        const std::string windowName = "ARTracker - Webcam Feed";
        cv::VideoCapture camera;
        //AssetManager assetManager;  

        void quit();
        void running();

};