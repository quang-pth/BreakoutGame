#include<Scene/GameScene.h>

namespace Client
{
    class MainScene : public Waternion::GameScene {
        public:
            MainScene();
            virtual void Load() override;
            // virtual void Render(float deltaTime) override;
    };
} // namespace Client