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
#include "CastManager.h"

int main() {
    auto castManager = CastManager::init(); // shared ptr instance

    // reinterpret (valid)
    int a = 5;
    int* intPtr = &a;
    void* voidPtr = castManager->reinterpret<int, void>(intPtr); 
    std::cout << "Reinterpreted int* to void*: " << voidPtr << std::endl;

    // static (valid)
    void* voidPtrStatic = castManager->cast_static<int, void>(intPtr); 
    std::cout << "Static cast int* to void*: " << voidPtrStatic << std::endl;

    // dynamic (valid)
    struct Foundation { virtual ~Foundation() = default; };
    struct Derived : public Foundation {};
    Foundation* basePtr = new Derived();
    Derived* derivedPtr = castManager->dynamic<Foundation, Derived>(basePtr);
    if (derivedPtr) {
        std::cout << "Dynamic cast successful!" << std::endl;
    } else {
        std::cerr << "Invalid dynamic cast from Foundation* to Derived*" << std::endl;
    }

    // invalid
    /*  const-casting between const int* and int* is invalid when trying to modify the value of a const object or if the object itself is defined as const.  */
    const int b = 10;
    const int* constIntPtr = &b;
    int* nonconstint = castManager->cast_const<const int, int>(constIntPtr);  // Const cast (valid)
    if (nonconstint) {
        std::cout << "Const cast successful!" << std::endl;
    } else {
        std::cerr << "Invalid const cast from const int* to int*" << std::endl;
    }


    delete basePtr;

    return 0;
}
```
**Output (Above)**:

```bash
Reinterpreted i to v
Reinterpreted int* to void*: 0x7fff3ec622b4
Static cast int* to void*: 0x7fff3ec622b4
Dynamic cast successful!
Invalid const cast from i to i
Invalid const cast from const int* to int*
```

# License
Do whatever you want with this code and modify it however. If you manage to do something illegal with this, then don't blame me (Why would you though).
