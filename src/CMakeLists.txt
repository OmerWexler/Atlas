add_executable(Atlas
    main.cpp 
    ${SOURCES}
)

add_executable(Server
    Server.cpp 
    ${SOURCES}
)

add_executable(Client
    Client.cpp 
    ${SOURCES}
)

target_link_libraries(Atlas PUBLIC wx::net wx::core wx::base wx::aui wx::html)
target_link_libraries(Atlas PUBLIC ${wxWidgets_LIBRARIES})

target_link_libraries(Server PUBLIC wx::net wx::core wx::base wx::aui wx::html)
target_link_libraries(Server PUBLIC ${wxWidgets_LIBRARIES})

target_link_libraries(Client PUBLIC wx::net wx::core wx::base wx::aui wx::html)
target_link_libraries(Client PUBLIC ${wxWidgets_LIBRARIES})