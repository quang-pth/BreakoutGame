#include"GameLevel.h"
#include"Core/Manager/ResourceManager.h"
#include"Core/Application.h"

// Components
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Audio/SoundComponent.h"
#include"ECS/Component/UI/TextComponent.h"

#include"Scripts/Brick.h"

namespace Waternion
{
    using namespace ECS;

    GameLevel::GameLevel() : NativeScript() {

    }

    GameLevel::GameLevel(EntityID id) : NativeScript(id),  mLevelWidth(0), mLevelHeight(0), mLevels()
    {
        mLevels.resize(4);
    }

    void GameLevel::OnStart() {
    }

    void GameLevel::LoadLevel(uint32_t level, const std::string& filepath, uint16_t levelWidth, uint16_t levelHeight) {
        std::vector<std::vector<uint16_t>> tiles = ResourceManager::LoadLevel(filepath.c_str()); 
        if (tiles.size() > 0) {
            this->Init(level, tiles, levelWidth, levelHeight);
        }
    }

    void GameLevel::Init(uint32_t level, const std::vector<std::vector<uint16_t>>& tiles, uint16_t levelWidth, uint16_t levelHeight) {
        uint16_t rowCount = tiles.size();
        uint16_t colCount = tiles[0].size();
        float unitWidth = StaticCast<float>(levelWidth) / colCount;
        float unitHeight = StaticCast<float>(levelHeight) / rowCount;

        mLevels[level].clear();
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
                    // Sound
                    solidBrick->AddComponent<SoundComponent>("assets/audio/solid.wav", false);
                    // Script
                    Shared<ScriptComponent> script = solidBrick->AddComponent<ScriptComponent>();
                    script->Bind<Brick>();
                    script->GetInstance<Brick>()->SetIsSolid(true);
                    mLevels[level].emplace_back(solidBrick);
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
                    // Sound
                    normalBlock->AddComponent<SoundComponent>("assets/audio/bleep.mp3", false);
                    // Script
                    Shared<ScriptComponent> script = normalBlock->AddComponent<ScriptComponent>();
                    script->Bind<Brick>();
                    script->GetInstance<Brick>()->SetIsSolid(false);
                    mLevels[level].emplace_back(normalBlock);
                }
            }
        }
    }

    bool GameLevel::IsCompleted() {
        for (Shared<Entity> brick : mLevels[mCurrentLevel]) {
            Shared<Brick> brickScript = brick->GetComponent<ScriptComponent>()->GetInstance<Brick>();
            if (!brickScript->GetIsSolid() && brickScript->GetOwner()->GetIsActive()) {
                return false;
            }
        }
        return true;
    }

    void GameLevel::Reset() {
        ChangeLevel(mCurrentLevel);
    }

    void GameLevel::ChangeLevel(uint32_t level) {
        mCurrentLevel = Math::Abs(StaticCast<int32_t>(level % mLevels.size()));
        for(uint32_t i = 0; i < mLevels.size(); i++) {
            for (Shared<Entity> brick : mLevels[i]) {
                if (i == mCurrentLevel) {
                    brick->SetActivate(true);
                }
                else {
                    brick->SetActivate(false);
                }
            }
        }
    }
} // namespace Waternion