#include"Native.h"
#include"Core/Application.h"
#include"ECS/System/InputSystem.h"

#include"Core/Event/Event.h"

namespace Waternion
{
    NativeScript::NativeScript() : mEntityID(INVALID_ID), mCoordinator() {
        mCoordinator = Application::GetInstance()->GetCoordinator();
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

    void NativeScript::OnActivate() {

    }

    void NativeScript::OnDeactivate() {

    }

    void NativeScript::OnWindowResized(const WindowResizedEvent& event) {

    }
} // namespace Waternion