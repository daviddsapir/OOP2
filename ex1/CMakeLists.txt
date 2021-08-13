
cmake_minimum_required (VERSION 3.14)
project ("ex1_David_Sapir_Shimshon_Polak")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/permissive-)
endif ()


add_executable (ex1_David_Sapir_Shimshon_Polak "")

add_subdirectory (include)
add_subdirectory (src)


# TODO: Add tests and install targets if needed.
