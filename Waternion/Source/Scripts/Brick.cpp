#include"Brick.h"
#include"Core/Application.h"
#include"Core/Event/Event.h"
#include"Render/PostProcessor.h"
#include"Scene/SceneManager.h"
#include"Scene/GameScene.h"

// Components 
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Audio/SoundComponent.h"

#include"Scripts/Powers/PowerManager.h"
#include"Scripts/GameLevel.h"

namespace Waternion
{
    using namespace ECS;

    Brick::Brick() : NativeScript() {
        
    }

    Brick::Brick(EntityID id) : NativeScript(id) {
    }

    void Brick::OnAwake() {
        mGameScene = Application::GetInstance()->FindScene<GameScene>();
    }

    void Brick::OnActivate() {
        Shared<Entity> powerManager = mGameScene->FindEntity("PowerManager");
        mPowerManager = powerManager->GetComponent<ScriptComponent>()->GetInstance<PowerManager>();
        Shared<Entity> gameLevel = mGameScene->FindEntity("GameLevel");
        mGameLevel = gameLevel->GetComponent<ScriptComponent>()->GetInstance<GameLevel>();
    }

    void Brick::OnCollision(const ECS::CollisionDetails& details) {
        Shared<Entity> ball = mGameScene->FindEntity("Ball");

        if (details.Collider->GetID() == ball->GetID()) {
            GetOwner()->GetComponent<SoundComponent>()->Play();
            if (!mIsSolid) {
                this->SpawnPowerUpWithProbability(0.25);
                GetOwner()->SetActivate(false);
                mGameLevel->SetPlayerScore(mGameLevel->GetPlayerScore() + 1);
            }
            else {
                mGameScene->GetPostProcessor()->SetShake(true);
            }
        }
    }

    void Brick::SpawnPowerUpWithProbability(float probability) {
        double value = (double) rand() / RAND_MAX;
        if (value < probability) {
            mPowerManager->SpawnRandomPower(GetOwner()->GetComponent<TransformComponent>());
        }
    }

    void Brick::Place(float width, float height, float unitWidth, float unitHeight) {
        Shared<TransformComponent> transform = GetOwner()->GetComponent<TransformComponent>(); 
        Shared<SpriteComponent> sprite = GetOwner()->GetComponent<SpriteComponent>();
        transform->SetPosition(-width / 2.0f + unitWidth * mCol, height / 2.0f - unitHeight * mRow, 0.0f);
        transform->SetScale(unitWidth / sprite->GetTextureWidth(), unitHeight / sprite->GetTextureHeight(), 1.0f);
    }
} // namespace Waternion