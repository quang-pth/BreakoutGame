#pragma once

#include"Native.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/SpriteComponent.h"

namespace Waternion
{
    class PlayerController : public NativeScript {
        public:
            PlayerController();
            PlayerController(ECS::EntityID id);
            
            virtual void OnAwake() override;
            virtual void OnProcessInput(const struct InputState&) override;
            virtual void OnPreUpdate(float deltaTime) override;
            virtual void OnUpdate(float deltaTime) override;
            virtual void OnPostUpdate(float deltaTime) override;
            WATERNION_INLINE void SetMaxSpeed(float speed) {
                mMaxSpeed = speed;
            }
        private:
            void ConstraintsInBounds();
            float mMaxSpeed;
            Shared<ECS::MoveComponent> mMoveComponent;
            Shared<ECS::TransformComponent> mTransform;
            Shared<ECS::SpriteComponent> mSprite;
    };
} // namespace Waternion