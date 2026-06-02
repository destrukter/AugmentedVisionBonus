#include <iostream>

class IModelLoader {
    virtual bool loadModel(const std::string& modelPath) = 0;
    virtual bool loadMarker(const std::string& markerPath) = 0;
};