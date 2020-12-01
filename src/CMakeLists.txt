add_executable(Atlas
    main.cpp 
    ${SOURCES}
)

target_link_libraries(Atlas PUBLIC wx::net wx::core wx::base)