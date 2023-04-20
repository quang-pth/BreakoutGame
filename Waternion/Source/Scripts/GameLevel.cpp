#include"GameLevel.h"
#include"Core/Manager/ResourceManager.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"Scripts/Brick.h"

namespace Waternion
{
    using namespace ECS;

    GameLevel::GameLevel() : NativeScript() {

    }

    GameLevel::GameLevel(EntityID id) : NativeScript(id), mBricks(), 
        mFilepath(), mLevelWidth(0), mLevelHeight(0) 
    {

    }

    void GameLevel::OnStart() {
    }

    void GameLevel::LoadLevel(const std::string& filepath, uint16_t levelWidth, uint16_t levelHeight) {
        mBricks.clear();
        std::vector<std::vector<uint16_t>> tiles = ResourceManager::LoadLevel(filepath.c_str()); 
        if (tiles.size() > 0) {
            this->Init(tiles, levelWidth, levelHeight);
        }
    }

    void GameLevel::Init(const std::vector<std::vector<uint16_t>>& tiles, uint16_t levelWidth, uint16_t levelHeight) {
        uint16_t rowCount = tiles.size();
        uint16_t colCount = tiles[0].size();
        float unitWidth = StaticCast<float>(levelWidth) / colCount;
        float unitHeight = StaticCast<float>(levelHeight) / rowCount;

        for (uint16_t row = 0; row < rowCount; row++) {
            for (uint16_t col = 0; col < colCount; col++) {
                // Solid blocks
                if (tiles[row][col] == 1) {
                    Math::Vector3 position(-levelWidth / 2.0f + unitWidth * col, unitHeight * row, 0.0f);
                    Math::Vector2 size(unitWidth, unitHeight);
                    Math::Vector3 color(0.8f, 0.8f, 0.7f);
                    Shared<Entity> solidBrick = MakeShared<Entity>();
                    // Sprite
                    Shared<SpriteComponent> sprite = solidBrick->AddComponent<SpriteComponent>();
                    sprite->Init("assets/textures/block_solid.png", true, "SolidBlock");
                    sprite->SetColor(color);
                    // Box2D
                    Shared<Box2DComponent> box = solidBrick->AddComponent<Box2DComponent>();
                    box->SetBox(sprite->GetBox());
                    // Transform
                    Shared<TransformComponent> transform = solidBrick->GetComponent<TransformComponent>();
                    transform->SetPosition(position);
                    transform->SetScale(unitWidth / sprite->GetWidth(), unitHeight / sprite->GetHeight(), 1.0f);
                    // Script
                    Shared<ScriptComponent> script = solidBrick->AddComponent<ScriptComponent>();
                    script->Bind<Brick>();
                    script->GetInstance<Brick>()->SetIsSolid(true);
                    this->mBricks.emplace_back(solidBrick);
                }
                // Normal blocks
                else if (tiles[row][col] > 1) {
                    Math::Vector3 color(1.0f);
                    if (tiles[row][col] == 2) {
                        color = Math::Vector3(0.2f, 0.6f, 1.0f);
                    }
                    else if (tiles[row][col] == 3) {
                        color = Math::Vector3(0.0f, 1.0f, 0.0f);
                    }
                    else if (tiles[row][col] == 4) {
                        color = Math::Vector3(0.8f, 0.8f, 0.4f);
                    }
                    else if (tiles[row][col] == 5) {
                        color = Math::Vector3(1.0f, 0.5f, 0.0f);
                    }

                    Math::Vector3 position(-levelWidth / 2.0f + unitWidth * col, unitHeight * row, 0.0f);
                    Math::Vector2 size(unitWidth, unitHeight);
                    Shared<Entity> normalBlock = MakeShared<Entity>();
                    // Sprite
                    Shared<SpriteComponent> sprite = normalBlock->AddComponent<SpriteComponent>();
                    sprite->Init("assets/textures/block.png", true, "SolidBlock");
                    sprite->SetColor(color);
                    // Box2D
                    Shared<Box2DComponent> box = normalBlock->AddComponent<Box2DComponent>();
                    box->SetBox(sprite->GetBox());
                    // Transform
                    Shared<TransformComponent> transform = normalBlock->GetComponent<TransformComponent>();
                    transform->SetPosition(position);
                    transform->SetScale(unitWidth / sprite->GetWidth(), unitHeight / sprite->GetHeight(), 1.0f);
                    // Script
                    Shared<ScriptComponent> script = normalBlock->AddComponent<ScriptComponent>();
                    script->Bind<Brick>();
                    script->GetInstance<Brick>()->SetIsSolid(false);
                    this->mBricks.emplace_back(normalBlock);
                }
            }
        }
    }

    bool GameLevel::IsCompleted() {
        for (Shared<Entity> brick : mBricks) {
            Shared<Brick> brickScript = brick->GetComponent<ScriptComponent>()->GetInstance<Brick>();
            if (!brickScript->GetIsSolid() && !brickScript->GetIsDestroyed()) {
                return false;
            }
        }
        return true;
    }
} // namespace Waternion