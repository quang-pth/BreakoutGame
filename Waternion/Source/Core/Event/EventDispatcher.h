#pragma once

#include"pch.h"

#include"Event.h"
#include"EventCallback.h"

namespace Waternion
{
    using CallbackFunctions = std::vector<Shared<EventCallbackBase>>;

    using EventID = UUID;

    class EventDispatcher {
        public: 
            EventDispatcher();
            ~EventDispatcher();
            
            template<typename T>
            void RegisterCallback(const CallbackFunction<T>& callback) {
                WATERNION_STATIC_ASSERT(std::is_base_of<WindowEvent, T>::value);
                Shared<EventCallback<T>> eventCallback = MakeShared<EventCallback<T>>(callback);
                mCallbacks[GetTypeID<T>()].emplace_back(eventCallback);
            }

            template<typename T, typename... Args>
            void Dispatch(Args&&... args) {
                WATERNION_STATIC_ASSERT(std::is_base_of<WindowEvent, T>::value);
                WATERNION_ASSERT(mCallbacks.count(GetTypeID<T>()) && "Event does not exist");
                Shared<T> event = MakeShared<T>(std::forward<Args>(args)...);
                for (Shared<EventCallbackBase> eventCallback : mCallbacks.at(GetTypeID<T>())) {
                    if (!eventCallback->OnTrigger(event)) {
                        break;
                    }
                }         
            }
        private:
            std::unordered_map<EventID, CallbackFunctions> mCallbacks;
    };
}