#pragma once

#include"Scene.h"

namespace Waternion
{
    class WATERNION_API GameScene : public Scene {
        public:
            GameScene();
            virtual bool Init() override;
            virtual void Shutdown() override;
            virtual void Load() override;
            virtual void Awake() override;
            virtual void Start() override;
            virtual void ProcessInput(const InputState&) override;
            virtual void Update(float) override;
            virtual void BeginScene(float) override;
            virtual void Render(float) override;
            virtual void EndScene(float) override;
            WATERNION_INLINE const Shared<PostProcessor>& GetPostProcessor() {
                return mPostProcessor;
            }
        private:
            bool InitSystems();
        protected:
            std::vector<ECS::EntityID> mEntities;
            Shared<PostProcessor> mPostProcessor;
    };
} // namespace Waternion