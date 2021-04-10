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

add_custom_command(
    TARGET Atlas
    POST_BUILD
    COMMENT "Adding XRC files..."
    DEPENDS "${GUI_XRC_FILE}"
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_CURRENT_BINARY_DIR}/Debug/Atlas.xrc"
    COMMAND ${CMAKE_COMMAND} -E copy "${GUI_XRC_FILE}" "${CMAKE_CURRENT_BINARY_DIR}/Debug/Atlas.xrc"
    
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_CURRENT_BINARY_DIR}/Release/Atlas.xrc"
    COMMAND ${CMAKE_COMMAND} -E copy "${GUI_XRC_FILE}" "${CMAKE_CURRENT_BINARY_DIR}/Release/Atlas.xrc"
)