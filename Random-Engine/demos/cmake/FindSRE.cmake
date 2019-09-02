#

# Try to find SimpleRenderEngine library and include path.
# Once done this will define
#
# SRE_FOUND
# SRE_INCLUDE_DIR
# SRE_LIBRARY
#
IF(WIN32)
    FIND_PATH( SRE_INCLUDE_DIR
            NAMES
                SRE/SimpleRenderEngine.hpp
            PATHS
                $ENV{PROGRAMFILES}/SRE
                ${SRE_ROOT_DIR}
                $ENV{SRE_ROOT_DIR}/include
                $ENV{SRE_ROOT_DIR}
                DOC "The directory where SRE/SimpleRenderEngine.hpp resides")
ELSE(WIN32)
    FIND_PATH( SRE_INCLUDE_DIR
            NAMES
                SRE/SimpleRenderEngine.hpp
            PATHS
                /usr/include
                /usr/local/include
                /sw/include
                /opt/local/include
                ${SRE_ROOT_DIR}
                $ENV{SRE_ROOT_DIR}/include
                $ENV{SRE_ROOT_DIR}
                DOC "The directory where SRE/SimpleRenderEngine.hpp resides"
            )
ENDIF(WIN32)

IF(WIN32)
find_library( SRE_LIBRARY
        NAMES
            SRE.a
        PATHS
            ${SRE_LOCATION}/lib
            DOC "The libSRE.a library")
ELSE(WIN32)
    find_library( SRE_LIBRARY
            NAMES
            libSRE.a
            PATHS
            ${SRE_LOCATION}/lib
            DOC "The libSRE.a library")

ENDIF(WIN32)

IF(SRE_INCLUDE_DIR)
    SET(SRE_FOUND "YES")
    MESSAGE(STATUS "Found SRE.")
ENDIF(SRE_INCLUDE_DIR)
