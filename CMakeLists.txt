cmake_minimum_required(VERSION 3.0.0)
project(Atlas VERSION 0.1.0)

set(BUILD_TESTING ON)
include(CTest)

include(SourcesList.cmake)
include(CommonIncludeList.cmake)

add_subdirectory(test)
add_subdirectory(src)

# set(QT_DIR "E:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake\\Qt5")
# set(Qt5_DIR "E:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake\\Qt5")
# add_subdirectory(Qt-Secret)

set(wxBUILD_SHARED FALSE)
add_subdirectory(wxWidgets)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /EHsc /D_DEBUG /DEBUG /MDd")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /EHsc /D_DEBUG /DEBUG /MDd")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)