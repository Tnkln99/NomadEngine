#pragma once
#include "IComponent.h"
#include "Transform.h"

#include <vector>
#include <memory>
#include <iostream>

template<typename T>
concept component = std::is_base_of<IComponent, T>::value;

class Actor
{
public:
    Transform mTransform{};

    template<component T, typename... Args>
    std::shared_ptr<T> addComponent(Args&&... args) {
        auto comp = std::make_shared<T>(std::forward<Args>(args)...);
        mComponents.emplace_back(comp);
        comp->mOwner = this;
        std::cout << comp->mOwner->mTransform.mPos.y << std::endl;
        return comp;
    }

    template<component T>
    std::shared_ptr<T> getComponent()
    {
        for (auto& comp : mComponents) {
            // Dynamic cast to check if the component is of type T
            std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(comp);
            if (result) {
                return result;  // Return the component if the cast is successful
            }
        }
        return nullptr;
    }
    
    void init();
    void update();
private:
    std::vector<std::shared_ptr<IComponent>> mComponents;
};

