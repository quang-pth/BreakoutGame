#pragma once

#include"pch.h"
#include"Core.h"

namespace Waternion {
    namespace ECS {
        class Coordinator {
            public:
                WATERNION_INLINE Coordinator() : mComponentArrayMap(), mSignatureMap(), mNextEntID(INVALID_ID) {}

                WATERNION_INLINE void Clear() {
                    mComponentArrayMap.clear();
                    mSignatureMap.clear();
                    mNextEntID = INVALID_ID;
                }

                WATERNION_INLINE EntityID AddEntity() {
                    EntityID newEntID = ++mNextEntID;
                    mSignatureMap[newEntID] = Signature();
                    mActiveEntities[newEntID] = true;
                    return newEntID;                   
                }

                WATERNION_INLINE bool DeleteEntity(EntityID entID) {
                    for (auto& pair : mComponentArrayMap) {
                        if (!pair.second->Erase(entID)) {
                            return false;
                        }
                    }
                    mSignatureMap.erase(entID);
                    mActiveEntities.erase(entID);
                    return true;
                }
                
                WATERNION_INLINE bool EntityIsAlive(EntityID entID) {
                    return mSignatureMap.count(entID) > 0;
                }

                template<typename T>
                WATERNION_INLINE EntityIDList GetEntityIDsHaveComponent() {
                    EntityIDList ids;
                    for(const std::pair<EntityID, Signature>& pair : mSignatureMap) {
                        if (pair.second.count(GetTypeID<T>()) > 0) {
                            ids.insert(pair.first);
                            continue;
                        }
                    }
                    return ids;
                }

                template<typename T>
                WATERNION_INLINE Shared<T> GetComponent(EntityID entID) {
                    WATERNION_ASSERT(mSignatureMap.count(entID) && "Failed to Get Component of non-existing entity");
                    return this->GetComponentArray<T>()->GetComponent(entID);
                }

                template<typename T, typename... Args>
                WATERNION_INLINE Shared<T> AddComponent(EntityID entID, Args&&... args) {
                    WATERNION_ASSERT(mSignatureMap.count(entID) && "Failed to Add Component to non-existing entity");
                    ComponentID componentID = GetTypeID<T>();
                    mSignatureMap.at(entID).insert(componentID);
                    Shared<T> component = MakeShared<T>(std::forward<Args>(args)...);
                    this->GetComponentArray<T>()->Add(entID, component);
                    return component;
                }

                template<typename T>
                WATERNION_INLINE bool RemoveComponent(EntityID entID) {
                    WATERNION_ASSERT(mSignatureMap.count(entID) && "Failed to Remove Component of non-existing entity");
                    ComponentID componentID = GetTypeID<T>();
                    mSignatureMap.at(entID).erase(componentID);
                    return this->GetComponentArray<T>()->Erase(entID);
                }

                template<typename T>
                WATERNION_INLINE bool HasComponent(EntityID entID) {
                    WATERNION_ASSERT(mSignatureMap.count(entID) && "Failed to Check Component of non-existing entity");
                    return mSignatureMap.at(entID).count(GetTypeID<T>()) != 0;
                }

                template<typename T>
                WATERNION_INLINE Shared<ComponentArray<T>> GetComponentArray() {
                    if (mComponentArrayMap.count(GetTypeID<T>()) == 0) {
                        this->AddComponentArray<T>();
                    }
                    return StaticPtrCast<ComponentArray<T>>(mComponentArrayMap.at(GetTypeID<T>()));                       
                }

                template<typename T>
                WATERNION_INLINE EntityID GetEntityID(UUID componentID) {
                    if (mComponentArrayMap.count(GetTypeID<T>()) == 0) {
                        return INVALID_ID;
                    }
                    return StaticPtrCast<ComponentArray<T>>(mComponentArrayMap.at(GetTypeID<T>()))->GetEntityID(componentID);                       
                }

                WATERNION_INLINE bool GetActivate(EntityID id) const {
                    WATERNION_ASSERT(mSignatureMap.count(id) && "Failed to Get Activate of non-existing entity");
                    return mActiveEntities.at(id);
                }

                void SetActivate(EntityID id);               
                void SetDeactivate(EntityID id);               
            private:
                template<typename T> 
                WATERNION_INLINE void AddComponentArray() {
                    ComponentID componentID = GetTypeID<T>();
                    mComponentArrayMap.insert({componentID, std::make_shared<ComponentArray<T>>()});
                }
            private:
                std::unordered_map<ComponentID, Shared<ComponentArrayBase>> mComponentArrayMap;
                std::unordered_map<EntityID, Signature> mSignatureMap;
                std::unordered_map<EntityID, bool> mActiveEntities;
                EntityID mNextEntID;
        };
    }
}