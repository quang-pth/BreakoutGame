#include"Ball.h"
#include"ECS/System/InputSystem.h"
#include"Core/Application.h"
#include"Scene/SceneManager.h"
#include"Scene/GameScene.h"

// Components
#include"ECS/Component/Defaults.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Physics/CircleComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Graphics/Particle2DComponent.h"
#include"ECS/Component/UI/TextComponent.h"
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"ECS/Component/Audio/SoundComponent.h"

// States
#include"Scripts/States/MovingState.h"
#include"Scripts/States/StickState.h"
#include"Scripts/States/PassthroughState.h"

#include"Scripts/GameManager.h"

#include"Utils/Settings.h"

namespace Waternion
{
    using namespace ECS;

    const static float MAX_INTERVAL = 0.5f;

    Ball::Ball() : 
        NativeScript(), mState()
    {
    }

    Ball::Ball(EntityID id) : NativeScript(id), mState(), mLives(3)
    {
        BallState::RegisterState<MovingState>(this);
        BallState::RegisterState<StickState>(this);
        BallState::RegisterState<PassthroughState>(this);
    }

    void Ball::OnAwake() {
        mGameScene = Application::GetInstance()->FindScene<GameScene>(); 
        mPaddle = mGameScene->FindEntity("Paddle");
        mTransform = GetComponent<TransformComponent>();
        mTransform->SetScale(0.045f);
        mTransform->SetPositionZ(1.0f);
        
        mSprite = AddComponent<SpriteComponent>();
        mSprite->Init("assets/textures/awesomeface.png", true, "Ball");
        
        mMove = AddComponent<MoveComponent>();

        Shared<CircleComponent> circle = AddComponent<CircleComponent>();
        circle->SetRadius(mSprite->GetScaledWidth() / 2.0f);

        Shared<Particle2DComponent> particle = AddComponent<Particle2DComponent>();
        particle->SetLifeTime(1.2f);
        particle->SetMaxParticle(1000);
        particle->SetParticlePerFrame(5);
        particle->Init("assets/textures/particle.png", true, "Particle");

        uint32_t windowWidth = Application::GetInstance()->GetWindowWidth();
        uint32_t windowHeight = Application::GetInstance()->GetWindowHeight();
        mText = AddComponent<TextComponent>(windowWidth, windowHeight);
        mText->SetFont("assets/fonts/OCRAEXT.TTF", 30);
        mText->SetText("Lives: " + std::to_string(mLives));
        mText->SetColor(Math::Vector3(1.0f));
        mText->SetScale(0.7f);
        mText->SetPosition(Math::Vector2(StaticCast<float>(windowWidth) / -2.0f + 120.0f, StaticCast<float>(windowHeight) / 2.0f) - 70.0f);

        ChangeState<StickState>();
    }

    void Ball::OnStart() {
        Shared<Entity> gameManager = mGameScene->FindEntity("GameManager");
        mGameManager = gameManager->GetComponent<ScriptComponent>()->GetInstance<GameManager>();
        mState->OnStart();
    }

    void Ball::OnProcessInput(const InputState& inputState) {
        mState->OnProcessInput(inputState);
    }

    void Ball::OnPreUpdate(float deltaTime) {
        mState->OnPreUpdate(deltaTime);
    }

    void Ball::OnUpdate(float deltaTime) {
        mState->OnUpdate(deltaTime);
    }

    void Ball::OnPostUpdate(float deltaTime) {
        mState->OnPostUpdate(deltaTime);
    }

    void Ball::OnCollision(const ECS::CollisionDetails& details) {
        mState->OnCollision(details);
    }

    void Ball::ConstraintsInBoundsX() {
        bool inLeftBound, inRightBound;
        mMove->IsInBoundsX(inLeftBound, inRightBound);
        
        if (!inLeftBound) {
            mTransform->SetPositionX(Application::GetInstance()->GetWindowWidth() / -2.0f - mSprite->GetScaledWidth() / 2.0f);
        }

        if (!inRightBound) {
            mTransform->SetPositionX(Application::GetInstance()->GetWindowWidth() / 2.0f - mSprite->GetScaledWidth() / 2.0f);
        }

        if (!inLeftBound || !inRightBound) {
            mMove->SetStrafeSpeed(mMove->GetStrafeSpeed() * -1.0f);
        }
    }
    
    void Ball::ConstraintsInBoundsY() {
        bool inLowerBound, inUpperBound;
        mMove->IsInBoundsY(inLowerBound, inUpperBound);
        
        if (!inUpperBound) {
            mTransform->SetPositionY(Application::GetInstance()->GetWindowHeight() / 2.0f - mSprite->GetScaledHeight() / 2.0f);
            mMove->SetForwardSpeed(mMove->GetForwardSpeed() * -1.0f);
        }
    }

    void Ball::SetLives(uint32_t value) {
        mLives = value;
        mText->SetText("Lives: " + std::to_string(mLives));
    }

    void Ball::Reset() {
        ChangeState<StickState>();
        SetLives(3);
    }

    void Ball::ResolveCollidesWithPaddle(float speed) {
            Shared<ECS::TransformComponent> paddleTransform = mPaddle->GetComponent<ECS::TransformComponent>(); 
            Shared<ECS::SpriteComponent> paddleSprite = mPaddle->GetComponent<ECS::SpriteComponent>();
            float paddleCenterX = paddleTransform->GetPosition().x + paddleSprite->GetScaledWidth() / 2.0f;
            float distanceToCenter = GetComponent<ECS::CircleComponent>()->GetCenter().x - paddleCenterX;
            
            float percentage = distanceToCenter / (paddleSprite->GetScaledWidth() / 2.0f);
            float strength = 4.5f;

            const Math::Vector2& oldVelocity = mMove->GetVelocity();
            Math::Vector2 newVelocity(speed * strength * percentage, Math::Abs(oldVelocity.y) * 1.0f);
            newVelocity.SafeNormalized();

            mMove->SetStrafeSpeed(newVelocity.x * speed);
            mMove->SetForwardSpeed(Math::Clamp(newVelocity.y * speed, 100.0f, 300.0f));
            mPaddle->GetComponent<ECS::SoundComponent>()->Play();
    }

    void Ball::ResolveCollidesWithBricks(float speed, const ECS::CollisionDetails& details) {
        const Math::Vector2& bounceDirection = details.ClosestDirection;
        if (bounceDirection == Math::Vector2::UnitX) {
            mMove->SetStrafeSpeed(speed);
            mTransform->SetPositionX(mTransform->GetPosition().x + details.Penetration);
        }
        else if (bounceDirection == -Math::Vector2::UnitX) {
            mMove->SetStrafeSpeed(-speed);
            mTransform->SetPositionX(mTransform->GetPosition().x - details.Penetration);
        }
        else if (bounceDirection == Math::Vector2::UnitY) {
            mMove->SetForwardSpeed(speed);
            mTransform->SetPositionY(mTransform->GetPosition().y + details.Penetration);
        }
        else if (bounceDirection == -Math::Vector2::UnitY) {
            mMove->SetForwardSpeed(-speed);
            mTransform->SetPositionY(mTransform->GetPosition().y - details.Penetration);
        }
    }

    void Ball::RestoreState() {
        mState->OnExit();
        mState = BallState::RestoreState();
        mState->OnContinue();
    }
} // namespace Waternion