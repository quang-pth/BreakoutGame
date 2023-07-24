#include"PlayerController.h"
#include"Core/Application.h"
#include"ECS/System/InputSystem.h"

// Components
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Audio/SoundComponent.h"
#include"ECS/Component/Behavior/ScriptComponent.h"

#include"Core/Event/Event.h"
#include"Scripts/GameManager.h"
#include"Scene/GameScene.h"

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

        AddComponent<SoundComponent>("assets/audio/bleep.wav", false);
    }

    void PlayerController::OnStart() {
        Shared<Entity> gameManager = Application::GetInstance()->FindScene<GameScene>()->FindEntity("GameManager");
        mGameManager = gameManager->GetComponent<ScriptComponent>()->GetInstance<GameManager>();
    }

    void PlayerController::OnProcessInput(const InputState& inputState) {
        if (mGameManager->GetGameState() != EGameState::Playing) {
            return;
        }

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

    void PlayerController::OnWindowResized(const WindowResizedEvent& event) {
        mTransform->SetPosition(event.GetWidth() / -8.0f, event.GetHeight() / -2.0f, 10.0f);
    }

    void PlayerController::ConstraintsInBounds() {
        bool inLeftBounds, inRightBounds;
        mMoveComponent->IsInBoundsX(inLeftBounds, inRightBounds);

        float windowWidth = Application::GetInstance()->GetWindowWidth();
        if (!inLeftBounds) {
            mTransform->SetPositionX(-windowWidth / 2.0f - mSprite->GetScaledWidth() / 2.0f);
        }
        if (!inRightBounds) {
            mTransform->SetPositionX(windowWidth / 2.0f - mSprite->GetScaledWidth() / 2.0f);
        }
    }
} // namespace Waternion