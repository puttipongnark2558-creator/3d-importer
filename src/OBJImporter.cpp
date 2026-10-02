#include "OBJImporter.hpp"
#include <fstream>
#include <sstream>

bool OBJImporter::processAndImport(const std::string& filepath, int startGroupId, int reductionPercent, bool centerModel, CCPoint centerPos) {
    std::ifstream file(filepath);
    if (!file.is_open()) return false;

    std::vector<Vertex3D> vertices;
    std::vector<Face3D> faces;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v") {
            Vertex3D v;
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        } else if (type == "f") {
            Face3D f;
            std::string vstr1, vstr2, vstr3;
            ss >> vstr1 >> vstr2 >> vstr3;
            
            auto parseIndex = [](const std::string& s) -> int {
                std::stringstream vss(s);
                int idx = 0;
                vss >> idx;
                return idx - 1;
            };

            f.v1 = parseIndex(vstr1);
            f.v2 = parseIndex(vstr2);
            f.v3 = parseIndex(vstr3);
            faces.push_back(f);
        }
    }
    file.close();

    auto editor = LevelEditorLayer::get();
    if (!editor) return false;

    float scale = 30.0f;
    int objectCount = 0;

    for (size_t i = 0; i < vertices.size(); i++) {
        if (reductionPercent > 0 && (i % 100 < (size_t)reductionPercent)) continue;

        auto& v = vertices[i];
        float posX = centerPos.x + (v.x * scale);
        float posY = centerPos.y + (v.y * scale);

        auto obj = editor->createObject(1, CCPoint{posX, posY}, true);
        if (obj) {
            obj->addToGroup(startGroupId);
            objectCount++;
        }
    }

    return objectCount > 0;
}
