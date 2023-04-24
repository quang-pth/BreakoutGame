#pragma once

#include"Native.h"

namespace Waternion
{
    class GameLevel : public NativeScript {
        public:
            GameLevel();
            GameLevel(ECS::EntityID id);
            virtual void OnStart() override;
            void LoadLevel(uint32_t level, const std::string& filepath, uint16_t levelWidth, uint16_t levelHeight);
            bool IsCompleted();
            void Reset();
            void ChangeLevel(uint32_t level);
            uint32_t GetCurrentLevel() {
                return mCurrentLevel;
            }
        private:
            void Init(uint32_t level, const std::vector<std::vector<uint16_t>>& tiles, uint16_t levelWidth, uint16_t levelHeight);
            std::vector<std::vector<Shared<ECS::Entity>>> mLevels;
            uint16_t mLevelWidth, mLevelHeight;
            uint32_t mCurrentLevel;
    };
} // namespace Waternion