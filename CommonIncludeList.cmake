include_directories(${CMAKE_SOURCE_DIR}/src/utils)
include_directories(${CMAKE_SOURCE_DIR}/src/utils/subprocess)

include_directories(${CMAKE_SOURCE_DIR}/src/atlas_app)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/socket)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/socket/winsocket)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages)

include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/cancel_job)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/disconnect)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/reject_name)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/request_node_performance)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_node_performance)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_rsa_key)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_output)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_policy)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/seperator_based)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/set_name)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/simple_string)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/transfer_file)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/messages/transfer_file_block)

include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/encryption)
include_directories(${CMAKE_SOURCE_DIR}/src/stonewall/comms/basic)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/grid)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/resources)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/resources/performance_analyzer)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/resources/performance_analyzer/win_performance_analyzer)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/search_policy)

include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/job_core)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/general_purpose_core)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/resource_core)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/file_core)

include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/job)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/job/log)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/job/job_wait)
include_directories(${CMAKE_SOURCE_DIR}/src/boulderbreaker/job/job_subprocess)