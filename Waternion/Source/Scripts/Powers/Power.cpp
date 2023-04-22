#include"Power.h"
#include"Core/Application.h"
#include"Render/PostProcessor.h"

#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"

#include"Collisions/Collision.h"

namespace Waternion
{
    void Chaos::SetEffect(bool value) {
        Application::GetInstance()->GetScene()->GetPostProcessor()->SetChaos(value);
    }

    void Confuse::SetEffect(bool value) {
        Application::GetInstance()->GetScene()->GetPostProcessor()->SetConfuse(value);        
    }

    void Increase::SetEffect(bool value) {

    }

    void Passthrough::SetEffect(bool value) {

    }

    void Speedy::SetEffect(bool value) {

    }

    void Sticky::SetEffect(bool value) {

    }

    PowerUp::PowerUp() : NativeScript()
    {
    }

    PowerUp::PowerUp(ECS::EntityID id) : NativeScript(id), mStart(false)
    {
    }

    void PowerUp::OnAwake() {
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

        mPaddle = Application::GetInstance()->GetScene()->FindEntity("Paddle");
        GetOwner()->SetActivate(false);
    }

    void PowerUp::OnUpdate(float deltaTime) {
        this->CheckCollisions();
        
        if (mStart) {
            mPower->Duration -= deltaTime;
            if (mPower->Duration <= 0.0f) {
                mPower->SetEffect(false);
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

    void PowerUp::CheckCollisions() {
        Shared<ECS::Box2DComponent> paddleBox = mPaddle->GetComponent<ECS::Box2DComponent>();
        if (Collisions::IsIntersect(paddleBox->GetBox(), mBox->GetBox())) {
            mPower->SetEffect(true);
            GetOwner()->GetComponent<ECS::SpriteComponent>()->SetIsVisible(false);
            mStart = true;
        }
    }
} // namespace Waternion