#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "TextManager/textManager.h"
#include "ECS/registry.h"
#include "ECS/entity.h"

class Application
{
protected:
  SDL_Window *window = nullptr;     // Pointer to the SDL window.
  SDL_Renderer *renderer = nullptr; // Pointer to the SDL renderer used for drawing.

  // TODO need to remove text manager, this needs to be managed through an ecs.
  // Fonts need to be registered and the used through the ecs.
  TextManager *textManager = nullptr; // Pointer to the TextManager for handling text resources.

private:
  SDL_Color backgroundColor; // Background color of the window.

public:
  Application();
  virtual ~Application();

  /**
   * Enable or disable vertical synchronization (vsync).
   *
   * @param vsync An integer flag; if non-zero, vsync is enabled,
   *              otherwise, it is disabled. Vsync helps to prevent
   *              screen tearing by synchronizing the frame rate with
   *              the display's refresh rate.
   */
  void setVSync(int vsync);

  /**
   * Set the dimensions of the SDL window.
   *
   * @param w The width of the window in pixels.
   * @param h The height of the window in pixels.
   */
  void setWindowDimensions(int w, int h);

  /**
   * Set the title of the SDL window.
   *
   * @param title A C-style string representing the title of the window.
   */
  void setWindowTitle(const char *title);

  /**
   * Set the background color of the window. Every frame will
   * call SDL_RenderClear with this color to set the background
   *
   * @param r the red value used to draw on the rendering target.
   * @param g the green value used to draw on the rendering target.
   * @param b the blue value used to draw on the rendering target.
   * @param a the alpha value used to draw on the rendering target; usually SDL_ALPHA_OPAQUE (255). Use SDL_SetRenderDrawBlendMode to specify how the alpha channel is used.
   */
  void setBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  /**
   * Open the SDL window and renderer.
   *
   * This method initializes and displays the SDL window.
   */
  void open();

  /**
   * @brief Called once at the start of each frame.
   *
   * This method is responsible for processing user input events,
   * such as keyboard and mouse actions. It should handle all
   * relevant input before any game state updates occur.
   *
   * @param event The SDL_Event structure to be filled with the next event from the queue, or NULL.
   *
   * @param deltaTime  The time elapsed between the current and the last frame,
   *                   measured in milliseconds. This value can be used for frame-rate independent
   *                   movement and animations.
   */
  virtual void onInput(SDL_Event *event, float deltaTime) = 0;

  /**
   * @brief Called once after onInput() for each frame.
   *
   * This method is responsible for updating the game/application state.
   * It should incorporate changes based on user input and other
   * game logic, such as physics, animations, and AI updates.
   *
   * @param deltaTime  The time elapsed between the current and the last frame,
   *                   measured in milliseconds. This value can be used for frame-rate independent
   *                   movement and animations.
   */
  virtual void onUpdate(float deltaTime) = 0;

  /**
   * @brief Called once after onUpdate() for each frame.
   *
   * This method is responsible for rendering the current state of
   * the game/application to the screen. It should clear the
   * previous frame and draw all visual elements based on the
   * updated state.
   *
   * @param deltaTime  The time elapsed between the current and the last frame,
   *                   measured in milliseconds. This value can be used for frame-rate independent
   *                   movement and animations.
   */
  virtual void onDraw(float deltaTime) = 0;

  /**
   * @brief Called to initialize the game or application resources.
   *
   * This method is responsible for setting up necessary components,
   * loading assets, creating game objects, and performing any initial
   * configuration required before the game starts. It should be called
   * at the beginning of the game loop.
   */
  virtual void onInitialize() = 0;

  /**
   * @brief Called to clean up resources before the game or application exits.
   *
   * This method is responsible for releasing or unloading any resources
   * that were allocated during initialization, such as textures, sounds,
   * and other game data. It should be called before shutting down the
   * application to prevent memory leaks and ensure proper cleanup.
   */
  virtual void onCleanUp() = 0;
};