#include "hierarchyScene.h"
#include <imgui_internal.h>

void HierarchyScene::onInitialize() {}

void HierarchyScene::onInput(SDL_Event *event, float deltaTime) {}

void HierarchyScene::onUpdate(float deltaTime) {}

void HierarchyScene::onDraw(float deltaTime)
{
  ImGuiWindowClass winClass;
  winClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
  ImGui::SetNextWindowClass(&winClass);

  ImGui::Begin("Tools", nullptr);

  if (ImGui::BeginPopupContextWindow("Tools Context"))
  {
    if (ImGui::MenuItem("Create armature"))
    {
      this->armatureSystem.createArmature();
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }

  ImGui::End();
}

void HierarchyScene::onCleanUp() {}
