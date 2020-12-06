include_directories(${CMAKE_SOURCE_DIR}/test/stonewall/socket)

add_executable(Tests
    main.cpp
    ${SOURCES}
)

add_test(NAME TestWinSocketCommunications COMMAND Tests 0)
add_test(NAME TestBasicCommunications COMMAND Tests 1)