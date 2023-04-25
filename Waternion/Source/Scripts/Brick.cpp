#include"Brick.h"
#include"Core/Application.h"
#include"Render/PostProcessor.h"

// Components 
#include"ECS/Component/Behavior/ScriptComponent.h"
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

    void Brick::OnActivate() {
        Shared<Entity> powerManager = Application::GetInstance()->GetScene()->FindEntity("PowerManager");
        mPowerManager = powerManager->GetComponent<ScriptComponent>()->GetInstance<PowerManager>();
        Shared<Entity> gameLevel = Application::GetInstance()->GetScene()->FindEntity("GameLevel");
        mGameLevel = gameLevel->GetComponent<ScriptComponent>()->GetInstance<GameLevel>();
    }

    void Brick::OnCollision(const ECS::CollisionDetails& details) {
        Shared<Entity> ball = Application::GetInstance()->GetScene()->FindEntity("Ball");

        if (details.Collider->GetID() == ball->GetID()) {
            GetOwner()->GetComponent<SoundComponent>()->Play();
            if (!mIsSolid) {
                this->SpawnPowerUpWithProbability(0.25);
                GetOwner()->SetActivate(false);
                mGameLevel->SetPlayerScore(mGameLevel->GetPlayerScore() + 1);
            }
            else {
                Application::GetInstance()->GetScene()->GetPostProcessor()->SetShake(true);
            }
        }
    }

    void Brick::SpawnPowerUpWithProbability(float probability) {
        double value = (double) rand() / RAND_MAX;
        if (value < probability) {
            mPowerManager->SpawnRandomPower(GetOwner()->GetComponent<TransformComponent>());
        }
    }
} // namespace Waternion