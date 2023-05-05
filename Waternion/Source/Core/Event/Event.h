#pragma once

#include"pch.h"

namespace Waternion
{
    class WindowEvent {
        public:
            virtual ~WindowEvent() = default;
    };

    class WindowResizedEvent : public WindowEvent {
        public:
            WindowResizedEvent() = default;
            WindowResizedEvent(int32_t width, int32_t height);
            WATERNION_INLINE void SetWidth(int32_t width) { mWidth = width; }
            WATERNION_INLINE void SetHeight(int32_t height) { mHeight = height; }
            WATERNION_INLINE int32_t GetWidth() const { return mWidth; }
            WATERNION_INLINE int32_t GetHeight() const { return mHeight; }
        private:
            int32_t mWidth;
            int32_t mHeight;
    };

    class KeyPressedEvent : public WindowEvent {
        public:
            KeyPressedEvent() = default;
            KeyPressedEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
            WATERNION_INLINE int32_t GetKey() const { return mKey; }
            WATERNION_INLINE int32_t GetScancode() const { return mScancode; }
            WATERNION_INLINE int32_t GetAction() const { return mAction; }
            WATERNION_INLINE int32_t GetMode() const { return mMode; }
        private:
            int32_t mKey, mScancode, mAction, mMode;  
    };
} // namespace Waternion