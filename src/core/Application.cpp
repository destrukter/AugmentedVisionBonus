#include <Application.hpp>

void Application::init(){
    camera =  cv::VideoCapture (0);
    if (!camera.isOpened()) {
        std::cerr << "Error: Could not open webcam (device 0)." << std::endl;
        return;
    }

    std::cout << "Camera opened. Backend: " << camera.getBackendName()
              << ", reported resolution: "
              << camera.get(cv::CAP_PROP_FRAME_WIDTH) << "x"
              << camera.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
}

void Application::start(){
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback(windowName, &Application::onMouse, this);

    std::cout << "Webcam started. Press 'q' or ESC to exit." << std::endl;

    isRunning = true;
    while (isRunning) {
        running();
    }

    camera.release();
    cv::destroyAllWindows();
}

void Application::running(){
    if (!camera.read(frame) || frame.empty()) {
        std::cerr << "Warning: Failed to read frame from webcam." << std::endl;
        isRunning = false;
        return;
    }

    if (!frameDiagnosticsLogged) {
        const cv::Scalar mean = cv::mean(frame);
        std::cout << "First frame: " << frame.cols << "x" << frame.rows
                  << ", channels=" << frame.channels()
                  << ", mean(BGR)=[" << mean[0] << ", " << mean[1] << ", "
                  << mean[2] << "]" << std::endl;
        if (mean[0] < 1.0 && mean[1] < 1.0 && mean[2] < 1.0) {
            std::cout << "  -> Frame is essentially black. The camera is "
                         "delivering empty frames (wrong device, in use by "
                         "another app, or no signal)." << std::endl;
        }
        frameDiagnosticsLogged = true;
    }

    drawUi(frame);

    cv::imshow(windowName, frame);
    const int key = cv::waitKey(1);
    if (key == 27 || key == 'q' || key == 'Q') {
        quit();
    }
}

void Application::drawUi(cv::Mat& image){
    const cv::Scalar fill = uploadButtonHovered ? cv::Scalar(90, 90, 90)
                                                : cv::Scalar(60, 60, 60);
    const cv::Scalar border(200, 200, 200);

    cv::rectangle(image, uploadButtonRect, fill, cv::FILLED);
    cv::rectangle(image, uploadButtonRect, border, 1);

    const std::string label = "Upload";
    int baseline = 0;
    const cv::Size textSize =
        cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.6, 1, &baseline);
    const cv::Point textOrg(
        uploadButtonRect.x + (uploadButtonRect.width - textSize.width) / 2,
        uploadButtonRect.y + (uploadButtonRect.height + textSize.height) / 2);
    cv::putText(image, label, textOrg, cv::FONT_HERSHEY_SIMPLEX, 0.6,
                cv::Scalar(255, 255, 255), 1, cv::LINE_AA);
}

void Application::onMouse(int event, int x, int y, int /*flags*/, void* userdata){
    auto* app = static_cast<Application*>(userdata);
    if (app != nullptr) {
        app->handleMouse(event, x, y);
    }
}

void Application::handleMouse(int event, int x, int y){
    const cv::Point cursor(x, y);
    uploadButtonHovered = uploadButtonRect.contains(cursor);

    if (event == cv::EVENT_LBUTTONUP && uploadButtonRect.contains(cursor)) {
        onUploadClicked();
    }
}

void Application::onUploadClicked(){
    // Placeholder: no functionality yet. This is where the upload flow will be
    // wired up to let the user pick an image or .fbx file, hand it to the
    // AssetManager for storage, and (for images) optionally assign a model.
    std::cout << "Upload button clicked (no functionality yet)." << std::endl;
}

void Application::quit(){
    isRunning = false;
    camera.release();
    cv::destroyAllWindows();
}
