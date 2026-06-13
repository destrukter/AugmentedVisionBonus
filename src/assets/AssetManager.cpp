#include <AssetManager.hpp>

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

AssetManager::AssetManager() {
    std::error_code ec;
    fs::create_directories(imageStorageDir, ec);
    fs::create_directories(modelStorageDir, ec);
}

bool AssetManager::hasExtension(
    const std::string& path, const std::vector<std::string>& extensions) {
    std::string ext = fs::path(path).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return std::find(extensions.begin(), extensions.end(), ext) != extensions.end();
}

std::optional<std::string> AssetManager::store(
    const std::string& sourcePath, const std::string& storageDir) {
    const fs::path source(sourcePath);
    std::error_code ec;
    if (!fs::exists(source, ec)) {
        std::cerr << "Error: Source file does not exist: " << sourcePath << std::endl;
        return std::nullopt;
    }

    fs::create_directories(storageDir, ec);
    const fs::path destination = fs::path(storageDir) / source.filename();
    fs::copy_file(source, destination, fs::copy_options::overwrite_existing, ec);
    if (ec) {
        std::cerr << "Error: Failed to store '" << sourcePath << "': "
                  << ec.message() << std::endl;
        return std::nullopt;
    }

    return destination.string();
}

std::optional<std::string> AssetManager::addImage(const std::string& sourcePath) {
    if (!hasExtension(sourcePath, {".png", ".jpg", ".jpeg"})) {
        std::cerr << "Error: Unsupported image format for: " << sourcePath
                  << ". Supported: .png, .jpg, .jpeg." << std::endl;
        return std::nullopt;
    }

    const std::optional<std::string> stored = store(sourcePath, imageStorageDir);
    if (!stored) {
        return std::nullopt;
    }

    const std::string id = "image_" + std::to_string(nextImageId++);
    images_.push_back(ImageAsset{id, *stored, ""});
    return id;
}

std::optional<std::string> AssetManager::addModel(const std::string& sourcePath) {
    if (!hasExtension(sourcePath, {".fbx"})) {
        std::cerr << "Error: Unsupported model format for: " << sourcePath
                  << ". Supported: .fbx." << std::endl;
        return std::nullopt;
    }

    const std::optional<std::string> stored = store(sourcePath, modelStorageDir);
    if (!stored) {
        return std::nullopt;
    }

    const std::string id = "model_" + std::to_string(nextModelId++);
    models_.push_back(ModelAsset{id, *stored});
    return id;
}

bool AssetManager::removeImage(const std::string& imageId) {
    const auto it = std::find_if(images_.begin(), images_.end(),
                                 [&](const ImageAsset& a) { return a.id == imageId; });
    if (it == images_.end()) {
        return false;
    }

    std::error_code ec;
    fs::remove(it->path, ec);
    images_.erase(it);
    return true;
}

bool AssetManager::removeModel(const std::string& modelId) {
    const auto it = std::find_if(models_.begin(), models_.end(),
                                 [&](const ModelAsset& a) { return a.id == modelId; });
    if (it == models_.end()) {
        return false;
    }

    std::error_code ec;
    fs::remove(it->path, ec);
    models_.erase(it);

    // Drop the assignment from any image that referenced this model.
    for (ImageAsset& image : images_) {
        if (image.assignedModelId == modelId) {
            image.assignedModelId.clear();
        }
    }
    return true;
}

bool AssetManager::assignModelToImage(
    const std::string& imageId, const std::string& modelId) {
    const auto image = std::find_if(images_.begin(), images_.end(),
                                    [&](const ImageAsset& a) { return a.id == imageId; });
    const auto model = std::find_if(models_.begin(), models_.end(),
                                    [&](const ModelAsset& a) { return a.id == modelId; });
    if (image == images_.end() || model == models_.end()) {
        return false;
    }

    image->assignedModelId = modelId;
    return true;
}

bool AssetManager::clearImageAssignment(const std::string& imageId) {
    const auto it = std::find_if(images_.begin(), images_.end(),
                                 [&](const ImageAsset& a) { return a.id == imageId; });
    if (it == images_.end()) {
        return false;
    }

    it->assignedModelId.clear();
    return true;
}
