#pragma once

#include"pch.h"
#include"Type.h"

namespace Waternion {
    namespace ECS {
        class ComponentEntryBase {
            public:
                WATERNION_INLINE virtual ~ComponentEntryBase() = default;
                virtual operator EntityID() const = 0;                
                virtual EntityID GetEntityID() const = 0;       
                virtual UUID GetComponentID() const = 0;       
        };

        template<typename T>
        class ComponentEntry : public ComponentEntryBase {
            public:
                WATERNION_INLINE ComponentEntry(EntityID entID, Shared<T> component) 
                    : mEntityID(entID), mComponent(component) {
                        mComponent->SetOwner(entID);
                    }
                WATERNION_INLINE virtual operator EntityID() const override { return mEntityID; }                
                WATERNION_INLINE virtual EntityID GetEntityID() const override { return mEntityID; }       
                WATERNION_INLINE virtual UUID GetComponentID() const override { return mComponent->GetID(); }       
                WATERNION_INLINE Shared<T> GetComponent() const { return mComponent; }         
            private:
                EntityID mEntityID;
                Shared<T> mComponent;
        };

        class ComponentArrayBase {
            public:
                WATERNION_INLINE virtual ~ComponentArrayBase() = default;
                virtual bool Erase(EntityID) = 0;
                virtual void Activate(EntityID) = 0;
                virtual void Deactivate(EntityID) = 0;
        };

        template<typename T>
        class ComponentArray : public ComponentArrayBase {
            public: 
                WATERNION_INLINE ComponentArray() : mComponentEntries() {}

                WATERNION_INLINE Shared<T> Add(EntityID entID, Shared<T> component) {
                    if (this->IsEntityExisted(entID) == mComponentEntries.end()) {
                        mComponentEntries.emplace_back(MakeShared<ComponentEntry<T>>(entID, component));
                    }
                    return component;      
                }

                WATERNION_INLINE virtual bool Erase(EntityID entID) override {
                    auto iter = this->IsEntityExisted(entID);
                    if (iter != mComponentEntries.end()) {
                        mComponentEntries.erase(iter);
                    }

                    return true;
                }

                WATERNION_INLINE virtual void Activate(EntityID id) override {
                    GetComponent(id)->SetDisabled(false);
                }

                WATERNION_INLINE virtual void Deactivate(EntityID id) override {
                    GetComponent(id)->SetDisabled(true);
                }

                WATERNION_INLINE Shared<T> GetComponent(EntityID id) {
                    auto iter = this->IsEntityExisted(id);
                    WATERNION_ASSERT(iter != mComponentEntries.end() && "Get non-existing entity");
                    return StaticPtrCast<ComponentEntry<T>>((*iter))->GetComponent();
                }

                WATERNION_INLINE EntityID GetEntityID(UUID componentID) {
                    for (auto iter = mComponentEntries.begin(); iter != mComponentEntries.end(); iter++) {
                        Shared<ComponentEntryBase> entry = *iter;
                        UUID id = entry->GetComponentID();
                        if (id == componentID) {
                            return entry->GetEntityID();
                        }
                    }
                    return INVALID_ID;
                }

                WATERNION_INLINE const std::vector<Shared<T>>& GetComponents() {
                    std::vector<Shared<T>> components;
                    for(Shared<ComponentEntryBase> entry : mComponentEntries) {
                        components.emplace_back(StaticPtrCast<ComponentEntry<T>>(entry)->GetComponent());
                    }
                    return components;
                }
            private:
                WATERNION_INLINE std::vector<Shared<ComponentEntryBase>>::iterator IsEntityExisted(EntityID id) {
                    return std::find_if(mComponentEntries.begin(), mComponentEntries.end(), [&](Shared<ComponentEntryBase> entry) {
                        return entry->GetEntityID() == id;
                    });
                }
            private:
                std::vector<Shared<ComponentEntryBase>> mComponentEntries;
        };
    }
}