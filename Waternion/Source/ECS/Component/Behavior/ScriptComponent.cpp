#include"ScriptComponent.h"

namespace Waternion::ECS
{
    ScriptComponent::ScriptComponent() : Component() {
        mInstance.reset();
    }

    void ScriptComponent::OnStart() {
        mInstance->OnStart();
    }

    void ScriptComponent::OnProcessInput(const struct InputState& inputState) {
        mInstance->OnProcessInput(inputState);
    }

    void ScriptComponent::OnPreUpdate(float deltaTime) {
        mInstance->OnPreUpdate(deltaTime);
    }

    void ScriptComponent::OnUpdate(float deltaTime) {
        mInstance->OnUpdate(deltaTime);
    }

    void ScriptComponent::OnPostUpdate(float deltaTime) {
        mInstance->OnPostUpdate(deltaTime);
    }

    void ScriptComponent::OnCollision(Shared<ECS::Entity> collidedEntity) {
        mInstance->OnCollision(collidedEntity);
    }

    void ScriptComponent::OnDestroy() {
        mInstance->OnDestroy();
    }
} // namespace Waternion::ECS