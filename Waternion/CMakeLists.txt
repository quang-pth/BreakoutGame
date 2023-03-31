# engine project (shared lib)
project(Waternion VERSION 0.0.1)

# get all cpp-files
file(GLOB_RECURSE SRC_FILES Source/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} ${SRC_FILES})

# file(GLOB_RECURSE SRC_FILES glad.c CMAKE_CONFIGURE_DEPENDS)
# add_library(${Projectname} ${SRC_FILES}) 

# define symbols
add_definitions(-DWATERNION_EXPORT)
add_definitions(-D_DEBUG)

# windows platform
if (WIN32)
  target_link_libraries(${PROJECT_NAME} glfw3 freetype irrKlang)
  target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/External/include)
  target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/External/libs)
endif (WIN32)

# precompile headers
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source/pch.h)

# add include directory
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)