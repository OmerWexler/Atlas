set(IS_TEST, false, PARENT_SCOPE)

add_executable(
    Atlas
    WIN32
    main.cpp 
    ${SOURCES}
    ${APP_SOURCES}
)

target_link_libraries(Atlas PUBLIC wx::net wx::core wx::base wx::aui wx::html wx::xrc)
target_link_libraries(Atlas PUBLIC ${wxWidgets_LIBRARIES})