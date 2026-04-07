#pragma once
#include <memory>
#include <type_traits>
#include <vector>

#include "behaviour.hpp"
#include "component.hpp"

class Scene;

class Entity
{
   public:
    Entity(Scene* scene) : m_scene(scene)
    {
    }

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args);

    template <typename T>
    T* GetComponent()
    {
        for (auto& component : m_components)
        {
            T* ptr = dynamic_cast<T*>(component.get());
            if (ptr != nullptr)
            {
                return ptr;
            }
        }
        return nullptr;
    }

    void notifyTriggerEnter(Entity* other)
    {
        for (Behaviour* script : m_behaviours) script->onTriggerEnter(other);
    }

    void notifyCollisionEnter(Entity* other)
    {
        for (Behaviour* script : m_behaviours) script->onCollisionEnter(other);
    }

   private:
    std::vector<std::unique_ptr<Component>> m_components;
    std::vector<Behaviour*> m_behaviours;
    Scene* m_scene;
};

#include "world/scene.hpp"

template <typename T, typename... Args>
T& Entity::AddComponent(Args&&... args)
{
    auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
    newComponent->m_entity = this;
    T* rawPointer = newComponent.get();

    m_components.push_back(std::move(newComponent));

    if constexpr (std::is_base_of_v<Behaviour, T>)
    {
        m_scene->addBehaviour(rawPointer);
        m_behaviours.push_back(rawPointer);
        rawPointer->onStart();
    }

    return *rawPointer;
}
