#include"MainScene.h"

#include<Core/Template.h>
#include<Core/Application.h>
#include<ECS/Entity.h>
#include<ECS/System/BatchRenderer.h>

using namespace Waternion;
using namespace Waternion::ECS;

namespace Client
{
    MainScene::MainScene() : GameScene() {
    }

    void MainScene::Load() {
        int xOffset = 10;
        int yOffset = 10;
        float totalWidth = (float) (Application::GetInstance()->GetWindowWidth() - xOffset * 2);
        float totalHeight = (float) (Application::GetInstance()->GetWindowHeight() - yOffset * 2);
        float sizeX = totalWidth / 20.0f;
        float sizeY = totalHeight / 20.0f;
        
        RefObject<BatchRenderer> batchRenderer = GetSystem<BatchRenderer>();
        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                float xPos = xOffset + (x * sizeX);
                float yPos = yOffset + (y * sizeY);
                RefObject<Entity> entity = CreateObject<Entity>("Background");
                entity->GetComponent<TransformComponent>()->SetPosition(xPos, yPos, 0);

                RefObject<SpriteComponent> sprite = entity->AddComponent<SpriteComponent>();
                sprite->Init("assets/textures/background.jpg", false, "Background");
                sprite->SetColor(xPos / totalWidth, yPos / totalHeight, 1.0f, 1.0f);

                batchRenderer->AddSprite(sprite);
            }
        }
    }
} // namespace Client