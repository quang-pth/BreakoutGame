#include"MoveComponent.h"
#include"Core/Application.h"
#include"ECS/Component/Graphics/SpriteComponent.h"

namespace Waternion::ECS {
    MoveComponent::MoveComponent() : 
        Component(), mStrafeSpeed(0.0f), mForwardSpeed(0.0f)
    {

    }

    void MoveComponent::Update(float deltaTime) {
        Shared<TransformComponent> transform = GetOwner()->GetComponent<TransformComponent>();
        Math::Vector3 position = transform->GetPosition();
        position += mForwardSpeed * Math::Vector3::UnitY * deltaTime;
        position += mStrafeSpeed * Math::Vector3::UnitX * deltaTime;

        transform->SetPosition(position);
    }

    Math::Vector2 MoveComponent::GetVelocity() const {
        return mForwardSpeed * Math::Vector2::UnitY + mStrafeSpeed * Math::Vector2::UnitX;
    }

    void MoveComponent::IsInBoundsX(bool& inLeftBound, bool& inRightBound) {
        Shared<SpriteComponent> sprite = GetOwner()->GetComponent<SpriteComponent>();
        Shared<TransformComponent> transform = GetOwner()->GetComponent<TransformComponent>();
        float windowWidth = Application::GetInstance()->GetWindowWidth();
        inLeftBound = transform->GetPosition().x > -windowWidth / 2.0f - sprite->GetWidth() / 2.0f;
        inRightBound = transform->GetPosition().x < windowWidth / 2.0f - sprite->GetWidth() / 2.0f;
    }
    
    void MoveComponent::IsInBoundsY(bool& inLowerBound, bool& inUpperBound) {
        Shared<SpriteComponent> sprite = GetOwner()->GetComponent<SpriteComponent>();
        Shared<TransformComponent> transform = GetOwner()->GetComponent<TransformComponent>();
        float windowHeight = Application::GetInstance()->GetWindowHeight();
        inLowerBound = transform->GetPosition().y > -windowHeight / 2.0f - 20.0f;
        inUpperBound = transform->GetPosition().y < windowHeight / 2.0f - sprite->GetHeight() / 2.0f;
    }
}