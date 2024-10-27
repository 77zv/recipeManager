cmake_minimum_required(VERSION 3.5.0)
project(recipeManager VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/domain/math/unit.cpp
    src/domain/math/quantity.cpp
    src/domain/ingredient/ingredient.cpp
    # src/domain/inventory/inventoryItem.cpp
    # src/domain/inventory/stock.cpp
    # src/domain/recipe/recipeStep.cpp
    # src/domain/recipe/recipe.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/domain
)

add_executable(${PROJECT_NAME} ${SOURCES})