INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_SDR sdr)

FIND_PATH(
    SDR_INCLUDE_DIRS
    NAMES sdr/api.h
    HINTS $ENV{SDR_DIR}/include
        ${PC_SDR_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    SDR_LIBRARIES
    NAMES gnuradio-sdr
    HINTS $ENV{SDR_DIR}/lib
        ${PC_SDR_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDR DEFAULT_MSG SDR_LIBRARIES SDR_INCLUDE_DIRS)
MARK_AS_ADVANCED(SDR_LIBRARIES SDR_INCLUDE_DIRS)

