include_directories(${CMAKE_SOURCE_DIR}/src/utils)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/socket)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/socket/winsocket)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages)

include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/accept_name)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/cancel_job)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/request_best_node)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_best_node)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_output)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_policy)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/seperator_based)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/set_name)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/simple_string)

include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms/basic)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/grid)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/resources)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/search_policy)

include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/job_core)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/general_purpose_core)

include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/job)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/job/log)