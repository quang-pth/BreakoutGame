#include"GameLevel.h"
#include"Core/Manager/ResourceManager.h"
#include"Core/Application.h"
#include"Core/Event/Event.h"
#include"Scene/GameScene.h"

// Components
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Audio/SoundComponent.h"
#include"ECS/Component/UI/TextComponent.h"

#include"Scripts/Brick.h"
#include"Scripts/Ball.h"
#include"Scripts/Powers/PowerManager.h"

namespace Waternion
{
    using namespace ECS;

    GameLevel::GameLevel() : NativeScript() {

    }

    GameLevel::GameLevel(EntityID id) : NativeScript(id),  mLevelWidth(0), mLevelHeight(0), mLevels(), mPlayerScore(0), mLevelSize()
    {
        mLevels.resize(4);
    }

    void GameLevel::OnAwake() {
        uint32_t windowWidth = Application::GetInstance()->GetWindowWidth();
        uint32_t windowHeight = Application::GetInstance()->GetWindowHeight();
        mText = AddComponent<TextComponent>(windowWidth, windowHeight);
        mText->SetFont("assets/fonts/OCRAEXT.TTF", 30);
        mText->SetText("Score: " + std::to_string(mPlayerScore));
        mText->SetColor(Math::Vector3(1.0f));
        mText->SetScale(1.2f);
        mText->SetPosition(Math::Vector2( StaticCast<float>(windowWidth) / -2.0f + 50.0f, StaticCast<float>(windowHeight) / 2.0f) - 30.0f);
        
        mGameScene = Application::GetInstance()->FindScene<GameScene>();
    }

    void GameLevel::OnStart() {
        Shared<Entity> ball = mGameScene->FindEntity("Ball");
        mBall = ball->GetComponent<ECS::ScriptComponent>()->GetInstance<Ball>();

        Shared<Entity> powerManager = mGameScene->FindEntity("PowerManager");
        mPowerManager = powerManager->GetComponent<ECS::ScriptComponent>()->GetInstance<PowerManager>();

        Reset();
    }
    
    void GameLevel::OnWindowResized(const WindowResizedEvent& event) {
        for (uint32_t i = 0; i < mLevels.size(); i++) {
            for (const Shared<Brick>& brick : mLevels[i]) {
                uint32_t colCount = mLevelSize.at(i).first;
                uint32_t rowCount = mLevelSize.at(i).second;
                float unitWidth = StaticCast<float>(event.GetWidth()) / colCount;
                float unitHeight = StaticCast<float>(event.GetHeight()) * 0.5f / rowCount;
                brick->Place(event.GetWidth(), event.GetHeight(), unitWidth, unitHeight);
            }
        }
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
        float unitHeight = StaticCast<float>(levelHeight) * 0.5f / rowCount;
        mLevelSize[level] = {colCount, rowCount};
        mLevels[level].clear();
        for (uint16_t row = 0; row < rowCount; row++) {
            for (uint16_t col = 0; col < colCount; col++) {
                uint16_t idx = tiles[row][col];
                // Solid blocks
                if (tiles[row][col] == 1) {
                    Math::Vector4 color(0.8f, 0.8f, 0.7f, 1.0f);
                    Shared<Entity> solidBrick = MakeShared<Entity>();
                    solidBrick->GetComponent<InfoComponent>()->SetTag("Solid");
                    // Sound
                    solidBrick->AddComponent<SoundComponent>("assets/audio/solid.wav", false);
                    // Sprite
                    Shared<SpriteComponent> sprite = solidBrick->AddComponent<SpriteComponent>();
                    sprite->Init("assets/textures/block_solid.png", true, "SolidBlock");
                    sprite->SetColor(color);
                    // Box2D
                    solidBrick->AddComponent<Box2DComponent>()->SetBox(sprite->GetBox());
                    // Script
                    Shared<ScriptComponent> script = solidBrick->AddComponent<ScriptComponent>();
                    script->Bind<Brick>();
                    script->GetInstance<Brick>()->SetIsSolid(true);
                    script->GetInstance<Brick>()->SetCol(col);
                    script->GetInstance<Brick>()->SetRow(row);
                    script->GetInstance<Brick>()->Place(levelWidth, levelHeight, unitWidth, unitHeight);
                    mLevels[level].emplace_back(script->GetInstance<Brick>());
                }
                // Normal blocks
                else if (tiles[row][col] > 1) {
                    Math::Vector4 color(1.0f);
                    if (tiles[row][col] == 2) {
                        color = Math::Vector4(0.2f, 0.6f, 1.0f, 1.0f);
                    }
                    else if (tiles[row][col] == 3) {
                        color = Math::Vector4(0.0f, 1.0f, 0.0f, 1.0f);
                    }
                    else if (tiles[row][col] == 4) {
                        color = Math::Vector4(0.8f, 0.8f, 0.4f, 1.0f);
                    }
                    else if (tiles[row][col] == 5) {
                        color = Math::Vector4(1.0f, 0.5f, 0.0f, 1.0f);
                    }
                    Shared<Entity> normalBlock = MakeShared<Entity>();
                    // Sound
                    normalBlock->AddComponent<SoundComponent>("assets/audio/bleep.mp3", false);
                    // Sprite
                    Shared<SpriteComponent> sprite = normalBlock->AddComponent<SpriteComponent>();
                    sprite->Init("assets/textures/block.png", true, "SolidBlock");
                    sprite->SetColor(color);
                    // Box2D
                    normalBlock->AddComponent<Box2DComponent>()->SetBox(sprite->GetBox());
                    // Script
                    Shared<ScriptComponent> script = normalBlock->AddComponent<ScriptComponent>();
                    script->Bind<Brick>();
                    script->GetInstance<Brick>()->SetIsSolid(false);
                    script->GetInstance<Brick>()->SetCol(col);
                    script->GetInstance<Brick>()->SetRow(row);
                    script->GetInstance<Brick>()->Place(levelWidth, levelHeight, unitWidth, unitHeight);
                    mLevels[level].emplace_back(script->GetInstance<Brick>());
                }
            }
        }
    }

    bool GameLevel::IsCompleted() {
        for (Shared<Brick> brick : mLevels[mCurrentLevel]) {
            if (!brick->GetIsSolid() && brick->GetOwner()->GetIsActive()) {
                return false;
            }
        }
        return true;
    }

    void GameLevel::Reset(uint32_t level) {
        ChangeLevel(level);
        mBall->Reset();
        mPowerManager->Reset();
        SetPlayerScore(0);
    }

    void GameLevel::ChangeLevel(uint32_t level) {
        mCurrentLevel = Math::Abs(StaticCast<int32_t>(level % mLevels.size()));
        for(uint32_t i = 0; i < mLevels.size(); i++) {
            for (Shared<Brick> brick : mLevels[i]) {
                if (i == mCurrentLevel) {
                    brick->GetOwner()->SetActivate(true);
                }
                else {
                    brick->GetOwner()->SetActivate(false);
                }
            }
        }
    }

    void GameLevel::SetPlayerScore(uint32_t value) {
        mPlayerScore = value;
        mText->SetText("Score: " + std::to_string(mPlayerScore));
    }
} // namespace Waternion