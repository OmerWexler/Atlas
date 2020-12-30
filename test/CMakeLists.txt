include_directories(${CMAKE_SOURCE_DIR}/test/stonewall/socket)
include_directories(${CMAKE_SOURCE_DIR}/test/stonewall/messages)

add_executable(Tests
    main.cpp
    ${SOURCES}
)

add_test(NAME TestWinSocketCommunications COMMAND Tests 0)
add_test(NAME TestBasicCommunications COMMAND Tests 1)
add_test(NAME TestSeperatorBasedMessages COMMAND Tests 2)
add_test(NAME TestSendJobPolicyMessages COMMAND Tests 3)
add_test(NAME TestCancelJobMessage COMMAND Tests 4)
add_test(NAME TestRequestBestNodeMessages COMMAND Tests 5)