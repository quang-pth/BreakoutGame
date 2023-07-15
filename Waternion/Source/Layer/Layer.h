#pragma once

namespace Waternion {
    class Layer {
        public:
            Layer();
            virtual ~Layer() = default;
            virtual bool Init() { return true; };
            virtual void Shutdown() {};
            virtual void Update(float deltaTime) {};
            virtual void Render() {};
    };
}