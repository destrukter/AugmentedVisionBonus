#include <Application.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

void Application::init() {
    camera = cv::VideoCapture(0);
    if (!camera.isOpened()) {
        std::cerr << "Error: Could not open webcam (device 0)." << std::endl;
    }

    if (!glfwInit()) {
        std::cerr << "Error: Failed to initialize GLFW." << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, windowName.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Error: Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glGenTextures(1, &cameraTexture);
    glBindTexture(GL_TEXTURE_2D, cameraTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::start() {
    if (!window) return;

    std::cout << "ARTracker started. Close the window to exit." << std::endl;

    isRunning = true;
    while (isRunning && !glfwWindowShouldClose(window)) {
        running();
    }

    quit();
}

void Application::uploadFrameToTexture() {
    if (frame.empty()) return;

    cv::Mat rgb;
    cv::cvtColor(frame, rgb, cv::COLOR_BGR2RGB);
    cv::flip(rgb, rgb, 0);

    glBindTexture(GL_TEXTURE_2D, cameraTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 rgb.cols, rgb.rows, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, rgb.data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::running() {
    glfwPollEvents();

    if (camera.isOpened()) {
        camera.read(frame);
        if (!frame.empty()) {
            uploadFrameToTexture();
        }
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    int displayW, displayH;
    glfwGetFramebufferSize(window, &displayW, &displayH);

    // Full-screen camera feed window
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({(float)displayW, (float)displayH});
    ImGui::Begin("Feed", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus);

    if (!frame.empty()) {
        ImGui::Image((ImTextureID)(intptr_t)cameraTexture,
                     {(float)frame.cols, (float)frame.rows});
    }

    ImGui::SetCursorPos({20, 20});
    if (ImGui::Button("Upload Image")) {
        // TODO: open file dialog and load image
        std::cout << "Upload Image clicked" << std::endl;
    }

    ImGui::End();

    ImGui::Render();
    glViewport(0, 0, displayW, displayH);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void Application::quit() {
    isRunning = false;

    if (cameraTexture) {
        glDeleteTextures(1, &cameraTexture);
        cameraTexture = 0;
    }

    camera.release();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}
