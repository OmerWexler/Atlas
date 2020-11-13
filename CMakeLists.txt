cmake_minimum_required(VERSION 3.0.0)
project(Atlas VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/src/utils)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms)

if (WIN32) 
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms/winsocket)
    file(GLOB SOURCES 
        "src/stonewall/comms/winsocket/*.cpp"
    )

endif (WIN32)

if (UNIX)

endif (UNIX)


file(GLOB SOURCES 
    "src/utils/*.cpp"
    "src/stonewall/comms/*.cpp"
)

add_executable(Atlas
    main.cpp 
    ${SOURCES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
