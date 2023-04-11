#pragma once

#include"Native.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/SpriteComponent.h"

namespace Waternion
{
    class PlayerController : public NativeScript {
        public:
            WATERNION_INLINE PlayerController() : NativeScript() {}
            WATERNION_INLINE PlayerController(ECS::EntityID id) : NativeScript(id) {}
            
            virtual void OnAwake() override;
            virtual void OnProcessInput(const struct InputState&) override;
            virtual void OnPreUpdate(float deltaTime) override;
            virtual void OnUpdate(float deltaTime) override;
            virtual void OnPostUpdate(float deltaTime) override;
        private:
            float mMaxSpeed = 230.0f;
            Shared<ECS::MoveComponent> mMoveComponent;
            Shared<ECS::TransformComponent> mTransform;
            Shared<ECS::SpriteComponent> mSprite;
    };
} // namespace Waternion