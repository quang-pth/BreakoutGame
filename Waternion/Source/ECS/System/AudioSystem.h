#pragma once

#include"ECS/System.h"

namespace Waternion
{
    namespace ECS {
        class AudioSystem : public System {
            public:
                AudioSystem();
                virtual bool Init() override;
                virtual void Shutdown() override;
                void PlaySound2D(const char* filepath, bool looped);
            private:
                Unique<irrklang::ISoundEngine> mSoundEngine;
        };
    }
} // namespace Waternion