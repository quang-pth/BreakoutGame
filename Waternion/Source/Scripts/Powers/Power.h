#pragma once

#include"Scripts/Native.h"

namespace Waternion
{
    struct Power {
        std::string SpritePath;
        Math::Vector3 Color;
        float Duration;
        Power(const char* spritePath, const Math::Vector3& color, float duration = 5.0f) {
            SpritePath = spritePath;
            Color = color;
            Duration = duration;
        }
        virtual ~Power() = default;
        WATERNION_INLINE virtual void SetEffect(bool value) {};
    };

    struct Chaos : public Power {
        Chaos(const char* spritePath, const Math::Vector3& color) : Power(spritePath, color) {   
        }
        virtual void SetEffect(bool value) override;
    };

    struct Confuse : public Power {
        Confuse(const char* spritePath, const Math::Vector3& color) : Power(spritePath, color) {
            
        }
        virtual void SetEffect(bool value) override;
    };

    struct Increase : public Power {
        Increase(const char* spritePath, const Math::Vector3& color) : Power(spritePath, color) {
            
        }
        virtual void SetEffect(bool value) override;
    };

    struct Passthrough : public Power {
        Passthrough(const char* spritePath, const Math::Vector3& color) : Power(spritePath, color) {
            
        }
        virtual void SetEffect(bool value) override;
    };

    struct Speedy : public Power {
        Speedy(const char* spritePath, const Math::Vector3& color) : Power(spritePath, color) {
            
        }
        virtual void SetEffect(bool value) override;
    };

    struct Sticky : public Power {
        Sticky(const char* spritePath, const Math::Vector3& color) : Power(spritePath, color) {
            
        }
        virtual void SetEffect(bool value) override;
    };

    class ECS::MoveComponent;
    class ECS::Box2DComponent;

    class PowerUp : public NativeScript {
        public:
            PowerUp();
            PowerUp(ECS::EntityID id);
            virtual void OnAwake() override;
            virtual void OnStart() override;
            virtual void OnUpdate(float deltaTime) override;
            virtual void OnActivate() override;
            template<typename T, typename... Args>
            WATERNION_INLINE void SetPower(Args&&... args) {
                WATERNION_STATIC_ASSERT(std::is_base_of<Power, T>::value);
                mPower = MakeShared<T>(std::forward<Args>(args)...);
            }
            WATERNION_INLINE Shared<Power> GetPower() const {
                return mPower;
            }
        private:
            void CheckCollisions();
            Shared<Power> mPower;
            Shared<ECS::MoveComponent> mMove;
            Shared<ECS::Box2DComponent> mBox;
            Shared<ECS::Entity> mPaddle;
            bool mStart;
    };
} // namespace Waternion