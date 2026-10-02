#pragma once

#include <Geode/Geode.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace geode::prelude;

struct Vec3 {
    float x, y, z;
};

struct Face {
    int v1, v2, v3;
};

class OBJImporter {
public:
    static bool processAndImport(
        const std::string& filePath,
        int startGroupId,
        int reductionPercent,
        bool useGradients,
        CCPoint centerPos
    ) {
        std::ifstream file(filePath);
        if (!file.is_open()) return false;

        std::vector<Vec3> rawVertices;
        std::vector<Face> faces;
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string type;
            ss >> type;

            if (type == "v") {
                Vec3 v;
                ss >> v.x >> v.y >> v.z;
                rawVertices.push_back(v);
            } else if (type == "f") {
                std::string s1, s2, s3;
                ss >> s1 >> s2 >> s3;
                
                auto parseIdx = [](const std::string& s) {
                    return std::stoi(s.substr(0, s.find('/'))) - 1;
                };

                try {
                    faces.push_back({ parseIdx(s1), parseIdx(s2), parseIdx(s3) });
                } catch (...) {}
            }
        }
        file.close();

        if (rawVertices.empty()) return false;

        auto editorLayer = LevelEditorLayer::get();
        if (!editorLayer) return false;

        int skipFactor = std::max(1, 100 / std::max(1, 100 - reductionPercent));
        int currentGroup = startGroupId;
        float scale = 30.0f;

        for (size_t i = 0; i < rawVertices.size(); i += skipFactor) {
            const auto& v = rawVertices[i];

            float screenX = centerPos.x + (v.x - v.z) * scale * 0.866f;
            float screenY = centerPos.y + (v.y + (v.x + v.z) * 0.5f) * scale * 0.5f;

            auto obj = editorLayer->createObject(211, { screenX, screenY }, true);
            if (obj) {
                obj->addGroup(currentGroup);

                if (useGradients) {
                    float depthFactor = (v.z + 10.0f) / 20.0f;
                    GLubyte brightness = static_cast<GLubyte>(std::clamp(depthFactor * 255.0f, 50.0f, 255.0f));
                    obj->setObjectColor(ccc3(brightness, brightness, brightness));
                }
            }
            currentGroup++;
        }

        return true;
    }
};
