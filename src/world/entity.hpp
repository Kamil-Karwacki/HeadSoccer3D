#pragma once
#include "component.hpp"
#include <vector>
#include <memory>
#include <iostream>

class Entity
{
public:
    Entity() = default;
    ~Entity() = default;

    void update(float deltaTime);
    void draw();

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
        
        newComponent->m_entity = this;
        
        T* rawPointer = newComponent.get();
        
        m_components.push_back(std::move(newComponent));
        
        rawPointer->start();
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
};