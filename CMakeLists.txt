cmake_minimum_required(VERSION 3.1)

set(project_name InvestCalc) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# ----------------------------------------

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE ..
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})

# ----------------------------------------
add_library(${project_name}-lib
        src/AppComponent.hpp
        src/controller/MyController.cpp
        src/controller/MyController.hpp
        src/dto/DTOs.hpp
        )

## link libs

#find_package(oatpp 1.3.0 REQUIRED)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

target_link_libraries(${project_name}-lib ${CONAN_LIBS})



#target_link_libraries(${project_name}-lib
#        PUBLIC oatpp::oatpp
#        PUBLIC oatpp::oatpp-test
#        )

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe
        src/App.cpp
        test/app/MyApiTestClient.hpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

install(TARGETS ${project_name}-exe DESTINATION ${CMAKE_SOURCE_DIR}/Release)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/app/public/ DESTINATION ${CMAKE_SOURCE_DIR}/Release/app)


add_executable(${project_name}-test
        test/tests.cpp
        test/app/TestComponent.hpp
        test/app/MyApiTestClient.hpp
        test/MyControllerTest.cpp
        test/MyControllerTest.hpp
        )

target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        )

enable_testing()
add_test(project-tests ${project_name}-test)

