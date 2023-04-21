#include"Settings.h"

namespace Waternion
{
    const char* Settings::DefaultVertexSource = "assets/shaders/sprite_vs.glsl";
    const char* Settings::DefaultFragmentSource = "assets/shaders/sprite_fs.glsl";
    const char* Settings::DefaultShaderName = "DefaultShader";
    
    const char* Settings::ParticleVertexSource = "assets/shaders/particle_vs.glsl";
    const char* Settings::ParticleFragmentSource = "assets/shaders/particle_fs.glsl";
    const char* Settings::ParticleShaderName = "ParticleShader";

    const char* Settings::PostProcessingVertexSource = "assets/shaders/post_processing_vs.glsl";
    const char* Settings::PostProcessingFragmentSource = "assets/shaders/post_processing_fs.glsl";
    const char* Settings::PostProcessingShaderName = "PostProcessingShader";
} // namespace Waternion