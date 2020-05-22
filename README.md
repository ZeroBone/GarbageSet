# GarbageSet
This is a set data structure implementation in C. It can be initialized in constant time what makes it different compared to typical set implementation.

# Complexity

The following table gives an overview of what the datastructure is capable of. All the complexities are calculated assuming memory allocation is performed in `O(1)`.

|     Operation      |                         Description                          | Complexity |
| :----------------: | :----------------------------------------------------------: | :--------: |
| `garbageset_init`  | Initializes the data structure with the specified capacity.  |   `O(1)`   |
| `garbageset_isset` |     Checks if there is an element at a specified index.      |   `O(1)`   |
|  `garbageset_get`  | Retrieves the element at a specified index or returns null, if there is no element at that index. |   `O(1)`   |
| `garbageset_write` | Writes a new element at the specified index or overwrites an old one if it was defined. |   `O(1)`   |

# Space complexity

The space complexity of the data structure is in `O(n)`. However, apart from storing the payload array itself the data structure requires additional space for redundancy checking purposes. This additional space is about `2*n*sizeof(index_t)` bytes where n is the capacity and `index_t` is the type used for indexes. With this user-defined you can easily reduce the memory overhead.

# License

This software is licensed under the terms of the MIT License.

Copyright (c) 2020 Alexander Mayorov

For more details see the `LICENSE` file.