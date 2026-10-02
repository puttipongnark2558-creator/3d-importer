#pragma once
#include <Geode/Geode.hpp>
#include <string>
#include <vector>

using namespace geode::prelude;

struct Vertex3D {
    float x, y, z;
};

struct Face3D {
    int v1, v2, v3;
};

class OBJImporter {
public:
    static bool processAndImport(const std::string& filepath, int startGroupId, int reductionPercent, bool centerModel, CCPoint centerPos);
};
