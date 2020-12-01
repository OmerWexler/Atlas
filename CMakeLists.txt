cmake_minimum_required(VERSION 3.0.0)
project(Atlas VERSION 0.1.0)

set(BUILD_TESTING ON)
include(CTest)

if(WIN32)
    file(GLOB SOURCES 
        "src/utils/*.cpp"
        "src/stonewall/socket/*.cpp"
        "src/stonewall/socket/winsocket/*.cpp"
        "src/stonewall/messages/*.cpp"
        "src/stonewall/comms/*.cpp"
    )
    
    include_directories(${CMAKE_SOURCE_DIR}/src/utils)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/socket)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/socket/winsocket)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms)
endif()

add_subdirectory(test)
add_subdirectory(src)

set(wxBUILD_SHARED FALSE)
add_subdirectory(wxWidgets)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
