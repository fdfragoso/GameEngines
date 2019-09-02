cmake_minimum_required(VERSION 3.6)
project(RandomEngine)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_library(RandomEngine STATIC ${SOURCES})

install(TARGETS RandomEngine DESTINATION /usr/lib)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#########################################################
# FIND OPENGL
#########################################################
IF(APPLE)
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    MARK_AS_ADVANCED (OpenGL_LIBRARY)
    SET(EXTRA_LIBS ${OpenGL_LIBRARY})
ELSE (APPLE)
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    IF(UNIX)
        find_package(GLEW REQUIRED)
    ELSE(UNIX)
        find_package(glew REQUIRED)
    ENDIF(UNIX)
    include_directories(${GLEW_INCLUDE_DIR})
    SET(EXTRA_LIBS ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
ENDIF (APPLE)

find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(.)

# Box2D
find_package(Box2D REQUIRED)
include_directories(${BOX2D_INCLUDE_DIR})

#SRE
# build sre library
include_directories(include)
add_subdirectory(src)

#Linking libraries
target_link_libraries(RandomEngine ${EXTRA_LIBS} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SRE_LIBRARY} ${BOX2D_LIBRARY})

IF (WIN32)
    SET(SDL2_dll "" CACHE STRING "Where the SDL2.dll can be found")
    SET(SDL2_image_dll "" CACHE STRING "Where the SDL2_image.dll can be found")
    SET(libjpeg-9_dll "" CACHE STRING "Where the libjpeg-9.dll can be found")
    SET(libpng16-16_dll "" CACHE STRING "Where the libpng16-16.dll can be found")
    SET(libtiff-5_dll "" CACHE STRING "Where the libtiff-5.dll can be found")
    SET(libwebp-4_dll "" CACHE STRING "Where the libwebp-4.dll can be found")
    SET(zlib1_dll "" CACHE STRING "Where the zlib1.dll can be found")
    SET(DLLFileList ${libjpeg-9_dll} ${libpng16-16_dll} ${SDL2_dll} ${SDL2_image_dll} ${zlib1_dll} ${libtiff-5_dll} ${libwebp-4_dll})
    file(COPY ${DLLFileList} DESTINATION Debug)
    file(COPY ${DLLFileList} DESTINATION Release)
ENDIF(WIN32)
