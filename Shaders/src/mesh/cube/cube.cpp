#include "cube.h"
#include <GL/glew.h>
#include "../../imgui/imgui.h"

CubeMesh::CubeMesh() : VAO(0), VBO(0), shaderProgram(0) {

    name = "cube";
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, getVertexDataSize(), getVertexData(), GL_DYNAMIC_DRAW);

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

    createShaderProgram();
}

CubeMesh::~CubeMesh() {
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

void CubeMesh::createShaderProgram() {
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

void CubeMesh::setUniforms() const {

}

unsigned int CubeMesh::getVertexCount() const {
    return 36;
}
unsigned int CubeMesh::getStride() const {
    return 8 * sizeof(float);
}
const float* CubeMesh::getVertexData() const {
    return mesh;
}
unsigned int CubeMesh::getVertexDataSize() const {
    return sizeof(mesh);
}
void CubeMesh::bind() {
    glBindVertexArray(VAO);
}
void CubeMesh::unbind() {
    glBindVertexArray(0);
}
unsigned int CubeMesh::getShaderProgram() const {
    return shaderProgram;
}
void CubeMesh::useShaderProgram() const {
    glUseProgram(shaderProgram);
}

void CubeMesh::update(float deltaTime) {
    timeElapsed += deltaTime;
}


void CubeMesh::renderCustomImGui() {
    ImGui::Separator();
    ImGui::Text("Color chaning interface");
}