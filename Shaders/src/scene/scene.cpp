#include "scene.h"
#include "../imgui/imgui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

Scene::Scene(const char *sceneName) : light(nullptr), name(sceneName) {
  meshes = std::make_unique<std::map<std::string, Mesh *>>();
  Light lightObj;
  lightObj.position = glm::vec3(0.0f, 3.0f, 0.0f);
  lightObj.color = glm::vec3(0.0f, 1.0f, 1.0f);
  light = std::make_unique<Light>(lightObj);
}

Scene::~Scene() {}

void Scene::addMesh(std::unique_ptr<Mesh> mesh, const std::string &id) {
  if (meshes->find(id) != meshes->end()) {
    std::cerr << "Warning: Mesh with id '" << id << "' already exists\n";
    return;
  }
  meshes->emplace(id, mesh.release());
}

void Scene::setLight(glm::vec3 position, glm::vec3 color) {
  light->position = position;
  light->color = color;
}

void Scene::removeMeshInstance(const std::string &id) {
  auto it = meshes->find(id);
  if (it != meshes->end()) {
    meshes->erase(it);
    return;
  }
  std::cerr << "Warning: Mesh with id '" << id << "' not found\n";
}

void Scene::update(float deltaTime) {
  for (auto &[id, mesh] : *meshes) {
    if (!mesh->shouldUpdateMesh())
      continue;

    mesh->update(deltaTime);
  }
}

void Scene::render(const glm::mat4 *view, const glm::mat4 *projection,
                   const glm::vec3 *cameraPos) {

  ImGui::SetNextWindowPos(ImVec2(0, 100), ImGuiCond_FirstUseEver);
  ImGui::Begin("Meshes Position", NULL, ImGuiWindowFlags_AlwaysAutoResize);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int index = 0;
  for (auto &[id, mesh] : *meshes) {

    ImGui::PushID(index);
    mesh->renderImGui();
    ImGui::PopID();

    if (!mesh->isVisible()) {
      index++;
      continue;
    }

    mesh->useShaderProgram();
    unsigned int shaderProgram = mesh->getShaderProgram();

    glm::mat4 model = mesh->getModelMatrix();

    // Common uniform locations
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
    unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &(*view)[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &(*projection)[0][0]);
    glUniform3f(viewPosLoc, cameraPos->x, cameraPos->y, cameraPos->z);

    unsigned int timeLoc = glGetUniformLocation(shaderProgram, "time");
    float time = glfwGetTime() / 5.0f;
    glUniform1f(timeLoc, time);

    unsigned int lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    unsigned int lightColorLoc =
        glGetUniformLocation(shaderProgram, "lightColor");
    glUniform3f(lightPosLoc, light->position.x, light->position.y,
                light->position.z);
    glUniform3f(lightColorLoc, light->color.x, light->color.y, light->color.z);

    mesh->setUniforms();

    mesh->bind();
    if (mesh->isIndexed()) {
      glDrawElements(mesh->getDrawMode(), mesh->getVertexCount(),
                     GL_UNSIGNED_INT, 0);
    } else {
      glDrawArrays(mesh->getDrawMode(), 0, mesh->getVertexCount());
    }

    mesh->unbind();
    index++;
  }
  ImGui::End();
}
