#pragma once

#include"ECS/System.h"

namespace Waternion::ECS
{
    class ScriptingSystem : public System {
        public:
            ScriptingSystem();
            virtual bool Init() override;
            virtual void Awake() override;
            virtual void Start() override;
            virtual void PreUpdate(float deltaTime) override;
            virtual void Update(float deltaTime) override;
            virtual void PostUpdate(float deltaTime) override;
  };
} // namespace Waternion::ECS