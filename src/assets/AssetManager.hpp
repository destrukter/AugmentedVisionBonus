#pragma once

#include <optional>
#include <string>
#include <vector>

// Central registry for the assets the application works with: marker images
// and 3D models (.fbx). It owns where files live on disk and the relationships
// between them (which model is rendered on top of which marker image).
//
// The upload button in the UI will eventually drive these operations. For now
// this provides the storage/registry surface the future upload, delete and
// assignment flows will build on.
class AssetManager{
    public:
        struct ImageAsset {
            std::string id;
            std::string path;
            // Id of the model assigned to this image, empty when none.
            std::string assignedModelId;
        };

        struct ModelAsset {
            std::string id;
            std::string path;
        };

        AssetManager();

        // Copies an image / .fbx file from sourcePath into managed storage and
        // registers it. Returns the generated asset id, or std::nullopt on
        // failure (missing file, unsupported extension, copy error).
        std::optional<std::string> addImage(const std::string& sourcePath);
        std::optional<std::string> addModel(const std::string& sourcePath);

        // Removes an asset from the registry and deletes its stored file.
        // Removing an image clears its assignment; removing a model clears it
        // from any image that referenced it. Returns false if id is unknown.
        bool removeImage(const std::string& imageId);
        bool removeModel(const std::string& modelId);

        // Assigns a model to an image so the model is rendered on the marker.
        // Returns false if either id is unknown.
        bool assignModelToImage(const std::string& imageId, const std::string& modelId);
        bool clearImageAssignment(const std::string& imageId);

        [[nodiscard]] const std::vector<ImageAsset>& images() const { return images_; }
        [[nodiscard]] const std::vector<ModelAsset>& models() const { return models_; }

    private:
        [[nodiscard]] static bool hasExtension(
            const std::string& path, const std::vector<std::string>& extensions);
        [[nodiscard]] std::optional<std::string> store(
            const std::string& sourcePath, const std::string& storageDir);

        std::vector<ImageAsset> images_;
        std::vector<ModelAsset> models_;

        // Default on-disk storage locations, relative to the working directory.
        std::string imageStorageDir = "assets/markers";
        std::string modelStorageDir = "assets/models";

        std::size_t nextImageId = 0;
        std::size_t nextModelId = 0;
};
