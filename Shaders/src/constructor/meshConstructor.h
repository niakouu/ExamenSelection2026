#ifndef MESH_CONSTRUCTOR_CPP
#define MESH_CONSTRUCTOR_CPP

#include "../src/mesh/mesh.h"
#include <cstdint>
#include <map>
#include <memory>
#include <sys/types.h>

enum MeshType { CUBE, WAVE_PLANE, TEAPOT, MESH_COUNT };

class MeshConstructor {
public:
  static MeshConstructor& getInstance();
  
  std::unique_ptr<Mesh> createMesh(MeshType meshType);
  uint16_t getMeshCount(MeshType meshType);

  MeshConstructor();
private:
  ~MeshConstructor() = default;
  
  MeshConstructor(const MeshConstructor&) = delete;
  MeshConstructor& operator=(const MeshConstructor&) = delete;
  
  static MeshConstructor* instance;
  std::unique_ptr<std::map<MeshType, uint16_t>> meshTypeToID;
  std::string *setDefaultName(MeshType meshType, Mesh *mesh);
  std::unique_ptr<Mesh> createCubeMesh();
  std::unique_ptr<Mesh> createWavePlaneMesh(unsigned int subdivisions = 50);
  std::unique_ptr<Mesh> createObjMesh(const std::string &name,
                                      const std::string &filepath);
};

#endif