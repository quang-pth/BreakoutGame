#include"Defaults.h"
#include"ECS/Coordinator.h"
#include"Core/Application.h"

namespace Waternion::ECS
{
    Component::Component() : mID(GenerateUUID()) {
        mCoordinator = Application::GetInstance()->GetCoordinator();
    }

    TransformComponent::TransformComponent() : 
        Component(), mPosition(Math::Vector3::Zero), mScale(Math::Vector3(1.0f)), 
        mRotation(0.0f), mRecomputeTransform(true) 
    {
        this->UpdateWorldTransform();
    }

    void TransformComponent::UpdateWorldTransform() {
        if (mRecomputeTransform) {
            mRecomputeTransform = false;
            mWorldTransform = Math::Matrix4::CreateFromScale(mScale);
            mWorldTransform *= Math::Matrix4::CreateFromRotationZ(mRotation);
            mWorldTransform *= Math::Matrix4::CreateFromTranslation(mPosition);
        }
    }
} // namespace Waternion::ECS