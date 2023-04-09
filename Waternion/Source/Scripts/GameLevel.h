#pragma once

#include"Native.h"

namespace Waternion
{
    class GameLevel : public NativeScript {
        public:
            GameLevel();
            GameLevel(ECS::EntityID id);
            virtual void OnStart() override;
            void LoadLevel(const std::string& filepath, uint16_t levelWidth, uint16_t levelHeight);
            bool IsCompleted();
        private:
            void Init(const std::vector<std::vector<uint16_t>>& tiles, uint16_t levelWidth, uint16_t levelHeight);
            std::vector<Shared<ECS::Entity>> mBricks;
            std::string mFilepath;
            uint16_t mLevelWidth, mLevelHeight;
    };
} // namespace Waternion