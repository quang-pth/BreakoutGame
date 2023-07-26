#include"MainScene.h"

#include<ECS/Entity.h>
#include<ECS/Component/Behavior/ScriptComponent.h>
#include<Core/Application.h>

#include<Scripts/PlayerController.h>
#include<Scripts/Background.h>
#include<Scripts/Ball.h>
#include<Scripts/Powers/PowerManager.h>
#include<Scripts/GameLevel.h>
#include<Scripts/GameManager.h>

namespace Client
{
    using namespace Waternion;
    using namespace Waternion::ECS;

    MainScene::MainScene() : GameScene() {

    }

    void MainScene::Load() {
        // TODO: export template function for all types to DLL
        Shared<Entity> player = MakeShared<Entity>("Paddle");
        player->AddComponent<ScriptComponent>()->Bind(new PlayerController(player->GetID()));
        
        Shared<Entity> background = MakeShared<Entity>("Background");
        background->AddComponent<ScriptComponent>()->Bind(new Background(background->GetID()));

        Shared<Entity> ball = MakeShared<Entity>("Ball");
        ball->AddComponent<ScriptComponent>()->Bind(new Ball(ball->GetID()));

        Shared<Entity> powerManager = MakeShared<Entity>("PowerManager");
        powerManager->AddComponent<ScriptComponent>()->Bind(new PowerManager(powerManager->GetID()));

        Shared<Entity> gameManager = MakeShared<Entity>("GameManager");
        gameManager->AddComponent<ScriptComponent>()->Bind(new GameManager(gameManager->GetID()));

        uint32_t windowWidth = Application::GetInstance()->GetWindowWidth();
        uint32_t windowHeight = Application::GetInstance()->GetWindowHeight();
        Shared<Entity> gameLevel = MakeShared<Entity>("GameLevel");
        gameLevel->AddComponent<ScriptComponent>()->Bind(new GameLevel(gameLevel->GetID()));
        gameLevel->GetComponent<ScriptComponent>()->GetInstance<GameLevel>()->LoadLevel(0, "assets/levels/one.lvl", windowWidth, windowHeight);
        gameLevel->GetComponent<ScriptComponent>()->GetInstance<GameLevel>()->LoadLevel(1, "assets/levels/two.lvl", windowWidth, windowHeight);
        gameLevel->GetComponent<ScriptComponent>()->GetInstance<GameLevel>()->LoadLevel(2, "assets/levels/three.lvl", windowWidth, windowHeight);
        gameLevel->GetComponent<ScriptComponent>()->GetInstance<GameLevel>()->LoadLevel(3, "assets/levels/four.lvl", windowWidth, windowHeight);
    }
} // namespace Client