#include"AudioSystem.h"

namespace Waternion
{
    namespace ECS {
        AudioSystem::AudioSystem() : System(), mSoundEngine() {
            
        }

        bool AudioSystem::Init() {
            mSoundEngine.reset(irrklang::createIrrKlangDevice());
            
            if (mSoundEngine == nullptr) {
                WATERNION_LOG_ERROR("AudioSystem is intialized failed!");
                return false;
            }

            WATERNION_LOG_INFO("AudioSystem is intialized sucessfully!");
            return true;
        }

        void AudioSystem::Shutdown() {
            mSoundEngine->drop();
            WATERNION_LOG_ERROR("AudioSystem is closed!");
        }

        void AudioSystem::PlaySound2D(const char* filepath, bool looped) {
            mSoundEngine->play2D(filepath, looped);
        }
    } // namespace ECS
} // namespace Waternion