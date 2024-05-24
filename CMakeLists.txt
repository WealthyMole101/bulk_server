cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(bulk_server VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

add_executable(bulk_server main.cpp server.h server.cpp async.h async.cpp analyzer.h analyzer.cpp saver.h saver.cpp out.h printer.h printer.cpp)

include_directories(/usr/include)

if (MSVC)
    target_compile_options(bulk_server PRIVATE
        /W4
    )
else ()
    target_compile_options(bulk_server PRIVATE
        #-Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bulk_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT vbespalov@astralinux.ru)

include(CPack)
