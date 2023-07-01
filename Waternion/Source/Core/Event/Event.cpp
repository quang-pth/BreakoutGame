#include"Event.h"

namespace Waternion
{
    WindowResizedEvent::WindowResizedEvent(int32_t width, int32_t height) : mWidth(width), mHeight(height) {

    }

    KeyPressedEvent::KeyPressedEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) 
        : mKey(key), mScancode(scancode), mAction(action), mMode(mode)
    {

    }
} // namespace Waternion