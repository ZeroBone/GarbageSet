# GarbageSet
This is a set data structure implementation with all operations implemented in O(1), including initialization.

# Complexity

The following table gives an overview of what the datastructure is capable of. All the complexities are calculated assuming memory allocation is performed in `O(1)`.

|     Operation      |                         Description                          | Complexity |
| :----------------: | :----------------------------------------------------------: | :--------: |
| `garbageset_init`  | Initializes the data structure with the specified capacity.  |   `O(1)`   |
| `garbageset_isset` |     Checks if there is an element at a specified index.      |   `O(1)`   |
|  `garbageset_get`  | Retrieves the element at a specified index or returns null, if there is no element at that index. |   `O(1)`   |
| `garbageset_write` | Writes a new element at the specified index or overwrites an old one if it was defined. |   `O(1)`   |

