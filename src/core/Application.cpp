#include <Application.hpp>
#include <opencv2/opencv.hpp>

void Application::init(){
    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "Error: Could not open webcam (device 0)." << std::endl;
        return 1;
    }

    cv::Mat frame;
    const std::string windowName = "ARTracker - Webcam Feed";
}

void Application::start(){
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    std::cout << "Webcam started. Press 'q' or ESC to exit." << std::endl;

    bool isRunning = true;
    while (isRunning) {
        running();
    }

    camera.release();
    cv::destroyAllWindows();
}

void Application::running(){
    if (!camera.read(frame) || frame.empty()) {
            std::cerr << "Warning: Failed to read frame from webcam." << std::endl;
            break;
        }

        cv::imshow(windowName, frame);
        const int key = cv::waitKey(1);
        if (key == 27 || key == 'q' || key == 'Q') {
            quit();
        }
}

void Application::quit(){
    isRunning = false;
    camera.release();
    cv::destroyAllWindows();
}