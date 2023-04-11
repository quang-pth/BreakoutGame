#pragma once

#include"ECS/System.h"

namespace Waternion::ECS
{
    class PhysicWorld : public System {
        public:
            PhysicWorld();
            virtual void Start() override;
            virtual void PreUpdate(float deltaTime) override;
            virtual void Update(float deltaTime) override;
            virtual void PostUpdate(float deltaTime) override;
        private:
            std::vector<Shared<class CircleComponent>> mCircles;
            std::vector<Shared<class Box2DComponent>> mBoxes;
    };
} // namespace ECS