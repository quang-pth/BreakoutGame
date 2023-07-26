#include<Core/Application.h>

namespace Client {
    class SandboxApplication : public Waternion::Application {
        public:
            SandboxApplication();
            virtual bool Init(int width, int height, const std::string& title) override;
    };
}