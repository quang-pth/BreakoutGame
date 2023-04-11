#include"MoveComponent.h"
#include"Core/Application.h"
#include"ECS/Component/SpriteComponent.h"

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
        
        if (this->IsInBoundsX(position) && this->IsInBoundsY(position)) {
            transform->SetPosition(position);
        }
        else {
            Bounce();
        }
    }

    bool MoveComponent::IsInBoundsX(const Math::Vector3& position) {
        Shared<SpriteComponent> sprite = GetOwner()->GetComponent<SpriteComponent>();
        float windowWidth = Application::GetInstance()->GetWindowWidth();
        return position.x >= -windowWidth / 2.0f - sprite->GetWidth() / 2.0f && position.x <= windowWidth / 2.0f - sprite->GetWidth() / 2.0f;
    }
    
    bool MoveComponent::IsInBoundsY(const Math::Vector3& position) {
        Shared<SpriteComponent> sprite = GetOwner()->GetComponent<SpriteComponent>();
        float windowHeight = Application::GetInstance()->GetWindowHeight();
        return position.y >= -windowHeight / 2.0f && position.y <= windowHeight / 2.0f - sprite->GetHeight();
    }

    void MoveComponent::Bounce() {

    }
}