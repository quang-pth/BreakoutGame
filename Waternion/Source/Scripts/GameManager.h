#pragma once

#include"Native.h"

namespace Waternion
{
    enum class EGameState {
        Paused,
        Playing,
        Won,
        Lose
    };

    namespace ECS {
        class TextComponent;
    };

    class WATERNION_API GameManager : public NativeScript {
        public:
            GameManager() = default;
            GameManager(ECS::EntityID id);
            virtual void OnAwake() override;
            virtual void OnStart() override;
            virtual void OnProcessInput(const struct InputState&) override;
            virtual void OnUpdate(float deltaTime) override;
            WATERNION_INLINE EGameState GetGameState() const {
                return mGameState;
            }
            WATERNION_INLINE void SetGameState(EGameState state) {
                mGameState = state;
            }
        private:
            EGameState mGameState;
            Shared<class GameLevel> mGameLevel;
            Shared<ECS::TextComponent> mText;
            Shared<class GameScene> mGameScene;
    };
} // namespace Waternion