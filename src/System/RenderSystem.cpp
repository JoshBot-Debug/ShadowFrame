#include "RenderSystem.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Component/Component.h"
#include "Bone/Bone.h"

RenderSystem::RenderSystem(Registry *registry, ShaderManager *shaderManager) : registry(registry), shaderManager(shaderManager)
{
  unsigned int vbo, ebo;

  // Create a vertex array & bind it.
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);

  // Create an array buffer, bind it & provide the mesh data.
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 4 * 5 * sizeof(float), &BONE_VERTICES, GL_STATIC_DRAW);

  // Create an element array buffer, bind it & provide the indices.
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 2 * sizeof(unsigned int), &BONE_INDICES, GL_STATIC_DRAW);

  // Setup our vertex locations for shaders
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void *)0);
  glEnableVertexAttribArray(0);

  // Setup our color locations for shaders
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Bind a new array buffer for the instance transforms
  glGenBuffers(1, &this->instanceVBO);
  glBindBuffer(GL_ARRAY_BUFFER, this->instanceVBO);
  // Keet it empty for now by passing nullptr
  glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

  // Setup our transform and rotation locations for shaders
  // using a vec3 x,y,z(rotation degrees)
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0);
  glEnableVertexAttribArray(2);
  glVertexAttribDivisor(2, 1);

  // Unbind vertex array
  glBindVertexArray(0);

  this->createBoneInstance({0.0f, 0.0f, 0.0f});

  this->shaderManager->load("Bone", "src/Shader/vertex.glsl", "src/Shader/fragment.glsl");
  this->shaderManager->bind("Bone");

  glm::mat4 projection = glm::ortho(0.0f, 725.0f, 0.0f, 504.0f, -1.0f, 1.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 0.0f));
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  glm::mat4 mvp = projection * view * model;

  this->shaderManager->addUniformMatrix4fv("Bone", mvp, "mvp");
}

void RenderSystem::draw(float deltaTime)
{

  // for (auto entity : registry->entities())
  // {
  //   if (entity->is("Bone"))
  //   {
  //     const auto [bone, transform] = entity->collect<CBone, CTransform>();
  //     glBindVertexArray(this->vao);
  //     glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, this->instances.size());
  //   }
  // }

  glBindVertexArray(this->vao);
  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, this->instances.size());
}

void RenderSystem::createBoneInstance(glm::vec3 transform)
{
  this->instances.push_back(transform);
  glBindBuffer(GL_ARRAY_BUFFER, this->instanceVBO);
  glBufferData(GL_ARRAY_BUFFER, this->instances.size() * 3 * sizeof(float), this->instances.data(), GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
