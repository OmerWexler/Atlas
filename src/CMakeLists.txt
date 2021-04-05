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
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/Debug/Atlas.xrc"
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_CURRENT_BINARY_DIR}/Debug/Atlas.xrc"
    COMMAND ${CMAKE_COMMAND} -E copy "${GUI_XRC_FILE}" "${CMAKE_CURRENT_BINARY_DIR}/Debug/Atlas.xrc"
    
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_CURRENT_BINARY_DIR}/Release/Atlas.xrc"
    COMMAND ${CMAKE_COMMAND} -E copy "${GUI_XRC_FILE}" "${CMAKE_CURRENT_BINARY_DIR}/Release/Atlas.xrc"
)

add_custom_target(AtlasGUIXRC ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/Debug/Atlas.xrc")

add_dependencies(Atlas AtlasGUIXRC)