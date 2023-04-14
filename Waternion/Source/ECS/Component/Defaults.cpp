#include"Defaults.h"
#include"ECS/Coordinator.h"
#include"Core/Application.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Physics/CircleComponent.h"

namespace Waternion::ECS
{
    Component::Component() : mID(GenerateUUID()), mDisabled(false) {
        mCoordinator = Application::GetInstance()->GetCoordinator();
    }

    TransformComponent::TransformComponent() : 
        Component(), mPosition(Math::Vector3::Zero), mScale(Math::Vector3(1.0f)), 
        mRotation(0.0f), mRecomputeTransform(true) 
    {
    }

    void TransformComponent::UpdateWorldTransform() {
        if (mRecomputeTransform) {
            mRecomputeTransform = false;
            mWorldTransform = Math::Matrix4::CreateFromScale(mScale);
            mWorldTransform *= Math::Matrix4::CreateFromRotationZ(mRotation);
            mWorldTransform *= Math::Matrix4::CreateFromTranslation(mPosition);

            if (GetOwner()->HasComponent<CircleComponent>()) {
                GetOwner()->GetComponent<CircleComponent>()->OnUpdateWorldTransform();
            }
            if (GetOwner()->HasComponent<Box2DComponent>()) {
                GetOwner()->GetComponent<Box2DComponent>()->OnUpdateWorldTransform();
            }
        }
    }
} // namespace Waternion::ECS