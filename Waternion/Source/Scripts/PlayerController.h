#pragma once

#include"Native.h"

namespace Waternion
{
    namespace ECS {
        class TransformComponent;
        class MoveComponent;
        class SpriteComponent;
    }

    class GameManager;

    class PlayerController : public NativeScript {
        public:
            PlayerController();
            PlayerController(ECS::EntityID id);
            
            virtual void OnAwake() override;
            virtual void OnStart() override;
            virtual void OnProcessInput(const struct InputState&) override;
            virtual void OnPreUpdate(float deltaTime) override;
            virtual void OnUpdate(float deltaTime) override;
            virtual void OnPostUpdate(float deltaTime) override;
            virtual void OnWindowResized(const WindowResizedEvent& event) override;
            WATERNION_INLINE void SetMaxSpeed(float speed) {
                mMaxSpeed = speed;
            }
            WATERNION_INLINE float GetMaxSpeed() const {
                return mMaxSpeed;
            }
        private:
            void ConstraintsInBounds();
            float mMaxSpeed;
            Shared<ECS::MoveComponent> mMoveComponent;
            Shared<ECS::TransformComponent> mTransform;
            Shared<ECS::SpriteComponent> mSprite;
            Shared<GameManager> mGameManager;
    };
} // namespace Waternion