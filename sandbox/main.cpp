#include <memory>
#include <SDL.h>
#include "retronomicon/lib/engine/game_engine.h"
#include "retronomicon/lib/scene/splash/splash_scene.h"
#include "retronomicon/lib/scene/menu/menu_scene.h"
#include "retronomicon/lib/scene/scene_change_system.h"
#include "retronomicon/lib/scene/scene_change_component.h"
#include "retronomicon/lib/asset/asset_manager.h"
#include "retronomicon/lib/graphic/render_system.h"
#include <iostream>

using retronomicon::lib::engine::GameEngine;
using retronomicon::lib::core::Scene;
using retronomicon::lib::scene::SceneChangeComponent;
using retronomicon::lib::scene::SceneChangeSystem;
using retronomicon::lib::scene::splash::SplashScene;
using retronomicon::lib::scene::menu::MenuScene;
using retronomicon::lib::asset::AssetManager;
using retronomicon::lib::graphic::RenderSystem;
int main(int argc, char* argv[]) {
    GameEngine engine;

    if (!engine.init("Retronomicon", 800, 600)) {
        SDL_Log("Failed to initialize GameEngine.");
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
    }
    //load image
    auto assetManager = std::make_shared<AssetManager>(engine.getRenderer());
    auto rawImage = assetManager->loadImage("asset/image/retronomicon_logo.png", "retronomicon_logo");
    auto bgImage = assetManager->loadImage("asset/image/menu_background.png", "menu_background");
    auto nineSliceImage = assetManager->loadImage("asset/image/space.png", "space");
    auto font = assetManager->loadFont("asset/font/manaspc.ttf", "manaspc.ttf",20,false);

    // Create SplashScene and attach SceneChangeSystem
    auto splash = std::make_shared<SplashScene>(engine.getRenderer());
    splash->setImage(rawImage->getTexture());
    splash->addSystem(std::make_unique<SceneChangeSystem>(&engine));

    // Add SceneChangeComponent to the SplashScene entity itself
    splash->addComponent<SceneChangeComponent>("Menu");

    // Create MenuScene
    auto menu = std::make_shared<MenuScene>(bgImage,font);
    menu->addSystem(std::make_unique<SceneChangeSystem>(&engine));
    menu->addSystem(std::make_unique<RenderSystem>(engine.getRenderer()));
    menu->createMenu(nineSliceImage,font);

    // Register scenes to engine's SceneManager
    engine.registerScene("Splash", splash);
    engine.registerScene("Menu", menu);

    // Start with SplashScene
    engine.changeScene("Splash");
    engine.run();

    return 0;
}
