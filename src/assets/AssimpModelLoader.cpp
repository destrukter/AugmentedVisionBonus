#include <AssimpModelLoader.hpp>

ModelLoader::ModelLoader()
    : importer(std::make_unique<Assimp::Importer>()), scene(nullptr) {}

ModelLoader::~ModelLoader() = default;

bool ModelLoader::loadModel(const std::string& modelPath) {
    const std::filesystem::path path(modelPath);
    if (!std::filesystem::exists(path)) {
        std::cerr << "Error: Model file does not exist: " << modelPath << std::endl;
        return false;
    }

    const aiScene* loadedScene = importer->ReadFile(
        modelPath,
        aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_ImproveCacheLocality | aiProcess_SortByPType);

    if (loadedScene == nullptr) {
        std::cerr << "Error: Failed to load model '" << modelPath << "'. Assimp: "
                  << importer->GetErrorString() << std::endl;
        return false;
    }

    scene = loadedScene;
    return true;
}

bool ModelLoader::loadMarkerImage(const std::string& imagePath) {
    const std::filesystem::path path(imagePath);
    if (!std::filesystem::exists(path)) {
        std::cerr << "Error: Marker image file does not exist: " << imagePath << std::endl;
        return false;
    }

    const std::string extension = path.extension().string();
    if (extension != ".png" && extension != ".jpg" && extension != ".jpeg") {
        std::cerr << "Error: Unsupported marker image format: " << extension
                  << ". Supported formats are .png, .jpg, and .jpeg." << std::endl;
        return false;
    }

    markerImage = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (markerImage.empty()) {
        std::cerr << "Error: Could not decode marker image: " << imagePath << std::endl;
        return false;
    }

    return true;
}