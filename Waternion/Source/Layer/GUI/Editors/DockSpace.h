#pragma once

#include"Editor.h"

namespace Waternion::Editor {
    class DockSpace : public Editor {
        public:
            DockSpace();
            virtual void OnUpdate(float deltaTime) override;
            virtual void OnRender() override;
            virtual void AddEditor(Editor* editor) override;
            virtual void RemoveEditor(Editor* editor) override;
        private:
            void BeginDocking();
            void EndDocking();
            void RenderEditors();
        private:
            bool mOptionFullscreen;
            bool mOptionPadding;
            std::vector<Shared<Editor>> mEditors;
    };
}