#pragma once

#include"pch.h"
#include"ECS/Component/Graphics/SpriteComponent.h"

namespace Waternion
{
    namespace ECS {
        struct Animation
        {
            bool IsLoop;
            std::vector<Sprite*> AnimationSprites;
            std::string Name;
            float AnimationFPS;

            Animation(const std::string& name, const std::vector<Sprite*>& sprites, bool isLoop = true);
            ~Animation();
            bool IsFinished(float currentFrame);
        };

        class AnimatorComponent : public SpriteComponent
        {
        public:
            AnimatorComponent();
            ~AnimatorComponent();
            void OnUpdate(float deltaTime) override;
            void SetAnimation(const std::string& animationName);
            void AddAnimation(Shared<class Animation> animation);
            void ResetAnimation(std::string animationName);
            bool IsFinishedAnimation();
        private:
            std::unordered_map <std::string, Shared<class Animation>> mAnimationsMap;
            Shared<class Animation> mCurrentAnimation;
            std::string mAnimationName;
            float mCurrentFrame;
        };
    }
} // namespace Waternion