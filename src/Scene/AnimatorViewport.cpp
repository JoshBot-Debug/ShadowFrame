#include <string>

#include "AnimatorViewport.h"
#include "System/SystemManager.h"

struct GrabPayload
{
  glm::vec2 offset{0, 0};
  int zIndex = 0;

  GrabPayload(glm::vec2 offset, int zIndex) : offset(offset), zIndex(zIndex) {}
};

AnimatorViewport::AnimatorViewport(App *app) : app(app)
{
  this->system = new SystemManager();
}

AnimatorViewport::~AnimatorViewport()
{
  delete this->system;
}

void AnimatorViewport::onInitialize()
{
  this->setTitle("Animator");
  this->setBackgroundColor(glm::vec4{0.7f, 0.7f, 0.7f, 1.0f});
}

void AnimatorViewport::onInput(SDL_Event *event, float deltaTime)
{
  this->system->input(event, deltaTime);
}

void AnimatorViewport::onUpdate(float deltaTime)
{
  Registry *registry = this->app->getRegistry();
  Mouse *mouse = this->app->getMouseInput();

  this->system->update(deltaTime, this, registry, mouse);
}

void AnimatorViewport::onDrawViewport(float deltaTime)
{
  Registry *registry = this->app->getRegistry();

  this->system->draw(deltaTime, registry);
}