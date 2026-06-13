#include <opencv2/opencv.hpp>

#include <AssetManager.hpp>

class Application{
    public:
        void init();
        void start();

    private:
        cv::Mat frame;
        bool isRunning = false;
        const std::string windowName = "ARTracker - Webcam Feed";
        cv::VideoCapture camera;
        AssetManager assetManager;

        // Simple HighGUI overlay button. Drawn on top of the camera frame and
        // clicked via the OpenCV mouse callback. Currently a placeholder that
        // will later drive image / .fbx uploads through the AssetManager.
        const cv::Rect uploadButtonRect{20, 20, 160, 48};
        bool uploadButtonHovered = false;
        bool frameDiagnosticsLogged = false;

        void quit();
        void running();

        void drawUi(cv::Mat& image);
        void handleMouse(int event, int x, int y);
        static void onMouse(int event, int x, int y, int flags, void* userdata);
        void onUploadClicked();
};
