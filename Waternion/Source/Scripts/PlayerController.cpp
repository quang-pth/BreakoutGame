#include"PlayerController.h"
#include"ECS/System/InputSystem.h"
#include"ECS/Component/Defaults.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"Core/Application.h"

namespace Waternion
{
    using namespace ECS;

    PlayerController::PlayerController() : NativeScript(), mMaxSpeed(400.0f) {

    }

    PlayerController::PlayerController(EntityID id) : NativeScript(id), mMaxSpeed(400.0f) {

    }

    void PlayerController::OnAwake() {
        float windowWidth = Application::GetInstance()->GetWindowWidth();
        float windowHeight = Application::GetInstance()->GetWindowHeight();
        mTransform = GetComponent<TransformComponent>();
        mTransform->SetScale(0.16f, 0.1f, 1.0f);
        mTransform->SetPosition(-windowWidth / 8.0f, -windowHeight / 2.0f, 10.0f);

        mMoveComponent = AddComponent<MoveComponent>();
        mSprite = AddComponent<SpriteComponent>();
        mSprite->Init("assets/textures/paddle.png", true, "Paddle");;

        Shared<Box2DComponent> box = AddComponent<Box2DComponent>();
        box->SetBox(mSprite->GetBox());
    }
    
    void PlayerController::OnProcessInput(const InputState& inputState) {
        float strafeSpeed = 0.0f;
        if (inputState.Keyboard.GetKeyValue(GLFW_KEY_A)) {
            strafeSpeed -= mMaxSpeed;
        }
        if (inputState.Keyboard.GetKeyValue(GLFW_KEY_D)) {
            strafeSpeed += mMaxSpeed;
        }
        mMoveComponent->SetStrafeSpeed(strafeSpeed);
    }

    void PlayerController::OnPreUpdate(float deltaTime) {
    }

    void PlayerController::OnUpdate(float deltaTime) {
        this->ConstraintsInBounds();
    }

    void PlayerController::OnPostUpdate(float deltaTime) {

    }

    void PlayerController::ConstraintsInBounds() {
        bool inLeftBounds, inRightBounds;
        mMoveComponent->IsInBoundsX(inLeftBounds, inRightBounds);

        float windowWidth = Application::GetInstance()->GetWindowWidth();
        if (!inLeftBounds) {
            mTransform->SetPositionX(-windowWidth / 2.0f - mSprite->GetWidth() / 2.0f);
        }
        if (!inRightBounds) {
            mTransform->SetPositionX(windowWidth / 2.0f - mSprite->GetWidth() / 2.0f);
        }
    }
} // namespace Waternion