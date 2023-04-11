#pragma once

#include"Native.h"

#include"ECS/Component/Defaults.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/SpriteComponent.h"

namespace Waternion
{
    class Ball : public NativeScript {
        public:
            Ball();
            Ball(ECS::EntityID id);
            WATERNION_INLINE Ball(const Ball&) = default;
            virtual void OnAwake() override;
            virtual void OnStart() override;
            virtual void OnProcessInput(const InputState&) override;
            virtual void OnUpdate(float deltaTime) override;
            virtual void OnPostUpdate(float deltaTime) override;
            virtual void OnCollision(Shared<ECS::Entity> collidedEntity) override;
        private:
            bool mIsMoving;
            bool mIsStick;
            float mForwardSpeed;
            Shared<ECS::Entity> mPaddle;
            Shared<ECS::TransformComponent> mTransform;
            Shared<ECS::MoveComponent> mMove;
            Shared<ECS::SpriteComponent> mSprite;
    };
} // namespace Waternion