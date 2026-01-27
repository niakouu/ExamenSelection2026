#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <cstdint>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

class Mesh {
public:
  Mesh();

  glm::vec3 *getPosition() const { return position.get(); }

  glm::vec3 *getScale() const { return scale.get(); }

  void setPosition(glm::vec3 *pos) { *position = *pos; }

  void setScale(const glm::vec3 *s) { *scale = *s; }

  bool isVisible() const { return visible; }

  const std::string &getName() const { return name; }

  bool setName(const std::string &newName);

  bool setId(uint32_t newId);

  uint32_t getId() const { return id; }

  glm::mat4 getModelMatrix() const;

  void setVisible(bool vis) { visible = vis; }

  bool shouldUpdateMesh() const { return updateMesh; }

  // Optional funtcions

  virtual void renderCustomImGui() {};

  virtual void update(float deltaTime) {};

  // Virtual functions
  virtual int getDrawMode() const;

  virtual bool isIndexed() const { return false; }

  virtual ~Mesh() = default;

  virtual void renderImGui();

  virtual const float *getVertexData() const = 0;

  virtual unsigned int getVertexDataSize() const = 0;

  virtual unsigned int getVertexCount() const = 0;

  virtual unsigned int getStride() const = 0;

  virtual void bind() = 0;

  virtual void unbind() = 0;

  virtual void useShaderProgram() const = 0;

  virtual unsigned int getShaderProgram() const = 0;

  virtual void setUniforms() const = 0;

  virtual int getInitialAngle() const { return 45; }

  virtual std::vector<std::string> shaderFiles() const { return {}; }

protected:
  std::string name;
  uint32_t id;
  bool updateMesh = true;

  std::unique_ptr<glm::vec3> position;
  std::unique_ptr<glm::vec3> scale;
  std::unique_ptr<glm::vec3> rotationAxis;
  float rotationAngle;
  bool visible;

  static std::string loadShaderSource(const std::string &filepath);

  static unsigned int compileShader(unsigned int type, const std::string &path);

  static std::string buildPath(const std::string &directory,
                               const std::string &filename);
};

#endif
