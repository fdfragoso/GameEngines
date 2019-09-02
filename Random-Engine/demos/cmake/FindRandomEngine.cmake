
# Try to find RandomEngine library and include path.
# If cannot find... GG 
#
# RANDOMENGINE_FOUND
# RANDOMENGINE_INCLUDE_DIR
# RANDOMENGINE_LIBRARY
#
IF(WIN32)
    FIND_PATH(RANDOMENGINE_INCLUDE_DIR
            NAMES
                RandomEngine.hpp
            PATHS
                $ENV{PROGRAMFILES}/RANDOMENGINE
                ${RANDOMENGINE_ROOT_DIR}
                $ENV{RANDOMENGINE_ROOT_DIR}/include
                $ENV{RANDOMENGINE_ROOT_DIR}
                DOC "The directory where RandomEngine.hpp resides")
ELSE(WIN32)
    FIND_PATH(RANDOMENGINE_INCLUDE_DIR
            NAMES
                RandomEngine.hpp
            PATHS
                /usr/include
                /usr/local/include
                /sw/include
                /opt/local/include
                ${RANDOMENGINE_ROOT_DIR}
                $ENV{RANDOMENGINE_ROOT_DIR}/include
                $ENV{RANDOMENGINE_ROOT_DIR}
                DOC "The directory where RandomEngine.hpp resides"
            )
ENDIF(WIN32)

IF(WIN32)
find_library(RANDOMENGINE_LIBRARY
        NAMES
            RANDOMENGINE.a
        PATHS
            ${RANDOMENGINE_LOCATION}/lib
            DOC "The libRANDOMENGINE.a library")
ELSE(WIN32)
    find_library(RANDOMENGINE_LIBRARY
            NAMES
            libRANDOMENGINE.a
            PATHS
            ${RANDOMENGINE_LOCATION}/lib
            DOC "The libRANDOMENGINE.a library")

ENDIF(WIN32)

IF(RANDOMENGINE_INCLUDE_DIR)
    SET(RANDOMENGINE_FOUND "YES")
    MESSAGE(STATUS "Random Engine is ready to do random stuff")
ENDIF(RANDOMENGINE_INCLUDE_DIR)
