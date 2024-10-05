#pragma once

#include <vector>
#include <memory>
#include "AssetManager.h"

namespace asteroidescape
{

    template <typename T>
    class GenericObjectPool
    {
    public:
        // initializes the pool with the given size and asset
        GenericObjectPool(AssetManager& asset, size_t poolSize)
        {
            for (size_t i = 0; i < poolSize; ++i)
            {
                _pool.push_back(std::make_unique<T>(asset));  // Assuming T has a parameterised constructor
                _pool.back()->SetActive(false);
            }
        }

        // initializes the pool with the given size and asset
        GenericObjectPool(size_t poolSize)
        {
            for (size_t i = 0; i < poolSize; ++i)
            {
                _pool.push_back(std::make_unique<T>());  // Assuming T has a default constructor
                _pool.back()->SetActive(false);
            }
        }

        // Acquire an object from the pool (activates the first available inactive object)
        T* Acquire()
        {
            for (auto& obj : _pool)
            {
                if (!obj->IsActive())
                {
                    obj->SetActive(true);
                    return obj.get();
                }
            }
            return nullptr;  // All objects are active
        }

        // Release an object back to the pool (deactivates it)
        void Release(T* object)
        {
            object->SetActive(false);
        }

        // Return the list of objects in the pool (read-only access)
        const std::vector<std::unique_ptr<T>>& GetObjects() const
        {
            return _pool;
        }

        // Clear all objects from the pool
        void Clear()
        {
            for (auto& obj : _pool)
            {
                obj->SetActive(false);
            }
        }

    private:
        std::vector<std::unique_ptr<T>> _pool;  // Container for the pool of objects
    };

}