cmake_minimum_required(VERSION 3.8)
file(GLOB SOURCES *.hpp *.cpp)
add_executable(SRE-ExerciseSnake ${SOURCES})
target_link_libraries(SRE-ExerciseSnake ${all_libs} SRE)
# copy resources into binary dir
file(COPY snake.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY snake.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY snake.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY snake.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
IF (WIN32)
 # Copy dll's to output path
 file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
 file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
 # Set working folder to project folder (to find project data runtime)
 set_target_properties(SRE-ExerciseSnake PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY 
 "${CMAKE_SOURCE_DIR}/Snake/bin")
ENDIF(WIN32)