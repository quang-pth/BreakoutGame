#include"ScriptComponent.h"
#include"ECS/System/InputSystem.h"

namespace Waternion::ECS
{
    ScriptComponent::ScriptComponent() : Component() {
        mInstance.reset();
    }

    void ScriptComponent::OnAwake() {
        mInstance->OnAwake();
    }

    void ScriptComponent::OnStart() {
        mInstance->OnStart();
    }

    void ScriptComponent::OnProcessInput(const InputState& inputState) {
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