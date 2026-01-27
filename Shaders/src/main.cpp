#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "mesh/obj/obj.h"
#include "input/input.h"
#include "scene/scene.h"
#include <bits/stdc++.h>
#include <memory>

#include "constructor/meshConstructor.h"


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

GLFWwindow *initGlfw(Input &input, int width, int height, const char *title) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return nullptr;
  }

  glfwSetWindowUserPointer(window, &input);

  glfwSetKeyCallback(
      window, [](GLFWwindow *win, int key, int sc, int action, int mods) {
        Input *in = (Input *)glfwGetWindowUserPointer(win);
        in->keyCallback(key, action);
      });

  glfwSetCursorPosCallback(window, [](GLFWwindow *win, double x, double y) {
    Input *in = (Input *)glfwGetWindowUserPointer(win);
    in->mouseMoveCallback(x, y);
  });

  glfwSetScrollCallback(window, [](GLFWwindow *win, double xoff, double yoff) {
    Input *in = (Input *)glfwGetWindowUserPointer(win);
    in->scrollCallback(yoff);
  });

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW\n";
    return nullptr;
  }
  return window;
}

void initImGui(GLFWwindow *window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
}

void imGuiWindow(std::vector<std::unique_ptr<Scene>> *scenes,
                 Scene*& currentScene) {
  // Scene control panel
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
  ImGui::Begin("Scene Control Panel", NULL,
               ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
  
  ImGui::Text("Scenes:");
  ImGui::Separator();
  for(size_t i = 0; i < scenes->size(); ++i) {
      if (ImGui::Selectable(scenes->at(i)->getName(), currentScene == scenes->at(i).get())) {
          currentScene = scenes->at(i).get();
      }
  }

  
  ImGui::End();

  // Instructions
  ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_FirstUseEver);
  ImGui::Begin("Movements", NULL, ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::Text("Use WASD to move the camera.");
  ImGui::Text("Use SPACE to move up.");
  ImGui::Text("Use SHIFT to move down.");
  ImGui::Text("Press Q or ESC to quit.");
  ImGui::End();
}

void handleCameraMovement(Input &input, glm::vec3 &cameraPos, float deltaTime) {
  float speed = 2.5f;
  if (input.getKeyHold(Input::W))
    cameraPos.z += speed * deltaTime;
  if (input.getKeyHold(Input::S))
    cameraPos.z -= speed * deltaTime;
  if (input.getKeyHold(Input::A))
    cameraPos.x += speed * deltaTime;
  if (input.getKeyHold(Input::D))
    cameraPos.x -= speed * deltaTime;
  if (input.getKeyHold(Input::SPACE))
    cameraPos.y -= speed * deltaTime;
  if (input.getKeyHold(Input::SHIFT))
    cameraPos.y += speed * deltaTime;
}

std::shared_ptr<std::vector<std::unique_ptr<Scene>>> createScenes() {

  auto& meshConstructor = MeshConstructor::getInstance();

  auto scenes = std::make_shared<std::vector<std::unique_ptr<Scene>>>();

  auto scene1 = std::make_unique<Scene>("Wave Scene");
  auto waveMesh = meshConstructor.createMesh(WAVE_PLANE);
  scene1->addMesh(std::move(waveMesh), "wave_plane");

  scenes->push_back(std::move(scene1));

  auto scene2 = std::make_unique<Scene>("Phong shading Scene");
  auto teapotMesh = std::make_unique<ObjMesh>("teapot", "teapot.obj");
  scene2->addMesh(std::move(teapotMesh), "teapot1");

  scenes->push_back(std::move(scene2));

  auto scene3 = std::make_unique<Scene>("Third Scene");
  auto cubeMesh = meshConstructor.createMesh(CUBE);
  scene3->addMesh(std::move(cubeMesh), "cube1");
  scenes->push_back(std::move(scene3));

  return scenes;
}

int main() {

  Input input;
  GLFWwindow *window = initGlfw(input, 800, 600, "Shaders");
  initImGui(window);

  if (!window)
    return -1;

  bool run = true;
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;


  auto scenes = createScenes();
  Scene *currentScene = scenes->at(0).get();

  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -5.0f);

  glEnable(GL_DEPTH_TEST);
  while (!glfwWindowShouldClose(window) && run) {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::StyleColorsDark();

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwPollEvents();

    handleCameraMovement(input, cameraPos, deltaTime);

    imGuiWindow(scenes.get(), currentScene);

    if (input.getKeyHold(Input::Q) || input.getKeyHold(Input::ESC))
      run = false;

    glm::mat4 view = glm::translate(glm::mat4(1.0f), cameraPos);
    glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // Render all mesh instances in the scene
    currentScene->update(deltaTime);
    currentScene->render(&view, &projection, &cameraPos);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  std::cout << "Goodbye !" << std::endl;

  glfwMakeContextCurrent(window);
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
