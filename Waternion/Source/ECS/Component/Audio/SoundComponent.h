#pragma once

#include"ECS/Component/Defaults.h"

namespace Waternion
{
    struct SoundClip {
        std::string ClipPath;
        bool Looped;
    };

    namespace ECS {
        class SoundComponent : public Component {
            public:
                SoundComponent();
                SoundComponent(const std::string& clipPath, bool looped);
                void SetClip(const std::string& clipPath, bool looped);
                void Play();
            private:
                Shared<class AudioSystem> mAudioSystem;
                SoundClip mClip;
        };
    }
} // namespace Waternion
