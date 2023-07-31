#include"MainScene.h"

#include<Core/Template.h>
#include<ECS/Entity.h>
#include<Core/Application.h>

using namespace Waternion;
using namespace Waternion::ECS;

namespace Client
{
    MainScene::MainScene() : GameScene() {

    }

    void MainScene::Load() {
        RefObject<Entity> background = CreateObject<Entity>("Background");
        background->AddComponent<SpriteComponent>()->Init("assets/textures/background.jpg", false, "Background");
        float windowWidth = Application::GetInstance()->GetWindowWidth();
        float windowHeight = Application::GetInstance()->GetWindowHeight();
        background->GetComponent<TransformComponent>()->SetPosition(-windowWidth / 2.0f, -windowHeight / 2.0f, 100.0f);
    }
} // namespace Client