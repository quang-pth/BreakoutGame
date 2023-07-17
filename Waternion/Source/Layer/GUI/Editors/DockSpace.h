#pragma once

#include"Editor.h"

namespace Waternion::Editor {
    class DockSpace : public Editor {
        public:
            DockSpace();
            virtual void OnUpdate(float deltaTime) override;
            virtual void OnRender() override;
        private:
            template<typename T, typename... Args>
            void PushEditor(Args&&... args) {
                WATERNION_STATIC_ASSERT(std::is_base_of<Editor, T>::value);
                mEditors.emplace_back(MakeUnique<T>(std::forward<Args>(args)...));
            }
            
            template<typename T>
            void RemoveEditor() {
                WATERNION_STATIC_ASSERT(std::is_base_of<Editor, T>::value);
                auto iter = std::find_if(mEditors.begin(), mEditors.end(), [&](const Unique<Editor::Editor>& editor) {
                    if (DyanmicPtrCast<T>(editor)) {
                        return true;
                    }
                    return false;
                });
                if (iter != nullptr) {
                    mEditors.erase(iter);
                }
            }
        private:
            bool mOptionFullscreen;
            bool mOptionPadding;
            std::vector<Unique<Editor>> mEditors;
    };
}