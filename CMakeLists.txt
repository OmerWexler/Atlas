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
        "src/stonewall/messages/cancel_job/*.cpp"
        "src/stonewall/messages/request_best_node/*.cpp"
        "src/stonewall/messages/send_best_node/*.cpp"
        "src/stonewall/messages/send_job/*.cpp"
        "src/stonewall/messages/send_job_output/*.cpp"
        "src/stonewall/messages/send_job_policy/*.cpp"
        "src/stonewall/messages/seperator_based/*.cpp"
        "src/stonewall/messages/simple_string/*.cpp"

        "src/stonewall/comms/*.cpp"
        "src/stonewall/comms/basic/*.cpp"
        "src/boulderbreaker/grid/*.cpp"
        "src/boulderbreaker/search_policy/*.cpp"
        "src/boulderbreaker/resources/*.cpp"
        
        "src/boulderbreaker/handler/*.cpp"
        "src/boulderbreaker/handler/registration_handler/*.cpp"
        "src/boulderbreaker/handler/job_handler/*.cpp"
        
        "src/boulderbreaker/job/*.cpp"
        "src/boulderbreaker/job/log/*.cpp"
    )
    
    include_directories(${CMAKE_SOURCE_DIR}/src/utils)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/socket)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/socket/winsocket)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages)

    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/cancel_job)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/request_best_node)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_best_node)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_output)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_policy)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/seperator_based)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/simple_string)
    
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms)
    include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms/basic)
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/grid)
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/resources)
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/search_policy)
    
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/handler)
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/handler/registration_handler)
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/handler/job_handler)

    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/job)
    include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/job/log)
endif()

add_subdirectory(test)
add_subdirectory(src)

set(wxBUILD_SHARED FALSE)
add_subdirectory(wxWidgets)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
