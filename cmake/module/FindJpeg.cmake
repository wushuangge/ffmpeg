MESSAGE(STATUS "Using bundled FindTurboJpeg.cmake...")

FIND_PATH(LIB_JPEG_INCLUDE_DIR
        jpeglib.h
        "/usr/include/"
        "/usr/local/include/")

FIND_LIBRARY(LIB_JPEG_LIBRARIES
        NAMES jpeglib
        PATHS "/usr/lib/" "/usr/local/lib/")