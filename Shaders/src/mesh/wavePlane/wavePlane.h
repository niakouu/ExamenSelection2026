#ifndef WAVE_PLANE_H
#define WAVE_PLANE_H

#include "../mesh.h"
#include <vector>

class WavePlaneMesh : public Mesh {
public:
    WavePlaneMesh(unsigned int subdivisions = 50, float width = 4.0f, float height = 4.0f);
    ~WavePlaneMesh();
    
    unsigned int getVertexCount() const override;
    unsigned int getStride() const override;
    const float* getVertexData() const override;
    unsigned int getVertexDataSize() const override;
    void bind() override;
    void unbind() override;
    unsigned int getShaderProgram() const override;
    void useShaderProgram() const override;
    int getInitialAngle() const override;
    void setUniforms() const override;
    void renderCustomImGui() override;
    bool isIndexed() const override { return true; }

private:
    unsigned int VAO, VBO, EBO;
    unsigned int shaderProgram;
    
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    unsigned int subdivisions;
    float width;
    float height;
    
    mutable float waveAmplitude = 0.3f;
    mutable float waveFrequency = 3.0f;
    mutable float waveSpeed = 2.0f;
    mutable glm::vec3 waveColor1 = glm::vec3(0.0f, 0.3f, 0.8f);  
    mutable glm::vec3 waveColor2 = glm::vec3(0.0f, 0.8f, 1.0f);
    
    const char* VS_SHADER_PATH = "wavePlane/";
    const char* FS_SHADER_PATH = "wavePlane/";
    const char* CURRENT_VS_SHADER = "wavePlane.vs.glsl";
    const char* CURRENT_FS_SHADER = "wavePlane.fs.glsl";
    
    void generateMesh();
    void createShaderProgram();
};

#endif
