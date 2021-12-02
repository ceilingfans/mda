# mda

`mda` is a multi-dimensional static array object which can be copied or reassigned regardless of length or number of dimensions. Recursively stores an array of `mda`s inside itself. 0-dimensional arrays or `mda`s store content of type `T` and can be cast to type `T` when this content is to be accessed. n-dimensional `mda`s (n>0) can be subscripted to access its children (n-1)-dimensional `mda`s, in the way that a `std::array` can be subscripted to access data stored inside it.

## Prerequisites

* c++11 or above
* `mda.hpp` includes the libraries:
    * `<vector>`
    * `<stdexcept>`
    * `<memory>`

## Documentation

### namespace `mda`

Namespace under which the mda::mda class is defined.

### class `template <typename T> mda::mda<T>`

Multi-dimensional static array object.

### constructor function `template <typename T> mda::mda<T>::mda()`

Empty constructor, calls empty constructor of `T` and initialized with size 0 and dim 0.

### constructor function `template <typename T> mda::mda<T>::mda(std::vector<size_t>&& shape)`
### constructor function `template <typename T> mda::mda<T>::mda(const std::vector<size_t>& shape)`

Constructs `mda` with `shape[0]` `mda`s, each containing `shape[1]` `mda`s, etc..., constructors differing by rvalue and lvalue parameters.

```C++
#include <iostream>
#include "mda.hpp"
int main()
{
    mda::mda<int> arr0({2, 3}); // initialize 2-dimensional mda::mda<int> arr0 with 2 rows and 3 columns
}
```

### function `template <typename T> size_t mda::mda<T>::size() const`

Returns the size, length, or number of `mda`s inside itself.

```C++
#include <iostream>
#include "mda.hpp"
int main()
{
    mda::mda<int> arr0({2, 3}); // initialize 2-dimensional mda::mda<int> arr0 with 2 rows (1-dimensional mda::mda<int>s) and 3 columns
    std::cout << arr0.size() << std::endl; // prints 2 because arr0 has 2 mda::mda<int>s inside itself
}
```

Output:
```
2
```

### function `template <typename T> size_t mda::mda<T>::dim() const`

Returns the recursion depth or number of dimensions of the `mda`.

```C++
#include <iostream>
#include "mda.hpp"
int main()
{
    mda::mda<int> arr0({2, 3}); // initialize 2-dimensional mda::mda<int> arr0 with 2 rows (1-dimensional mda::mda<int>s) and 3 columns
    std::cout << arr0.dim() << std::endl; // prints 2 because arr0 was initialized as having 2 rows and 3 columns, hence having 2 dimensions
}
```

Output:
```
2
```

### function `template <typename T> const mda::mda<T>& mda::mda<T>::operator[](size_t i) const`

Returns `i`th member `mda` by const reference. Throws `std::invalid_argument` exception if `mda` is 0-dimensional.

```C++
#include <iostream>
#include "mda.hpp"
int main()
{
    mda::mda<int> arr0({2, 3}); // initialize 2-dimensional mda::mda<int> arr0 with 2 rows (1-dimensional mda::mda<int>s) and 3 columns
    arr0[0][0][0]; // arr0 is 2-dimensional, arr0[0] is 1-dimensional, arr0[0][0] is 0-dimensional, arr0[0][0][0] throws std::invalid_argument
    std::cout << "okay!" << std::endl;
}
```

Output:
```
terminate called after throwing an instance of 'std::invalid_argument'
  what():  attempted subscript of mda with dim==0
```

```C++
#include <iostream>
#include "mda.hpp"
int main()
{
    mda::mda<int> arr0({2, 3}); // initialize 2-dimensional mda::mda<int> arr0 with 2 rows (1-dimensional mda::mda<int>s) and 3 columns
    arr0[0][0]; // arr0 is 2-dimensional, arr0[0] is 1-dimensional, arr0[0][0] is 0-dimensional which is okay
    std::cout << "okay!" << std::endl;
}
```

Output:
```
okay!
```

### function `template <typename T> mda::mda::operator T&() const`

