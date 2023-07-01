project(imgui VERSION 0.0.1)

file(GLOB_RECURSE SRC_FILES Source/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

if (WIN32)
  target_link_libraries(${PROJECT_NAME} glfw3)
  target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/External/include)
  target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/External/libs)
endif (WIN32)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)