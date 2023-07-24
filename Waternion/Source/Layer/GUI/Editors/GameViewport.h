#pragma once

#include"pch.h"
#include"Editor.h"

struct ImVec2;

namespace Waternion {
    class GameScene;
}

namespace Waternion::Editor {
    class GameViewport : public Editor {
        public:
            GameViewport();
            virtual void OnUpdate(float deltaTime) override;
            virtual void OnRender() override;
        private:
            ImVec2 CalculateViewportSize();
            ImVec2 CalculateViewportCenterPosition(const ImVec2& viewportSize);
            Shared<class GameScene> mGameScene;
    };
}