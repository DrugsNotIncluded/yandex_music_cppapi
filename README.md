<div align="center">
    <h1>Yandex Music C++ API library</h1>
</div>

**Огромное спасибо [MarshalX](https://github.com/MarshalX) за его замечательную [yandex-music-api python библиотеку](https://github.com/MarshalX/yandex-music-api) и составление [OpenAPI спецификации](https://github.com/acherkashin/yandex-music-open-api/blob/main/src/yandex-music.yaml) яндекс музыки на основе которой и была написана эта обёртка <3**

Примеры
---
```cpp
#include <string>
#include <iostream>
#include "ymcppapi/ymclient.hpp"

using namespace std;

int main() {
    string token = "token";
    auto client = ymapi::YMClient(token, "ru");
    auto result = client.account_status();
    cout << result.get();
}
// Возвращает статус аккаунта в виде nlohmann::json

```

Использование
---
## Cmake
Without FetchContent:
```cmake
add_subdirectory(deps/ymcppapi)
target_link_libraries("${PROJECT_NAME}" ymcppapi)
target_include_directories("${PROJECT_NAME}" PRIVATE "${ymcppapi_INCLUDE_DIRS}")
```

Документация
---
На данный момент у проекта нет документации, но все реализованные эндпоинты можно посмотреть в `ymcppapi/ymclient.cpp`

Использованные проекты
---
* [CPR]()
* [Nlohmann Json]()
* [Pugixml]()
* [fmt]() - Реализация C++20 `std::format`