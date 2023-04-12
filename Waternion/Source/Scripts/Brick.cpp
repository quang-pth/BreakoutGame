#include"Brick.h"
#include"Core/Application.h"

namespace Waternion
{
    using namespace ECS;

    Brick::Brick() : NativeScript() {

    }

    Brick::Brick(EntityID id) : NativeScript(id) {

    }

    void Brick::OnCollision(const ECS::CollisionDetails& details) {
        Shared<Entity> ball = Application::GetInstance()->GetScene()->GetEntity("Ball");

        if (details.Collider->GetID() == ball->GetID()) {
            if (!mIsSolid) {
                GetOwner()->Destroy();
            }
        }
    }
} // namespace Waternion