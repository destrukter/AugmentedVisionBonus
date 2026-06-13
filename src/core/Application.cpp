#include <Application.hpp>

void Application::init(){
    camera =  cv::VideoCapture (0);
    if (!camera.isOpened()) {
        std::cerr << "Error: Could not open webcam (device 0)." << std::endl;
        return;
    }
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
