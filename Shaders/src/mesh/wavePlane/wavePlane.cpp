#include "wavePlane.h"
#include "../../imgui/imgui.h"
#include <GL/glew.h>

WavePlaneMesh::WavePlaneMesh(unsigned int subdivisions, float width, float height) 
    : VAO(0), VBO(0), EBO(0), shaderProgram(0), 
      subdivisions(subdivisions), width(width), height(height) {
    
    name = "wavePlane";
    
    generateMesh();
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    
    createShaderProgram();
}

WavePlaneMesh::~WavePlaneMesh() {
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
    }
    if (EBO != 0) {
        glDeleteBuffers(1, &EBO);
    }
    if (shaderProgram != 0) {
        glDeleteProgram(shaderProgram);
    }
}

void WavePlaneMesh::generateMesh() {
    vertices.clear();
    indices.clear();
    
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    
    for (unsigned int z = 0; z <= subdivisions; ++z) {
        for (unsigned int x = 0; x <= subdivisions; ++x) {
            float xPos = -halfWidth + (width * x / subdivisions);
            float yPos = 0.0f;  
            float zPos = -halfHeight + (height * z / subdivisions);
            
            float nx = 0.0f;
            float ny = 1.0f;
            float nz = 0.0f;
            
            float u = static_cast<float>(x) / subdivisions;
            float v = static_cast<float>(z) / subdivisions;
            
            vertices.push_back(xPos);
            vertices.push_back(yPos);
            vertices.push_back(zPos);
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
            vertices.push_back(u);
            vertices.push_back(v);
        }
    }
    
    for (unsigned int z = 0; z < subdivisions; ++z) {
        for (unsigned int x = 0; x < subdivisions; ++x) {
            unsigned int topLeft = z * (subdivisions + 1) + x;
            unsigned int topRight = topLeft + 1;
            unsigned int bottomLeft = (z + 1) * (subdivisions + 1) + x;
            unsigned int bottomRight = bottomLeft + 1;
            
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
}

void WavePlaneMesh::createShaderProgram() {
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

void WavePlaneMesh::setUniforms() const {

    
    unsigned int amplitudeLoc = glGetUniformLocation(shaderProgram, "waveAmplitude");
    glUniform1f(amplitudeLoc, waveAmplitude);
    
    unsigned int frequencyLoc = glGetUniformLocation(shaderProgram, "waveFrequency");
    glUniform1f(frequencyLoc, waveFrequency);
    
    unsigned int speedLoc = glGetUniformLocation(shaderProgram, "waveSpeed");
    glUniform1f(speedLoc, waveSpeed);
    
    unsigned int color1Loc = glGetUniformLocation(shaderProgram, "waveColor1");
    glUniform3f(color1Loc, waveColor1.x, waveColor1.y, waveColor1.z);
    
    unsigned int color2Loc = glGetUniformLocation(shaderProgram, "waveColor2");
    glUniform3f(color2Loc, waveColor2.x, waveColor2.y, waveColor2.z);
}

void WavePlaneMesh::renderCustomImGui() {
    ImGui::Text("Wave Parameters");
    ImGui::SliderFloat("Amplitude", &waveAmplitude, 0.0f, 1.0f);
    ImGui::SliderFloat("Frequency", &waveFrequency, 0.1f, 10.0f);
    ImGui::SliderFloat("Speed", &waveSpeed, 0.0f, 10.0f);
    ImGui::ColorEdit3("Color 1 (Low)", &waveColor1.x);
    ImGui::ColorEdit3("Color 2 (High)", &waveColor2.x);
}

const float* WavePlaneMesh::getVertexData() const {
    return vertices.data();
}

unsigned int WavePlaneMesh::getVertexDataSize() const {
    return vertices.size() * sizeof(float);
}

unsigned int WavePlaneMesh::getVertexCount() const {
    return indices.size();
}

unsigned int WavePlaneMesh::getStride() const {
    return 8;
}

void WavePlaneMesh::bind() {
    glBindVertexArray(VAO);
}

void WavePlaneMesh::unbind() {
    glBindVertexArray(0);
}

unsigned int WavePlaneMesh::getShaderProgram() const {
    return shaderProgram;
}

void WavePlaneMesh::useShaderProgram() const {
    glUseProgram(shaderProgram);
}

int WavePlaneMesh::getInitialAngle() const {
    return 0;
}
