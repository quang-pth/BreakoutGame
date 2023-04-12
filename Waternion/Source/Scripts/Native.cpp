#include"Native.h"
#include"Core/Application.h"
#include"ECS/System/InputSystem.h"

namespace Waternion
{
    NativeScript::NativeScript() : mEntityID(INVALID_ID), mCoordinator() {

    }

    NativeScript::NativeScript(ECS::EntityID id) : mEntityID(id) {
        mCoordinator = Application::GetInstance()->GetCoordinator();
        WATERNION_ASSERT(mCoordinator != nullptr && "Reference Coordinator as nullptr");
    }
    
    void NativeScript::OnAwake() {

    }

    void NativeScript::OnStart() {

    }

    void NativeScript::OnProcessInput(const InputState& inputState) {

    }

    void NativeScript::OnPreUpdate(float deltaTime) {
        
    }

    void NativeScript::OnUpdate(float deltaTime) {

    }

    void NativeScript::OnPostUpdate(float deltaTime) {

    }

    void NativeScript::OnCollision(const ECS::CollisionDetails& details) {

    }

    void NativeScript::OnDestroy() {

    }
} // namespace Waternion