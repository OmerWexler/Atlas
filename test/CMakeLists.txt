include_directories(${CMAKE_SOURCE_DIR}/test/stonewall/socket)
include_directories(${CMAKE_SOURCE_DIR}/test/stonewall/messages)
include_directories(${CMAKE_SOURCE_DIR}/test/boulderbreaker/resources/performance_analyzer/win_performance_analyzer)

set(IS_TEST, true, PARENT_SCOPE)

add_executable(Tests
    main.cpp
    ${SOURCES}
)

add_test(NAME TestWinSocketCommunications COMMAND Tests 0)
add_test(NAME TestBasicCommunications COMMAND Tests 1)
add_test(NAME TestSeperatorBasedMessages COMMAND Tests 2)
add_test(NAME TestSendJobPolicyMessages COMMAND Tests 3)
add_test(NAME TestCancelJobMessage COMMAND Tests 4)
add_test(NAME TestSendNodePerformanceMessages COMMAND Tests 5)
add_test(NAME TestSendJobMessage COMMAND Tests 6)
add_test(NAME TestSendJobOutputMessage COMMAND Tests 7)
add_test(NAME WinPerformanceAnalyzerTest COMMAND Tests 8)