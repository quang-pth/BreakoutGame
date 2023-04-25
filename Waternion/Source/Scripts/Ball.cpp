#include"Ball.h"
#include"ECS/System/InputSystem.h"
#include"Core/Application.h"
#include"ECS/Component/Physics/CircleComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Graphics/Particle2DComponent.h"

// States
#include"Scripts/States/MovingState.h"
#include"Scripts/States/StickState.h"

#include"Utils/Settings.h"

namespace Waternion
{
    using namespace ECS;

    const static float MAX_INTERVAL = 0.5f;

    Ball::Ball() : 
        NativeScript(), mState()
    {
    }

    Ball::Ball(EntityID id) : NativeScript(id), mState()
    {
        BallState::RegisterState<MovingState>(this);
        BallState::RegisterState<StickState>(this);
    }

    void Ball::OnAwake() {
        mPaddle = Application::GetInstance()->GetScene()->FindEntity("Paddle");
        mTransform = GetComponent<TransformComponent>();
        mTransform->SetScale(0.045f);
        mTransform->SetPositionZ(1.0f);
        
        mSprite = AddComponent<SpriteComponent>();
        mSprite->Init("assets/textures/awesomeface.png", true, "Ball");
        
        mMove = AddComponent<MoveComponent>();

        Shared<CircleComponent> circle = AddComponent<CircleComponent>();
        circle->SetRadius(mSprite->GetWidth() / 2.0f);

        Shared<Particle2DComponent> particle = AddComponent<Particle2DComponent>();
        particle->Init("assets/textures/particle.png", true, "Particle");
        particle->SetLifeTime(0.4f);
        particle->SetMaxParticle(300);
        particle->SetParticlePerFrame(2);

        mState = BallState::ChangeState<StickState>();
        mState->OnEnter();
    }

    void Ball::OnStart() {
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
            mTransform->SetPositionX(Application::GetInstance()->GetWindowWidth() / -2.0f - mSprite->GetWidth() / 2.0f);
        }

        if (!inRightBound) {
            mTransform->SetPositionX(Application::GetInstance()->GetWindowWidth() / 2.0f - mSprite->GetWidth() / 2.0f);
        }

        if (!inLeftBound || !inRightBound) {
            mMove->SetStrafeSpeed(mMove->GetStrafeSpeed() * -1.0f);
        }
    }
    
    void Ball::ConstraintsInBoundsY() {
        bool inLowerBound, inUpperBound;
        mMove->IsInBoundsY(inLowerBound, inUpperBound);
        
        if (!inUpperBound) {
            mTransform->SetPositionY(Application::GetInstance()->GetWindowHeight() / 2.0f - mSprite->GetHeight() / 2.0f);
            mMove->SetForwardSpeed(mMove->GetForwardSpeed() * -1.0f);
        }
    }
} // namespace Waternion