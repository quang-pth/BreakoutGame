#include"Power.h"

#include"Core/Application.h"
#include"Render/PostProcessor.h"
#include"Scene/GameScene.h"

// Components
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Audio/SoundComponent.h"

// Scripts
#include"Scripts/Ball.h"
#include"Scripts/States/PassthroughState.h"
#include"Scripts/Powers/PowerManager.h"
#include"Scripts/PlayerController.h"

#include"Collisions/Collision.h"

namespace Waternion
{
    void Chaos::SetActive() {
        Application::GetInstance()->FindScene<GameScene>()->GetPostProcessor()->SetChaos(true);
    }

    void Chaos::SetDeactive() {
        Application::GetInstance()->FindScene<GameScene>()->GetPostProcessor()->SetChaos(false);
    }

    void Confuse::SetActive() {
        Application::GetInstance()->FindScene<GameScene>()->GetPostProcessor()->SetConfuse(true);        
    }

    void Confuse::SetDeactive() {
        Application::GetInstance()->FindScene<GameScene>()->GetPostProcessor()->SetConfuse(false);        
    }

    void Increase::SetActive() {
        Shared<ECS::Entity> paddle = Application::GetInstance()->FindScene<GameScene>()->FindEntity("Paddle");
        Shared<ECS::TransformComponent> transform = paddle->GetComponent<ECS::TransformComponent>();
        transform->SetScale(transform->GetScale().x * 3.0f, transform->GetScale().y, transform->GetScale().z);
        paddle->GetComponent<ECS::SpriteComponent>()->SetColor(Math::Vector4(1.0f, 0.6f, 0.4f));
    }

    void Increase::SetDeactive() {
        Shared<ECS::Entity> paddle = Application::GetInstance()->FindScene<GameScene>()->FindEntity("Paddle");
        Shared<ECS::TransformComponent> transform = paddle->GetComponent<ECS::TransformComponent>();
        transform->SetScale(transform->GetScale().x / 3.0f, transform->GetScale().y, transform->GetScale().z);
        paddle->GetComponent<ECS::SpriteComponent>()->SetColor(Math::Vector4(1.0f));
    }

    void Passthrough::SetActive() {
        Shared<ECS::Entity> ball = Application::GetInstance()->FindScene<GameScene>()->FindEntity("Ball");
        Shared<Ball> script = ball->GetComponent<ECS::ScriptComponent>()->GetInstance<Ball>();
        script->ChangeState<PassthroughState>();
    }

    void Passthrough::SetDeactive() {
        Shared<ECS::Entity> ball = Application::GetInstance()->FindScene<GameScene>()->FindEntity("Ball");
        Shared<Ball> script = ball->GetComponent<ECS::ScriptComponent>()->GetInstance<Ball>();
        script->RestoreState();
    }

    void Speedy::SetActive() {
        Shared<ECS::Entity> paddle = Application::GetInstance()->FindScene<GameScene>()->FindEntity("Paddle");
        Shared<PlayerController> playerController = paddle->GetComponent<ECS::ScriptComponent>()->GetInstance<PlayerController>();
        playerController->SetMaxSpeed(playerController->GetMaxSpeed() * 1.3f);
        paddle->GetComponent<ECS::SpriteComponent>()->SetColor(Math::Vector4(.5f, 0.5f, 1.0f));
    }

    void Speedy::SetDeactive() {
        Shared<ECS::Entity> paddle = Application::GetInstance()->FindScene<GameScene>()->FindEntity("Paddle");
        Shared<PlayerController> playerController = paddle->GetComponent<ECS::ScriptComponent>()->GetInstance<PlayerController>();
        playerController->SetMaxSpeed(playerController->GetMaxSpeed() / 1.3f);
        paddle->GetComponent<ECS::SpriteComponent>()->SetColor(Math::Vector4(1.0f));
    }

    void Sticky::SetActive() {
        Shared<ECS::Entity> paddle = Application::GetInstance()->FindScene<GameScene>()->FindEntity("Paddle");
        paddle->GetComponent<ECS::InfoComponent>()->SetTag("Stickable");
        paddle->GetComponent<ECS::SpriteComponent>()->SetColor(Math::Vector4(1.0f, 0.5f, 1.0f));
    }

    void Sticky::SetDeactive() {
        Shared<ECS::Entity> paddle = Application::GetInstance()->FindScene<GameScene>()->FindEntity("Paddle");
        paddle->GetComponent<ECS::InfoComponent>()->SetTag("None");
        paddle->GetComponent<ECS::SpriteComponent>()->SetColor(Math::Vector4(1.0f));
    }

    PowerUp::PowerUp() : NativeScript()
    {
    }

    PowerUp::PowerUp(ECS::EntityID id) : NativeScript(id), mStart(false)
    {
    }

    void PowerUp::OnAwake() {
        mGameScene = Application::GetInstance()->FindScene<GameScene>();
    }

    void PowerUp::OnStart() {
        Shared<ECS::InfoComponent> info = GetComponent<ECS::InfoComponent>();
        info->SetTag("Ignore");

        Shared<ECS::TransformComponent> transform = GetComponent<ECS::TransformComponent>();
        transform->SetScale(0.15f, 0.15f, 1.0f);

        Shared<ECS::SpriteComponent> sprite = AddComponent<ECS::SpriteComponent>();
        sprite->Init(mPower->SpritePath.c_str(), true, mPower->SpritePath.c_str());
        sprite->SetColor(mPower->Color);

        mBox = AddComponent<ECS::Box2DComponent>();
        mBox->SetBox(sprite->GetBox());

        mMove = AddComponent<ECS::MoveComponent>();
        mMove->SetForwardSpeed(-140.0f);

        mPaddle = mGameScene->FindEntity("Paddle");
        
        mSound = AddComponent<ECS::SoundComponent>("assets/audio/powerup.wav", false);
        
        Shared<ECS::Entity> powerManager = mGameScene->FindEntity("PowerManager");
        mPowerManager = powerManager->GetComponent<ECS::ScriptComponent>()->GetInstance<PowerManager>();

        GetOwner()->SetActivate(false);
    }

    void PowerUp::OnUpdate(float deltaTime) {
        this->CheckCollisions();
        
        if (mStart) {
            mPower->Duration -= deltaTime;
            if (mPower->Duration <= 0.0f) {
                GetOwner()->SetActivate(false);
            }
        }
        else {
            bool inLowerBoundY, inUpperBoundY;
            mMove->IsInBoundsY(inLowerBoundY, inUpperBoundY);
            if (!inLowerBoundY) {
                GetOwner()->SetActivate(false);
            }
        }
    }

    void PowerUp::OnActivate() {
        mPower->Duration = 8.0f;
        mStart = false;
    }

    void PowerUp::OnDeactivate() {
        if (mStart) {
            mPowerManager->DeactivatePower(mPower);
            mStart = false;
        }
    }

    void PowerUp::CheckCollisions() {
        Shared<ECS::Box2DComponent> paddleBox = mPaddle->GetComponent<ECS::Box2DComponent>();
        if (Collisions::IsIntersect(paddleBox->GetBox(), mBox->GetBox())) {
            mSound->Play();
            if (mPowerManager->ActivatePower(mPower)) {
                mStart = true;
            }
            GetOwner()->GetComponent<ECS::SpriteComponent>()->SetIsVisible(false);
        }
    }
} // namespace Waternion