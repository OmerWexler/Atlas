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
        "src/stonewall/serializers/*.cpp"
        "src/stonewall/parsers/*.cpp"
        "src/stonewall/comms/*.cpp"
        "src/stonewall/comms/basic/*.cpp"
        "src/boulderbreaker/grid/*.cpp"
        "src/boulderbreaker/callback/*.cpp"
        "src/boulderbreaker/search_policy/*.cpp"
        "src/boulderbreaker/resources/*.cpp"
        "src/boulderbreaker/job/*.cpp"
    )
    
    include_directories(${CMAKE_SOURCE_DIR}/src/utils)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/socket)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/socket/winsocket)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/parsers)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/serializers)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms/basic)
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/grid)
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/callback)
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/resources)
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/search_policy)
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/job)
endif()

add_subdirectory(test)
add_subdirectory(src)

set(wxBUILD_SHARED FALSE)
add_subdirectory(wxWidgets)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
