#include<Scene/GameScene.h>

namespace Client
{
    class MainScene : public Waternion::GameScene {
        public:
            MainScene();
            virtual void Load() override;
    };
} // namespace Client