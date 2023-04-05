#pragma once

#include"pch.h"

namespace Waternion::ECS
{
    using EntityID = size_t;
    using ComponentID = uint32_t;
    using Signature = std::set<ComponentID>;
    using EntityIDList =  std::set<EntityID>;
} // namespace Waternion::ECS