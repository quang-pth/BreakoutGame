# runtime project (.exe)
project(Game VERSION 0.0.1)

# get all cpp-files
file(GLOB_RECURSE SRC_FILES Source/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# link libraries
target_link_libraries(${PROJECT_NAME} Waternion)

# includes directories
include_directories(${CMAKE_SOURCE_DIR}/Waternion/Source ${CMAKE_SOURCE_DIR}/Game/Source)