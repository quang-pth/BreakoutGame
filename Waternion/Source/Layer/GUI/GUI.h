#include"Layer/Layer.h"

class GLFWwindow;

namespace Waternion {
    class GUI : public Layer {
        public:
            GUI();
            virtual bool Init() override;
            virtual void Shutdown() override;
            virtual void Update(float deltaTime) override;
            virtual void Render() override;
            void Begin();
            void End();
            void SetWindow(GLFWwindow*);
        private:
            GLFWwindow* mWindow;
    };
} // namespace Waternion