#pragma once

namespace Waternion
{
    class Settings {
        public:
            static const char* DefaultVertexSource;
            static const char* DefaultFragmentSource;
            static const char* DefaultShaderName;
            static const char* ParticleVertexSource;
            static const char* ParticleFragmentSource;
            static const char* ParticleShaderName;
            static const char* PostProcessingVertexSource;
            static const char* PostProcessingFragmentSource;
            static const char* PostProcessingShaderName;
        private:
            Settings() = default;
    };
} // namespace Waternion