cmake_minimum_required(VERSION 3.0.0)
project(Atlas VERSION 0.1.0)

set(BUILD_TESTING ON)
include(CTest)

include(SourcesList.cmake)
include(CommonIncludeList.cmake)

add_subdirectory(test)
add_subdirectory(src)

set(wxBUILD_SHARED FALSE)
add_subdirectory(wxWidgets)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
