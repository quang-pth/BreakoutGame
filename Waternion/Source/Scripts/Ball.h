#pragma once

#include"Native.h"

namespace Waternion
{
    namespace ECS {
        class TransformComponent;
        class TextComponent;
        class MoveComponent;
        class SpriteComponent;
    };
    
    class GameManager;

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
            void SetLives(uint32_t value);
            WATERNION_INLINE uint32_t GetLives() const {
                return mLives;
            }
            void Reset();
        private:
            void ConstraintsInBoundsX();
            void ConstraintsInBoundsY();
            Shared<ECS::Entity> mPaddle;
            Shared<ECS::TransformComponent> mTransform;
            Shared<ECS::MoveComponent> mMove;
            Shared<ECS::SpriteComponent> mSprite;
            Shared<ECS::TextComponent> mText;
            Shared<class BallState> mState;
            Shared<GameManager> mGameManager;
            uint32_t mLives;
    };
} // namespace Waternion