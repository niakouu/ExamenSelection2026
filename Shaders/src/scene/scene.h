#ifndef SCENE_H
#define SCENE_H

#include "../mesh/mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <memory>
#include <string>


typedef struct {
    glm::vec3 position;
    glm::vec3 color;

} Light;


class Scene {
public:
    Scene(const char* sceneName);
    ~Scene();

    void addMesh(std::unique_ptr<Mesh> mesh, const std::string& id);

    void removeMeshInstance(const std::string& id);
    
    void update(float deltaTime);

    void render(const glm::mat4* view, const glm::mat4* projection,
                const glm::vec3* cameraPos);

    void setLight(glm::vec3 position, glm::vec3 color);

    const char* getName() const { return name; }

private:
    std::unique_ptr<std::map<std::string, Mesh*>> meshes;
    std::unique_ptr<Light> light;
    const char* name;
};

#endif