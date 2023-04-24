#include"Coordinator.h"

namespace Waternion
{
    namespace ECS {
        void Coordinator::SetActivate(EntityID id) {
            WATERNION_ASSERT(mSignatureMap.count(id) && "Activate non-existing entity");
            mEnabledEntities[id] = true;
            Signature signature = mSignatureMap.at(id);
            for (ComponentID componentID : signature) {
                mComponentArrayMap.at(componentID)->Activate(id);
            }
        }

        void Coordinator::SetDeactivate(EntityID id) {
            WATERNION_ASSERT(mSignatureMap.count(id) && "Deactivate non-existing entity");
            mEnabledEntities.erase(id);
            Signature signature = mSignatureMap.at(id);
            for (ComponentID componentID : signature) {
                mComponentArrayMap.at(componentID)->Deactivate(id);
            }
        }
    } // namespace ECS
} // namespace Waternion::ECS