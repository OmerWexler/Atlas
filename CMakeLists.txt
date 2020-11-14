cmake_minimum_required(VERSION 3.0.0)
project(Atlas VERSION 0.1.0)

include(CTest)
enable_testing()


if (WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/src/utils)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms/winsocket)


    file(GLOB SOURCES 
        "src/utils/*.cpp"
        "src/stonewall/comms/*.cpp"
        "src/stonewall/comms/winsocket/*.cpp"
    )
ENDIF(WIN32)

add_executable(Atlas
    main.cpp 
    ${SOURCES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
