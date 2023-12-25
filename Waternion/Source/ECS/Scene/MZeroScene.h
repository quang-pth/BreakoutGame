#pragma once
#include"Scene.h"

namespace Waternion
{
    namespace ECS {
        class MZeroScene : public ECS::Scene {
            public:
                MZeroScene();
                ~MZeroScene() = default;
                
                virtual bool Load();
        };
    }
} // namespace Waternion