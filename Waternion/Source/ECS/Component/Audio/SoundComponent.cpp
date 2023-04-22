#include"SoundComponent.h"

#include"Core/Application.h"
#include"ECS/System/AudioSystem.h"

namespace Waternion
{
    namespace ECS {
        SoundComponent::SoundComponent() : Component(), mClip() {
            mAudioSystem = Application::GetInstance()->GetScene()->GetSystem<AudioSystem>();
        }

        SoundComponent::SoundComponent(const std::string& clipPath, bool looped) : 
            Component(), mClip()
        {
            mClip.ClipPath = clipPath;
            mClip.Looped = looped;
            mAudioSystem = Application::GetInstance()->GetScene()->GetSystem<AudioSystem>();
        }

        void SoundComponent::SetClip(const std::string& clipPath, bool looped) {
            mClip.ClipPath = clipPath;
            mClip.Looped = looped;
        }

        void SoundComponent::Play() {
            mAudioSystem->PlaySound2D(mClip.ClipPath.c_str(), mClip.Looped);
        }
    } // namespace ECS
} // namespace Waternion