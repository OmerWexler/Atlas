set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/utils/Logger.cpp

    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/accept_name/AcceptNameMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/accept_name/AcceptNameparser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/accept_name/AcceptNameSerializer.cpp

    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/cancel_job/CancelJobMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/cancel_job/CancelJobparser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/cancel_job/CancelJobSerializer.cpp

    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/request_best_node/RequestBestNodeMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/request_best_node/RequestBestNodeParser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/request_best_node/RequestBestNodeSerializer.cpp
    
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_best_node/SendBestNodeMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_best_node/SendBestNodeParser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_best_node/SendBestNodeSerializer.cpp

    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job/SendJobMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job/SendJobParser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job/SendJobSerializer.cpp

    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_output/SendJobOutputMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_output/SendJobOutputParser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_output/SendJobOutputSerializer.cpp
    
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_policy/SendJobPolicyMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_policy/SendJobPolicyParser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_job_policy/SendJobPolicySerializer.cpp
    
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/seperator_based/SeperatorBasedMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/seperator_based/SeperatorBasedParser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/seperator_based/SeperatorBasedSerializer.cpp
    
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/set_name/SetNameMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/set_name/SetNameParser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/set_name/SetNameSerializer.cpp
    
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/simple_string/SimpleStringMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/simple_string/SimpleStringParser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/simple_string/SimpleStringSerializer.cpp
    
    ${CMAKE_SOURCE_DIR}/src/stonewall/comms/basic/BasicConnection.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/comms/basic/BasicServer.cpp

    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/grid/GridConnection.cpp
    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/grid/GridNode.cpp

    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/ASyncFunctionCore.cpp
    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/job_core/JobCore.cpp
    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/general_purpose_core/GeneralPurposeCore.cpp

    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/job/JobRegistry.cpp
)

if (WIN32)
    list(APPEND SOURCES
        ${CMAKE_SOURCE_DIR}/src/stonewall/socket/winsocket/WinConnectionSocket.cpp
        ${CMAKE_SOURCE_DIR}/src/stonewall/socket/winsocket/WinServerSocket.cpp
    )
endif()