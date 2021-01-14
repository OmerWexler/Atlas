add_executable(Atlas
    main.cpp 
    ${SOURCES}
)

target_link_libraries(Atlas PUBLIC wx::net wx::core wx::base wx::aui wx::html)
target_link_libraries(Atlas PUBLIC ${wxWidgets_LIBRARIES})