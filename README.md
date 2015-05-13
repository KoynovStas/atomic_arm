# Set atomic_fetch_xxx functions for ARMv6 ARMv7


## Description
New standard C11 has support atomic operations. Atomic operations was supported since version 4.9.x of GCC compiler.
The project implemented atomic operations such as **atomic_fetch_xxx** (xxx is add, sub, and, or, xor) and **atomic_exchange** for **int** type.

**You can use this set of functions in old projects that uses previous version of GCC. If transfer of the project to new standard C11 is difficult.**


***
<br/>
## Warning
This implementation does not contain memory barriers (DMB - command for ARM). 
Therefore, there can't be used to implement the synchronization primitives.
If you using GCC 4.9.0 or higher, use standard atomic operations according of STD C11.


##### This implementation supports the following architectures:  **ARMv6, ARMv6J, ARMv6K, ARMv6Z, ARMv6ZK, ARMv7, ARMv7A, ARMv7R**

<br/>
## Usage

You need to include **atomic_arm.h** file in your **.c** file.

```c
#include "atomic_arm.h"    //use our atomic functions

//Then we can use the atomic functions.
```

And add file **atomic_arm.S** to list of source files to compile. (see an example)
