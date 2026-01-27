#include "meshConstructor.h"
#include "mesh/cube/cube.h"
#include "mesh/mesh.h"
#include "mesh/obj/obj.h"
#include "mesh/wavePlane/wavePlane.h"
#include <cstdint>
#include <utility>
#include <stdexcept>

 MeshConstructor* MeshConstructor::instance = nullptr;

MeshConstructor& MeshConstructor::getInstance() {
  if (instance == nullptr) {
    instance = new MeshConstructor();
  }
  return *instance;
}

MeshConstructor::MeshConstructor() {
  meshTypeToID = std::make_unique<std::map<MeshType, uint16_t>>();
  for (uint16_t i = 0; i < MESH_COUNT; ++i) {
    (*meshTypeToID)[static_cast<MeshType>(i)] = 0;
  }
}

std::unique_ptr<Mesh> MeshConstructor::createMesh(MeshType meshType) {
  (*meshTypeToID)[static_cast<MeshType>(meshType)]++;

  std::unique_ptr<Mesh> mesh;
  switch (meshType) {
  case CUBE:
    mesh = createCubeMesh();
    break;
    break;
  case WAVE_PLANE:
    mesh = createWavePlaneMesh();
    break;
  case TEAPOT:
    mesh = createObjMesh("teapot", "teapot.obj");
    break;
  default:
    throw std::invalid_argument("Invalid mesh type");
  }

  mesh->setId((*meshTypeToID)[static_cast<MeshType>(meshType)]);

  return mesh;
}

uint16_t MeshConstructor::getMeshCount(MeshType meshType) {
  return (*meshTypeToID)[static_cast<MeshType>(meshType)];
}

std::unique_ptr<Mesh> MeshConstructor::createCubeMesh() {

  auto mesh = std::make_unique<CubeMesh>();
  return std::move(mesh);
}

std::unique_ptr<Mesh> MeshConstructor::createWavePlaneMesh(unsigned int subdivisions) {
  auto mesh = std::make_unique<WavePlaneMesh>(subdivisions);
  return std::move(mesh);
}

std::unique_ptr<Mesh>
MeshConstructor::createObjMesh(const std::string &name,
                               const std::string &filepath) {
  auto mesh = std::make_unique<ObjMesh>(name, filepath);
  return std::move(mesh);
}
