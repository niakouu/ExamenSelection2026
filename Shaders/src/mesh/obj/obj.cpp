#include "../../imgui/imgui.h"
#include "obj.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <algorithm>


ObjMesh::ObjMesh(const std::string& meshName, const std::string& fileName) : VAO(0), VBO(0), shaderProgram(0) {
    name = meshName;
    auto path = buildPath(std::string(GLTF_ASSET_PATH), fileName);
    loadOBJ(path.c_str());
    setupMeshBuffers();
    createShaderProgram();
}

ObjMesh::~ObjMesh() {
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
    }
    if (shaderProgram != 0) {
        glDeleteProgram(shaderProgram);
    }
}

void ObjMesh::loadOBJ(const  std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << filepath << std::endl;
        return;
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            positions.push_back(glm::vec3(x, y, z));
        }
        else if (prefix == "vn") {
            float x, y, z;
            iss >> x >> y >> z;
            normals.push_back(glm::normalize(glm::vec3(x, y, z)));
        }
        else if (prefix == "vt") {
            float u, v;
            iss >> u >> v;
            texCoords.push_back(glm::vec2(u, v));
        }
        else if (prefix == "f") {
            std::string vertexStr;
            std::vector<int> posIndices, texIndices, normIndices;

            while (iss >> vertexStr) {
                int posIdx = 0, texIdx = 0, normIdx = 0;
                std::replace(vertexStr.begin(), vertexStr.end(), '/', ' ');
                std::istringstream vertexStream(vertexStr);

                vertexStream >> posIdx;
                if (vertexStream >> texIdx) {
                    if (vertexStream >> normIdx) {
                    } else {
                        normIdx = 0;
                    }
                } else {
                    texIdx = 0;
                    normIdx = 0;
                }

                posIdx--;
                texIdx--;
                normIdx--;

                if (posIdx >= 0 && posIdx < (int)positions.size()) {
                    vertexData.push_back(positions[posIdx].x);
                    vertexData.push_back(positions[posIdx].y);
                    vertexData.push_back(positions[posIdx].z);
                }

                if (normIdx >= 0 && normIdx < (int)normals.size()) {
                    vertexData.push_back(normals[normIdx].x);
                    vertexData.push_back(normals[normIdx].y);
                    vertexData.push_back(normals[normIdx].z);
                } else {
                    vertexData.push_back(0.0f);
                    vertexData.push_back(1.0f);
                    vertexData.push_back(0.0f);
                }

                if (texIdx >= 0 && texIdx < (int)texCoords.size()) {
                    vertexData.push_back(texCoords[texIdx].x);
                    vertexData.push_back(texCoords[texIdx].y);
                } else {
                    vertexData.push_back(0.0f);
                    vertexData.push_back(0.0f);
                }
            }
        }
    }

    file.close();
}

void ObjMesh::setupMeshBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void ObjMesh::createShaderProgram() {
    auto vsShaderPath = buildPath(VS_SHADER_PATH, CURRENT_VS_SHADER);
    auto fsShaderPath = buildPath(FS_SHADER_PATH, CURRENT_FS_SHADER);
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vsShaderPath.c_str());
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fsShaderPath.c_str());

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ObjMesh::setUniforms() const {

}

unsigned int ObjMesh::getVertexCount() const {
    return vertexData.size() / 8;
}

unsigned int ObjMesh::getStride() const {
    return 8 * sizeof(float);
}

const float* ObjMesh::getVertexData() const {
    return vertexData.data();
}

unsigned int ObjMesh::getVertexDataSize() const {
    return vertexData.size() * sizeof(float);
}

void ObjMesh::bind() {
    glBindVertexArray(VAO);
}

void ObjMesh::unbind() {
    glBindVertexArray(0);
}


unsigned int ObjMesh::getShaderProgram() const {
    return shaderProgram;
}

void ObjMesh::useShaderProgram() const {
    glUseProgram(shaderProgram);
}

int ObjMesh::getDrawMode() const {
    return GL_TRIANGLES;
}
