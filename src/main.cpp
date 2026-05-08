#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "Error: Could not open webcam (device 0)." << std::endl;
        return 1;
    }

    cv::Mat frame;
    const std::string windowName = "ARTracker - Webcam Feed";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    std::cout << "Webcam started. Press 'q' or ESC to exit." << std::endl;

    bool isRunning = true;
    while (isRunning) {
        if (!camera.read(frame) || frame.empty()) {
            std::cerr << "Warning: Failed to read frame from webcam." << std::endl;
            break;
        }

        cv::imshow(windowName, frame);
        const int key = cv::waitKey(1);

        if (key == 27 || key == 'q' || key == 'Q') {
            isRunning = false;
        }
    }

    camera.release();
    cv::destroyAllWindows();
    return 0;
}