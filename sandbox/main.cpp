#include <memory>
#include <SDL.h>
#include "retronomicon/lib/engine/game_engine.h"
#include "retronomicon/lib/core/splash_scene.h"
#include "retronomicon/lib/core/menu_scene.h"
#include "retronomicon/lib/core/scene_change_system.h"
#include "retronomicon/lib/core/scene_change_component.h"

using retronomicon::lib::engine::GameEngine;
using retronomicon::lib::core::Scene;
using retronomicon::lib::core::SceneChangeComponent;
using retronomicon::lib::core::SceneChangeSystem;
using retronomicon::lib::core::SplashScene;
using retronomicon::lib::core::MenuScene;

int main(int argc, char* argv[]) {
    GameEngine engine;

    if (!engine.init("Retronomicon", 800, 600)) {
        SDL_Log("Failed to initialize GameEngine.");
        return 1;
    }

    // Create SplashScene and attach SceneChangeSystem
    auto splash = std::make_shared<SplashScene>(engine.getRenderer());
    splash->addSystem(std::make_unique<SceneChangeSystem>(&engine));

    // Add SceneChangeComponent to the SplashScene entity itself
    splash->addComponent<SceneChangeComponent>("Menu");

    // Create MenuScene
    auto menu = std::make_shared<MenuScene>();

    // Register scenes to engine's SceneManager
    engine.registerScene("Splash", splash);
    engine.registerScene("Menu", menu);

    // Start with SplashScene
    engine.changeScene("Splash");
    engine.run();

    return 0;
}
