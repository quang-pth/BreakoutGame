#include"PostProcessor.h"

#include"Shader.h"
#include"Framebuffer.h"
#include"VertexArray.h"

#include"Core/Application.h"

#include"Window/Window.h"
#include"Core/Event/EventDispatcher.h"

namespace Waternion
{
    const static float MAX_SHAKE_TIME = 0.05f;

    PostProcessor::PostProcessor() : mChaos(false), mConfuse(false), mShake(false), mShakeTime(MAX_SHAKE_TIME) {
    }

    bool PostProcessor::Init(Shared<Shader> shader, uint32_t width, uint32_t height) {
        mShader = shader;
        mFramebuffer = MakeShared<Framebuffer>();
        if (!mFramebuffer->Init(width, height)) {
            return false;
        }
        this->InitRenderData();

        Window::sEventDispatcher->RegisterCallback<WindowResizedEvent>([&](const WindowResizedEvent& event) {
            mFramebuffer->Clear();
            if (mFramebuffer->Init(event.GetWidth(), event.GetHeight())) {
                return false;
            }
            WATERNION_LOG_ERROR("Failed to resize framebuffer");
            return true;
        });

        return true;
    }

    void PostProcessor::Update(float deltaTime) {
        if (mShake) {
            mShakeTime -= deltaTime;
            if (mShakeTime <= 0.0f) {
                mShake = false;
                mShakeTime = MAX_SHAKE_TIME;
            }
        }
    }

    void PostProcessor::BeginRender() {
        mFramebuffer->Bind();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void PostProcessor::Render(float deltaTime) {
        mShader->Use();
        mShader->SetFloat("time", GetDeltaTime());
        mShader->SetBool("chaos", mChaos);
        mShader->SetBool("confuse", mConfuse);
        mShader->SetBool("shake", mShake);
        mVertexArray->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void PostProcessor::EndRender() {
        mFramebuffer->Unbind();
    }

    void PostProcessor::InitRenderData() {
        float vertices[] = {
            // Position       // Texcoords
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
              
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f
        };
        int32_t numOfVertices = sizeof(vertices) / sizeof(float);
        mVertexArray = MakeShared<VertexArray>(vertices, numOfVertices);
        // Set shader uniforms
        mShader->Use();
        mShader->SetInt("scene", 0);
        float offset = 1.0f / 300.0f;
        float offsets[9][2] = {
            { -offset,  offset  },  // top-left
            {  0.0f,    offset  },  // top-center
            {  offset,  offset  },  // top-right
            { -offset,  0.0f    },  // center-left
            {  0.0f,    0.0f    },  // center-center
            {  offset,  0.0f    },  // center - right
            { -offset, -offset  },  // bottom-left
            {  0.0f,   -offset  },  // bottom-center
            {  offset, -offset  }   // bottom-right    
        };
        mShader->SetFloats2("offsets", &offsets[0][0], 9);
        int edgeKernel[9] = {
            -1, -1, -1,
            -1,  8, -1,
            -1, -1, -1
        };
        mShader->SetInts("edgeKernel", edgeKernel, sizeof(edgeKernel) / sizeof(int));
        float blurKernel[9] = {
            1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
            2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
            1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
        };
        mShader->SetFloats("blurKernel", blurKernel, sizeof(blurKernel) / sizeof(float));
    }
} // namespace Waternion