Casts 0-dimensional `mda<T>`s to type `T` which returns its contents. Throws `std::invalid_argument` if `mda` is not 0-dimensional.

```C++
#include <iostream>
#include "mda.hpp"
int main()
{
    mda::mda<int> arr0({2, 3}); // initialize 2-dimensional mda::mda<int> arr0 with 2 rows (1-dimensional mda::mda<int>s) and 3 columns
    std::cout << arr0[0] << std::endl; // attempted implicit cast of arr0[0] to int (arr0[0] is 1-dimensional; will result in error)
}
```

Output:
```
terminate called after throwing an instance of 'std::invalid_argument'
  what():  attempted cast from mda with dim>0
```

```C++
#include <iostream>
#include "mda.hpp"
int main()
{
    mda::mda<int> arr0({2, 3}); // initialize 2-dimensional mda::mda<int> arr0 with 2 rows (1-dimensional mda::mda<int>s) and 3 columns
    std::cout << arr0[0][0] << std::endl; // implicit cast of arr0[0][0] to int (okay)
}
```

Output:
```
0
```

Explicit cast must be used if accessing a member function of the contained object.

```C++
#include <iostream>
#include <vector>
#include "mda.hpp"
int main()
{
    mda::mda< std::vector<int> > arr0({2, 3});
    ((std::vector<int>&) arr0[0][0]).push_back(1); // remember to cast to vector REFERENCE
    // (casting to vector non-reference only affects some random copy of the data and not the original data in arr0[0][0])
    std::cout << ((std::vector<int>) arr0[0][0])[0] << std::endl; // cast also to subscript vector
}
```

Output:
```
1
```

### function `template <typename T> void mda::mda::operator=(const T& p_content)`

Copies `p_content` into 0-dimensional `mda`. Throws `std::invalid_argument` if `mda` is not 0-dimensional.

```C++
#include <iostream>
#include "mda.hpp"
int main()
{
    mda::mda<int> arr0({2, 3});
    arr0[0] = 1; // attempted implicit cast arr[0] mda<int>& to int& (arr[0] is 1-dimensional; will result in error)
    std::cout << arr0[0][0] << std::endl;
}
```

Output:
```
terminate called after throwing an instance of 'std::invalid_argument'
  what():  attempted assignment of value to mda with dim>0
```

```C++
#include <iostream>
#include "mda.hpp"
int main()
{
    mda::mda<int> arr0({2, 3});
    arr0[0][0] = 1; // implicit cast arr[0][0] mda<int>& to int& (okay)
    std::cout << arr0[0][0] << std::endl;
}
```

Output:
```
1
```

### constructor function `template <typename T> void mda::mda<T>::mda(const mda<T>& p_mda)`
### constructor function `template <typename T, typename U> void mda::mda<T>::mda(const mda<U>& p_mda)`

Copies the contents of `p_mda` into the new `mda`. Two constructors are created to support type casting.

```C++
#include <iostream>
#include "mda.hpp"
int main()
{
    mda::mda<int> arr0({2, 3});
    arr0[0][0] = 1;
    mda::mda<int> arr1 = arr0;
    mda::mda<float> arr2 = arr0;
    std::cout << arr0[0][0] << ' ' << arr1[0][0] << ' ' << arr2[0][0] << std::endl;
}
```

Output:
```
1 1 1
```

### function `template <typename T> void operator=(const mda<T>& p_mda)`
### function `template <typename T> void operator=(mda<T>&& p_mda)`

Copies the contents of `p_mda` into the existing `mda`. Two constructors are created to support lvalue and rvalue parameters.

```C++
#include <iostream>
#include "mda.hpp"
int main()
{
    mda::mda<int> arr0({2, 3});
    arr0[0][0] = 1;
    mda::mda<int> arr1;
    arr1 = arr0;
    mda::mda<float> arr2;
    arr2 = arr0;
    std::cout << arr0[0][0] << ' ' << arr1[0][0] << ' ' << arr2[0][0] << std::endl;
}
```

Output:
```
1 1 1
```

