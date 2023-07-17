#pragma once

#include"Editor.h"

namespace Waternion::Editor
{
    class DebugConsole : public Editor {
        public:
            DebugConsole();
            virtual void OnRender() override;
    };
} // namespace Waternion::Editor