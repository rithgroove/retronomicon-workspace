#include <memory>
#include <SDL.h>
#include "retronomicon/lib/engine/game_engine.h"
#include "retronomicon/lib/scene/splash/splash_scene.h"
#include "retronomicon/lib/scene/menu/menu_scene.h"
#include "retronomicon/lib/scene/scene_change_system.h"
#include "retronomicon/lib/scene/scene_change_component.h"
#include "retronomicon/lib/asset/asset_manager.h"
#include "retronomicon/lib/graphic/render_system.h"
#include "retronomicon/lib/conversation/asset/conversation_character_module_loader.h"
#include "retronomicon/lib/audio/audio_wrapper.h"
#include "retronomicon/lib/conversation/conversation_loader.h"
#include <iostream>

using retronomicon::lib::engine::GameEngine;
using retronomicon::lib::core::Scene;
using retronomicon::lib::scene::SceneChangeComponent;
using retronomicon::lib::scene::SceneChangeSystem;
using retronomicon::lib::scene::splash::SplashScene;
using retronomicon::lib::scene::menu::MenuScene;
using retronomicon::lib::asset::AssetManager;
using retronomicon::lib::graphic::RenderSystem;
using retronomicon::lib::audio::AudioWrapper;
using retronomicon::lib::conversation::asset::ConversationCharacterModuleLoader;
int main(int argc, char* argv[]) {
    GameEngine engine;

    if (!engine.init("Retronomicon", 800, 600)) {
        SDL_Log("Failed to initialize GameEngine.");
        return 1;
    }

    engine.registerCharacterLoaderModule(std::make_shared<ConversationCharacterModuleLoader>());
    engine.loadCharacterDb("asset/conversation/characters.json");

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
    }
    auto* audio = new AudioWrapper();
    audio->init();

    //load image
    auto assetManager = engine.getAssetManager();
    auto conversation = assetManager->loadText("asset/conversation/conversation.json","new_game_conversation",false);

    // Create SplashScenes
    auto splash = std::make_shared<SplashScene>(&engine,"asset/image/retronomicon_logo.png", "retronomicon_logo","Splash2");
    auto splash2 = std::make_shared<SplashScene>(&engine,"asset/image/npg_logo.png", "npg_logo","Menu");
    // auto splash3 = std::make_shared<SplashScene>(&engine,nineSliceImage,"Menu");
    auto conv_scene = retronomicon::lib::conversation::ConversationLoader::loadFromTextAsset(conversation);
    conv_scene->setEngine(&engine);
    conv_scene->changeFont("asset/font/manaspc.ttf", "manaspc.ttf",20);
    conv_scene->setTextBoxBackground("asset/image/space2.png", "space2");

    // Create MenuScene
    auto menu = std::make_shared<MenuScene>(&engine,"asset/image/menu_background.png","asset/image/space.png","asset/font/manaspc.ttf",16,"asset/sound/music/background_music.ogg","asset/sound/foley/funny_swish.ogg");

    // Register scenes to engine's SceneManager
    engine.registerScene("Splash", splash);
    engine.registerScene("Splash2", splash2);
    // engine.registerScene("Splash3", splash3);
    engine.registerScene("Menu", menu);
    engine.registerScene("New Game", conv_scene);

    // Start with SplashScene
    engine.changeScene("Splash");
    engine.run();

    return 0;
}
