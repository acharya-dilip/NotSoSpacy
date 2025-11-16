cmake_minimum_required(VERSION 4.0)
project(NotSoSpacy C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find GTK4 with pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})

link_directories(${GTK4_LIBRARY_DIRS})


add_executable(NotSoSpacy main.c
)

target_link_libraries(${PROJECT_NAME}
        ${GTK4_LIBRARIES}
)
target_compile_options(${PROJECT_NAME}
        PRIVATE ${GTK4_CFLAGS_OTHER})