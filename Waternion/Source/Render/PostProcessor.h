#pragma once

#include"pch.h"

namespace Waternion {
    class PostProcessor {
        public:
            PostProcessor();
            bool Init(Shared<class Shader> shader, uint32_t width, uint32_t height);
            void Update(float deltaTime);
            void BeginRender();
            void Render(float deltaTime);
            void EndRender();
            WATERNION_INLINE void SetShake(bool value) {
                mShake = value;
            } 
            WATERNION_INLINE void SetChaos(bool value) {
                mChaos = value;
            } 
            WATERNION_INLINE void SetConfuse(bool value) {
                mConfuse = value;
            }
            const Shared<class Framebuffer> GetFramebuffer() {
                return mFramebuffer;
            }
        private:
            void InitRenderData();
            Shared<class Shader> mShader;
            Shared<class Framebuffer> mFramebuffer;
            Shared<class VertexArray> mVertexArray;
            bool mChaos, mConfuse, mShake;
            float mShakeTime;
    };
}