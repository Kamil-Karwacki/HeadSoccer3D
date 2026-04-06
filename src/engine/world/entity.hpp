#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <type_traits>

#include "component.hpp"
#include "behaviour.hpp"

class Scene;

class Entity
{
public:
    Entity(Scene* scene) : m_scene(scene) {}
    template <typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
        newComponent->m_entity = this;
        T* rawPointer = newComponent.get();
        m_components.push_back(std::move(newComponent));
        
        if constexpr (std::is_base_of_v<Behaviour, T>)
        {
            m_scene->addBehaviour(rawPointer);
            rawPointer->onStart();
        }

        return *rawPointer;
    }

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

private:
    std::vector<std::unique_ptr<Component>> m_components;
    Scene* m_scene;
};