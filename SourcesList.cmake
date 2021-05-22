set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/utils/Logger.cpp

    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/cancel_job/CancelJobMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/cancel_job/CancelJobparser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/cancel_job/CancelJobSerializer.cpp

    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/disconnect/DisconnectMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/disconnect/Disconnectparser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/disconnect/DisconnectSerializer.cpp
    
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/reject_name/RejectNameMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/reject_name/RejectNameparser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/reject_name/RejectNameSerializer.cpp
    
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_node_performance/SendNodePerformanceMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_node_performance/SendNodePerformanceParser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_node_performance/SendNodePerformanceSerializer.cpp
    
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_rsa_key/SendRSAKeyMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_rsa_key/SendRSAKeyParser.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/messages/send_rsa_key/SendRSAKeySerializer.cpp

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
    
    ${CMAKE_SOURCE_DIR}/src/stonewall/encryption/RSAEncryptionModule.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/encryption/euclid.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/encryption/mpuint.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/encryption/random.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/encryption/rsa.cpp

    ${CMAKE_SOURCE_DIR}/src/stonewall/comms/basic/BasicConnection.cpp
    ${CMAKE_SOURCE_DIR}/src/stonewall/comms/basic/BasicServer.cpp

    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/job/IJob.cpp
    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/job/JobRegistry.cpp
    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/resources/performance_analyzer/win_performance_analyzer/WinPerformanceAnalyzer.cpp
    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/resources/PCPerformance.cpp
    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/job/job_wait/JobWait.cpp
)

set(
    APP_SOURCES

    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/grid/GridConnection.cpp
    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/grid/GridNode.cpp

    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/ASyncFunctionCore.cpp
    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/job_core/JobCore.cpp
    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/general_purpose_core/GeneralPurposeCore.cpp
    ${CMAKE_SOURCE_DIR}/src/boulderbreaker/function_core/resource_core/ResourceCore.cpp

    ${CMAKE_SOURCE_DIR}/src/atlas_app/MainFrame.cpp
    ${CMAKE_SOURCE_DIR}/src/atlas_app/AtlasApp.cpp
)

if (WIN32)
    list(APPEND SOURCES
        ${CMAKE_SOURCE_DIR}/src/stonewall/socket/winsocket/WinConnectionSocket.cpp
        ${CMAKE_SOURCE_DIR}/src/stonewall/socket/winsocket/WinServerSocket.cpp
    )
endif()


set(GUI_XRC_FILE
    ${CMAKE_SOURCE_DIR}/GUI/Atlas.xrc)