#pragma once

#include"Native.h"

namespace Waternion
{
    namespace ECS {
        class TextComponent;
    };

    class Brick;

    class WATERNION_API GameLevel : public NativeScript {
        public:
            GameLevel();
            GameLevel(ECS::EntityID id);
            virtual void OnAwake() override;
            virtual void OnStart() override;
            virtual void OnWindowResized(const class WindowResizedEvent&) override;
            void LoadLevel(uint32_t level, const std::string& filepath, uint16_t levelWidth, uint16_t levelHeight);
            bool IsCompleted();
            void Reset(uint32_t level = 0);
            WATERNION_INLINE uint32_t GetCurrentLevel() {
                return mCurrentLevel;
            }
            WATERNION_INLINE uint32_t GetPlayerScore() const {
                return mPlayerScore;
            }
            void SetPlayerScore(uint32_t value);
        private:
            void ChangeLevel(uint32_t level);
            void Init(uint32_t level, const std::vector<std::vector<uint16_t>>& tiles, uint16_t levelWidth, uint16_t levelHeight);
            std::vector<std::vector<Shared<Brick>>> mLevels;
            std::unordered_map<uint32_t, std::pair<uint32_t, uint32_t>> mLevelSize;
            uint16_t mLevelWidth, mLevelHeight;
            uint32_t mCurrentLevel;
            uint32_t mPlayerScore;
            Shared<ECS::TextComponent> mText;
            Shared<class Ball> mBall;
            Shared<class PowerManager> mPowerManager;
            Shared<class GameScene> mGameScene;
    };
} // namespace Waternion