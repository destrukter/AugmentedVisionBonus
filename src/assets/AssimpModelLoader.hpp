#include <IModelLoader.hpp>
#include <opencv2/core/mat.hpp>
#include <string>

class AssimpModelLoader: IModelLoader {
    public:
    AssimpModelLoader();
    ~AssimpModelLoader();

    bool loadModel(const std::string& modelPath);
    bool loadMarker(const std::string& markerPath);

    [[nodiscard]] bool hasModel() const;
    [[nodiscard]] bool hasMarker() const;
    [[nodiscard]] const cv::Mat& getModel() const;
    [[nodiscard]] const cv::Mat& getMarker() const;

private:
    std::unique_ptr<Assimp::Importer> importer; //have importer only in local scope?
    const void* scene;
    cv::Mat model;
    cv::Mat marker;
};