#pragma once

#include"Editor.h"

namespace Waternion::Editor
{
    class DemoSpace : public Editor {
        public:
            DemoSpace();
            virtual void OnRender() override;
    };
} // namespace Waternion::Editor