### Add to project:
```cmake
add_subdirectory(ymcppapi)
target_link_libraries("${PROJECT_NAME}" ymcppapi)
target_include_directories("${PROJECT_NAME}" PRIVATE "${ymcppapi_INCLUDE_DIRS}")
```

### Include:
```cpp
#include <ymcppapi/ymapi.hpp>
```
