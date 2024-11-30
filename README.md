# CastManager

`CastManager` is a simple utility for safely handling common C++ type casts: `static_cast`, `dynamic_cast`, `const_cast`, and `reinterpret_cast`. It uses runtime checks to ensure valid casting. (I was bored.)

## Features

- **`cast_static<From, To>(From* ptr)`**
- **`dynamic<From, To>(From* ptr)`**
- **`cast_const<From, To>(From* ptr)`**
- **`reinterpret<From, To>(From* ptr)`**

## Usage
**Prequisites**:
-> cpp compiler (g++ or clang++ or whatever you have)
-> C++11

Simply include the `CastManager.h` header in your C++ project:

```cpp
#include "CastManager.h"
```

# Code example:
```cpp
#include <iostream>
#include <memory>
#include <typeinfo>
#include "CastManager.h"

class Base {
public:
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void hello() { std::cout << "Hello from Derived!" << std::endl; }
};

int main() {
    // init
    auto castManager = CastManager::init();

    
    std::shared_ptr<Base> basePtr = std::make_shared<Derived>();

    
    castManager->cast_static<Base, Derived>(basePtr);

    
    castManager->dynamic<Base, Derived>(basePtr);

    
    castManager->reinterpret<Base, Derived>(basePtr);

    
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}

```
**Output (Above)**:

```bash
Cast error: 4BaseDynamic cast succeeded!
 to 7Derived (static)
Reinterpreted 4Base to 7Derived

```

# License
Do whatever you want with this code and modify it however. If you manage to do something illegal with this, then don't blame me (Why would you though).
