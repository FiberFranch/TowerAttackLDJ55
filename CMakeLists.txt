CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(TowerAttack)

file(GLOB SOURCE_FILES
  src/*.c
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/raylib/)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/external/raylib/src/
  )

target_link_libraries(${PROJECT_NAME}
  raylib
  )
