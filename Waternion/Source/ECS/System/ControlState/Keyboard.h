#pragma once

#include"pch.h"

namespace Waternion {
    namespace ECS
    {
        const static uint16_t NUM_KEYS = 1025;

        enum class ButtonState {
            ENone,
            EHeld,
            EPressed,
            EReleased
        };

        struct KeyboardState {
            bool PreviousState[NUM_KEYS];
            bool CurrentState[NUM_KEYS];
            WATERNION_INLINE int32_t GetKeyValue(int32_t key) const {
                return CurrentState[key];
            }
            WATERNION_INLINE ButtonState GetKeyState(int32_t key) const {
                if (CurrentState[key]) {
                    if (PreviousState[key]) {
                        return ButtonState::EHeld;
                    }
                    else {
                        return ButtonState::EPressed;
                    }
                }
                else {
                    if (PreviousState[key]) {
                        return ButtonState::EReleased;
                    }
                    else {
                        return ButtonState::ENone;
                    }
                }
            }
        };

        struct InputState {
            KeyboardState Keyboard;
            WATERNION_INLINE InputState() {
                memset(Keyboard.CurrentState, false, NUM_KEYS);
                memset(Keyboard.PreviousState, false, NUM_KEYS);
            }
        };
    } // namespace ECS
}