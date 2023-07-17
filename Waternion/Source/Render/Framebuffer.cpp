#include"Framebuffer.h"

#include"Window/Window.h"
#include"Core/Event/EventDispatcher.h"

namespace Waternion
{
    Framebuffer::Framebuffer() {
        Window::sEventDispatcher->RegisterCallback<WindowResizedEvent>([&](const WindowResizedEvent& event) {
            if (mID) {
                glDeleteFramebuffers(1, &mID);
            }
            if (mRenderBuffer) {
                glDeleteRenderbuffers(1, &mRenderBuffer);
            }
            if (mTexture) {
                mTexture->Delete();
            }
            if (Init(event.GetWidth(), event.GetHeight())) {
                return true;
            }
            WATERNION_LOG_INFO("Failed to resize framebuffer");
            return false;
        });
    }

    Framebuffer::~Framebuffer() {
        this->Clear();
    }

    bool Framebuffer::Init(uint32_t width, uint32_t height) {
        glGenFramebuffers(1, &mID);
        glBindFramebuffer(GL_FRAMEBUFFER, mID);
        // Attach color buffer
        mTexture = MakeUnique<Texture2D>();
        mTexture->Init(width, height, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture->ID, 0);
        // Attach render buffer
        glGenRenderbuffers(1, &mRenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, mRenderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderBuffer);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            WATERNION_LOG_ERROR("Framebuffer is not complete!");
            return false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return true;
    }

    void Framebuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, mID);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Framebuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        mTexture->Bind();
    }

    void Framebuffer::Clear() {
        glDeleteFramebuffers(1, &mID);
        glDeleteRenderbuffers(1, &mRenderBuffer);
        mTexture->Delete();
    }
} // namespace Waternion