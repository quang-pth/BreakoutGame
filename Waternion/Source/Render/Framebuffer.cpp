#include"Framebuffer.h"
#include"Texture.h"

namespace Waternion
{
    Framebuffer::Framebuffer() {

    }

    Framebuffer::~Framebuffer() {
        glDeleteFramebuffers(1, &mID);
        glDeleteRenderbuffers(1, &mRenderBuffer);
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
} // namespace Waternion