#include"AnimatorComponent.h"

#include"ECS/Component/Graphics/SpriteComponent.h"

namespace Waternion
{
    namespace ECS {
        Animation::Animation(const std::string& name, 
            const std::vector<Sprite*>& sprites, bool isLoop)
            : Name(name), AnimationSprites(sprites), IsLoop(isLoop), AnimationFPS(24.0f)
        {

        }

        Animation::~Animation()
        {
        }

        bool Animation::IsFinished(float currentFrame)
        {
            return !IsLoop && AnimationSprites.size() - 1 == currentFrame;
        }

        AnimatorComponent::AnimatorComponent() :
            SpriteComponent(), 
            mCurrentFrame(0), 
            mAnimationsMap(), mCurrentAnimation()
        {

        }

        AnimatorComponent::~AnimatorComponent()
        {
        }

        void AnimatorComponent::OnUpdate(float deltaTime)
        {
            mCurrentAnimation = mAnimationsMap[mAnimationName];
            const std::vector<Sprite*> animationSprites = mCurrentAnimation->AnimationSprites;
            const int animationFrames = animationSprites.size();
            
            if (animationFrames < 0) return;

            mCurrentFrame += mCurrentAnimation->AnimationFPS * deltaTime;

            while (mCurrentFrame >= animationFrames) {
                mCurrentFrame -= animationFrames;
                
                if (!mCurrentAnimation->IsLoop) {
                    mCurrentFrame = animationSprites.size() - 1;
                }
            }

            SpriteComponent::SetSprite(animationSprites[static_cast<int>(mCurrentFrame)]);
        }

        void AnimatorComponent::SetAnimation(const std::string& animationName)
        {
            if (animationName == mAnimationName) return;
            
            if (mAnimationsMap.find(animationName) == mAnimationsMap.end()) {
                std::cout << "No animation name found" << std::endl;
                return;
            }

            ResetAnimation(animationName);
        }

        void AnimatorComponent::AddAnimation(Shared<Animation> animation)
        {
            mAnimationsMap.insert({animation->Name, animation});
            ResetAnimation(animation->Name);
        }

        void AnimatorComponent::ResetAnimation(std::string animationName)
        {
            mAnimationName = animationName;
            mCurrentFrame = 0;
        }

        bool AnimatorComponent::IsFinishedAnimation()
        {
            return mCurrentAnimation->IsFinished(mCurrentFrame);
        }
    }
} // namespace Waternion