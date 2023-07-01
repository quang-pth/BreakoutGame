#include"EventDispatcher.h"

namespace Waternion
{
    EventDispatcher::EventDispatcher() : mCallbacks() {

    }

    EventDispatcher::~EventDispatcher() {
        mCallbacks.clear();
    }
} // namespace Waternion