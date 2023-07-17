#include"Layer/Layer.h"

namespace Waternion {
    namespace Editor {
        class Editor;
    };

    class GUI : public Layer {
        public:
            GUI();
            virtual bool Init() override;
            virtual void Shutdown() override;
            virtual void Update(float deltaTime) override;
            virtual void Render() override;
            void Begin();
            void End();
        private:
            Unique<Editor::Editor> mEditor;
    };
} // namespace Waternion