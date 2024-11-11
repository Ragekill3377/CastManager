/* Ragekill3377's CastManager*/
/* Honestly, it's useless. It just... looks satisfying.*/

/*

auto castManager = CastManager::init(); // shared ptr
castManager->cast_const
castManager->cast_static
castManager->dynamic
castManager->reinterpret

*/

#pragma once

#include <iostream>
#include <memory>
#include <type_traits>

class CastManager {
public:
    CastManager() = default;

    static std::shared_ptr<CastManager> init() {
        return std::make_shared<CastManager>();
    }

     template <typename From, typename To>
    To* cast_static(From* ptr) {
        if (!ptr) {
            return nullptr;
        }
        if (std::is_convertible<From*, To*>::value) {
            return static_cast<To*>(ptr);
        } else {
            std::cerr << "Invalid static cast from " << typeid(From).name() << " to " << typeid(To).name() << std::endl;
            return nullptr;
        }
    }

    template <typename From, typename To>
    To* dynamic(From* ptr) {
        if (!ptr) {
            return nullptr;
        }
        To* result = dynamic_cast<To*>(ptr);
        if (result) {
            return result;
        } else {
            std::cerr << "Invalid dynamic cast from " << typeid(From).name() << " to " << typeid(To).name() << std::endl;
            return nullptr;
        }
    }

    template <typename From, typename To>
    To* cast_const(From* ptr) {
        if (!ptr) {
            return nullptr;
        }
        if (std::is_convertible<From*, To*>::value) {
            return const_cast<To*>(ptr);
        } else {
            std::cerr << "Invalid const cast from " << typeid(From).name() << " to " << typeid(To).name() << std::endl;
            return nullptr;
        }
    }

    template <typename From, typename To>
    To* reinterpret(From* ptr) {
        if (!ptr) {
            return nullptr;
        }
        To* result = reinterpret_cast<To*>(ptr);
        std::cout << "Reinterpreted " << typeid(From).name() << " to " << typeid(To).name() << std::endl;
        return result;
    }
};
