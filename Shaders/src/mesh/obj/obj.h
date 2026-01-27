#ifndef OBJ_H
#define OBJ_H

#include "../mesh.h"
#include <vector>

class ObjMesh : public Mesh {
public:
    ObjMesh(const std::string& meshName, const std::string& fileName);
    ~ObjMesh();
    
    unsigned int getVertexCount() const override;
    unsigned int getStride() const override;
    const float* getVertexData() const override;
    unsigned int getVertexDataSize() const override;
    void bind() override;
    void unbind() override;
    unsigned int getShaderProgram() const override;
    void useShaderProgram() const override;
    int getDrawMode() const override;
    void setUniforms() const override;
    
private:
    std::vector<float> vertexData;
    unsigned int VAO, VBO;
    unsigned int shaderProgram;
    float objColor[3] = {0.8f, 0.5f, 0.3f};
    
    const std::string VS_SHADER_PATH = "phong/";
    const std::string FS_SHADER_PATH = "phong/";
    const std::string CURRENT_VS_SHADER = "phong.vs.glsl";
    const std::string CURRENT_FS_SHADER = "phong.fs.glsl";

    void loadOBJ(const std::string& filepath);
    void createShaderProgram();
    void setupMeshBuffers();

};

#endif
