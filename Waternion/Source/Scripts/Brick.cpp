#include"Brick.h"
#include"Core/Application.h"
#include"Render/PostProcessor.h"
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"Scripts/Powers/PowerManager.h"

namespace Waternion
{
    using namespace ECS;

    Brick::Brick() : NativeScript() {

    }

    Brick::Brick(EntityID id) : NativeScript(id) {

    }

    void Brick::OnStart() {
        Shared<Entity> powerManager = Application::GetInstance()->GetScene()->FindEntity("PowerManager");
        WATERNION_ASSERT(powerManager != nullptr && "PowerManager does not exist");
        mPowerManager = powerManager->GetComponent<ScriptComponent>()->GetInstance<PowerManager>();
    } 

    void Brick::OnCollision(const ECS::CollisionDetails& details) {
        Shared<Entity> ball = Application::GetInstance()->GetScene()->FindEntity("Ball");

        if (details.Collider->GetID() == ball->GetID()) {
            if (!mIsSolid) {
                this->SpawnPowerUpWithProbability(0.5);
                GetOwner()->Destroy();
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