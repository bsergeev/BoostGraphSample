cmake_minimum_required (VERSION 3.5)

if(NOT TARGET_NAME)
  set(TARGET_NAME GlApp)
endif()
project(${TARGET_NAME} VERSION 0.0.1 LANGUAGES CXX)

option(Boost_USE_STATIC_LIBS "Use Boost static version" ON)
set(BOOST_VER "1.67.0" CACHE STRING "boost version")
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost ${BOOST_VER} REQUIRED COMPONENTS graph REQUIRED)
if (NOT Boost_FOUND)
  message(FATAL_ERROR "Boost not found.")
endif()

# Define project_options "library" with all the build options and warnings
include(cmake/ProjectOptions.cmake)
include(cmake/BuildType.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(include_dirs  "${PROJECT_SOURCE_DIR}/src")
set(Sources "${PROJECT_SOURCE_DIR}/src/cuthill_mckee_ordering.cpp")
FILE(GLOB Headers "${PROJECT_SOURCE_DIR}/src/*.h")
message(STATUS "-> Sources: ${Sources}")

add_executable(${TARGET_NAME} ${Sources} ${Headers})

target_include_directories(${TARGET_NAME} 
  PRIVATE
    "${include_dirs}"
    "${Boost_INCLUDE_DIRS}"
)
target_link_libraries(${TARGET_NAME}  project_options)

if (MSVC)
  add_definitions(-D_WIN32_WINNT=0x0601) # Windows 7
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})
endif()

