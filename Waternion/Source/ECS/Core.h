#pragma once

#include"pch.h"

namespace Waternion {
    namespace ECS {
        using EntityID = size_t;
        using ComponentID = uint32_t;
        using Signature = std::set<ComponentID>;
        using EntityIDList =  std::set<EntityID>;
        
        class ComponentEntryBase {
            public:
                WATERNION_INLINE virtual ~ComponentEntryBase() = default;
                virtual operator EntityID() const = 0;                
                virtual EntityID GetEntityID() const = 0;       
        };

        template<typename T>
        class ComponentEntry : public ComponentEntryBase {
            public:
                WATERNION_INLINE ComponentEntry(EntityID entID, Shared<T> component) 
                    : mEntityID(entID), mComponent(component) {}
                WATERNION_INLINE virtual operator EntityID() const override { return mEntityID; }                
                WATERNION_INLINE virtual EntityID GetEntityID() const override { return mEntityID; }       
                WATERNION_INLINE Shared<T> GetComponent() { return mComponent; }         
            private:
                EntityID mEntityID;
                Shared<T> mComponent;
        };

        class ComponentArrayBase {
            public:
                WATERNION_INLINE virtual ~ComponentArrayBase() = default;
                virtual bool Erase(EntityID) = 0;
        };

        template<typename T>
        class ComponentArray : public ComponentArrayBase {
            public: 
                WATERNION_INLINE ComponentArray() : mComponentEntries() {}

                WATERNION_INLINE Shared<T> Add(EntityID entID, Shared<T> component) {
                    if (this->IsExisted(entID) == mComponentEntries.end()) {
                        mComponentEntries.emplace_back(std::make_shared<ComponentEntry<T>>(entID, component));
                    }
                    return component;      
                }

                WATERNION_INLINE virtual bool Erase(EntityID entID) override {
                    auto iter = this->IsExisted(entID);
                    if (iter != mComponentEntries.end()) {
                        mComponentEntries.erase(iter);
                    }

                    return true;
                }

                WATERNION_INLINE Shared<T> GetComponent(EntityID entID) {
                    auto iter = this->IsExisted(entID);
                    WATERNION_ASSERT(iter != mComponentEntries.end() && "Get non-existing component");
                    return StaticPtrCast<ComponentEntry<T>>((*iter))->GetComponent();
                }
            private:
                WATERNION_INLINE std::vector<Shared<ComponentEntryBase>>::iterator IsExisted(EntityID entID) {
                    return std::find_if(mComponentEntries.begin(), mComponentEntries.end(), [&](Shared<ComponentEntryBase> entry) {
                        return entry->GetEntityID() == entID;
                    });
                }
                std::vector<Shared<ComponentEntryBase>> mComponentEntries;
        };
    }
}