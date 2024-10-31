cmake_minimum_required(VERSION 3.5.0)
project(recipeManager VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG master
)
FetchContent_MakeAvailable(SQLiteCpp)

set(SOURCES
    src/main.cpp
    src/domain/math/unit.cpp
    src/domain/math/quantity.cpp
    src/domain/ingredient/ingredient.cpp
    src/domain/inventory/inventory_item.cpp
    src/domain/recipe/recipe_step.cpp
    src/domain/recipe/recipe.cpp
    src/repository/sqlite/sqlite_ingredient_repository.cpp
    src/repository/sqlite/sqlite_inventory_item_repository.cpp
    src/repository/sqlite/sqlite_recipe_repository.cpp
    src/repository/sqlite/sqlite_recipe_step_repository.cpp
    src/infrastructure/database/database_connection.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/domain
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE SQLiteCpp sqlite3)