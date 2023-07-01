#pragma once

#include"pch.h"

namespace Waternion
{
    template<typename T> using CallbackFunction = std::function<bool(const T&)>;

    class WindowEvent;

    class EventCallbackBase {
        public:
            virtual ~EventCallbackBase() = default;
            virtual bool OnTrigger(Shared<class WindowEvent>) = 0;
    };

    template<typename T>
    class EventCallback : public EventCallbackBase {
        public:
            EventCallback(const CallbackFunction<T>& callback) : mCallback(callback) {}
            virtual ~EventCallback() = default;
            virtual bool OnTrigger(Shared<class WindowEvent> event) override {
                return mCallback(*(StaticPtrCast<T>(event).get()));
            }
        private:
            CallbackFunction<T> mCallback;
    };
} // namespace Waternion