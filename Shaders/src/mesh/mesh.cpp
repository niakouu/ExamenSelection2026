#include "mesh.h"
#include "../imgui/imgui.h"
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sstream>

#include <iostream>

Mesh::Mesh() {
  position = std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f);
  scale = std::make_unique<glm::vec3>(1.0f, 1.0f, 1.0f);
  rotationAngle = 0.0f;
  rotationAxis = std::make_unique<glm::vec3>(0.0f, 1.0f, 0.0f);
  visible = true;
  name = "DefaultMesh";
  id = 0;
}

glm::mat4 Mesh::getModelMatrix() const {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, *position);
  model = glm::rotate(model, rotationAngle, *rotationAxis);
  model = glm::scale(model, *scale);
  return model;
}

void Mesh::renderImGui() {
  if (ImGui::TreeNode(getName().c_str())) {
    ImGui::Checkbox("Visible", &visible);
    if (ImGui::Button("Reset All")) {
      *position = glm::vec3(0.0f, 0.0f, 0.0f);
      *scale = glm::vec3(1.0f, 1.0f, 1.0f);
      *rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
      rotationAngle = 0.0f;
    }

    ImGui::Text("Position");
    ImGui::DragFloat3("##Position", &position->x, 0.1f);
    ImGui::SameLine();
    if (ImGui::Button("Reset##Position")) {
      *position = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    ImGui::Text("Scale");
    ImGui::DragFloat3("##Scale", &scale->x, 0.1f);
    ImGui::SameLine();
    if (ImGui::Button("Reset##Scale")) {
      *scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    ImGui::Text("Rotation Axis");
    ImGui::DragFloat3("##Rotation Axis", &rotationAxis->x, 0.1f);
    ImGui::SameLine();
    if (ImGui::Button("Reset##RotationAxis")) {
      *rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    ImGui::Text("Rotation Angle");
    ImGui::DragFloat("##Rotation Angle", &rotationAngle, 0.01f);
    ImGui::SameLine();
    if (ImGui::Button("Reset##RotationAngle")) {
      rotationAngle = 0.0f;
    }

    renderCustomImGui();

    ImGui::TreePop();
  }
}

std::string Mesh::loadShaderSource(const std::string &filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Failed to open shader file: " << filepath << std::endl;
    return "";
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

unsigned int Mesh::compileShader(unsigned int type, const std::string &path) {

  std::string src = Mesh::loadShaderSource(std::string(COMPILED_SHADER_DIR) + path);
  const char *source = src.c_str();

  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info[512];
    glGetShaderInfoLog(shader, 512, NULL, info);
    std::cerr << "Error compiling shader (" << path << "): " << info
              << std::endl;
  }
  return shader;
}

std::string Mesh::buildPath(const std::string &directory,
                            const std::string &filename) {
  return directory + filename;
}

bool Mesh::setName(const std::string &newName) {
  if (newName.empty()) {
    std::cerr << "Error: Mesh name cannot be empty." << std::endl;
    return false;
  }
  name = newName;
  return true;
}

int Mesh::getDrawMode() const { return GL_TRIANGLES; }

bool Mesh::setId(uint32_t newId) {
  if (id != 0)
    return false;
  id = newId;
  return true;
}