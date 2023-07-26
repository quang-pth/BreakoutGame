#pragma once

#include"pch.h"

namespace Waternion {
    class WATERNION_API Layer {
        public:
            virtual ~Layer() = default;
            virtual bool Init() = 0;
            virtual void Shutdown() = 0;
            virtual void Update(float deltaTime) = 0;
            virtual void Render() = 0;
        protected:
            Layer();
    };
}