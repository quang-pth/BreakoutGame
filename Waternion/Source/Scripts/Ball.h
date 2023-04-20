#pragma once

#include"Native.h"

#include"ECS/Component/Defaults.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/Graphics/SpriteComponent.h"

namespace Waternion
{
    class Ball : public NativeScript {
            friend class BallState;
            friend class MovingState;
            friend class StickState;
        public:
            Ball();
            Ball(ECS::EntityID id);
            WATERNION_INLINE Ball(const Ball&) = default;
            virtual void OnAwake() override;
            virtual void OnStart() override;
            virtual void OnProcessInput(const InputState&) override;
            virtual void OnPreUpdate(float deltaTime) override;
            virtual void OnUpdate(float deltaTime) override;
            virtual void OnPostUpdate(float deltaTime) override;
            virtual void OnCollision(const ECS::CollisionDetails& details) override;
        private:
            void ConstraintsInBoundsX();
            void ConstraintsInBoundsY();
            Shared<ECS::Entity> mPaddle;
            Shared<ECS::TransformComponent> mTransform;
            Shared<ECS::MoveComponent> mMove;
            Shared<ECS::SpriteComponent> mSprite;
            Shared<class BallState> mState;
    };
} // namespace Waternion