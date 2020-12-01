include_directories(${CMAKE_SOURCE_DIR}/test/stonewall/socket)

add_executable(Tests
    main.cpp
    ${SOURCES}
)

add_test(NAME TestWinSocketCommunicationSequence COMMAND Tests 0)