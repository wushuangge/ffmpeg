#!/usr/bin/env python3

from ctypes import *

import pdb

ffmpegPython = cdll.LoadLibrary('./linux-build-cmake-make/ffmpeg-python.so')

rtspUrl = "rtsp://admin:123456@192.168.1.65:554/h264/ch1/main/av_stream"
# rtspUrl = "file://opt/ffmpeg_python_cmake/test2.mp4"

width = c_int()
pwidth = pointer(width)
height = c_int()
pheight = pointer(height)

# char *input_filename, bool nobuffer, bool use_gpu, bool use_tcp, int timeout, [out] width, [out] height
ffmpegPython.init.argtypes = [c_char_p, c_bool, c_bool, c_bool, c_int, POINTER(c_int), POINTER(c_int)]
ffmpegPython.init.restype = c_int
initErr = ffmpegPython.init(rtspUrl.encode("utf8"), False, False, True, 2, pwidth, pheight)

print(width.value)
print(height.value)

print(initErr)
# initErr:
#       0:      success
#       -1      network init error
#       -2      couldn't open url
#       -3      has no video stream
#       -4      find video stream error
#       -5      find decoder error
#       -6      parse codec error
#       -7      malloc stream context error
#       -8      copy codec params error
#       -9      open codec error
#       -10     find video frame error

if (initErr == 0):
    # for i in range(20):
    i = 0

    size = c_ulong()
    psize = pointer(size)

    error = c_int()
    perror = pointer(error)

    # int chose_frames, int type (YUV = 0, RGB = 1, JPEG = 2), int quality (JPEG; 1~100)
    ffmpegPython.getImageBuffer.argtypes = [c_int, c_int, c_int, POINTER(c_ulong), POINTER(c_int)]
    ffmpegPython.getImageBuffer.restype = c_void_p

    while (True):
        i += 1

        # if (i == 500):
        #     break

        pbuffer = ffmpegPython.getImageBuffer(25, 2, 100, psize, perror)

        print(error.value)
        # error:
        #       0:              success
        #       -1              malloc frame error
        #       -2              malloc packet error
        #       -3              has no video stream
        #       -4              decode packet error
        #       -5              decode frame error
        #       -6              data is null, network may be error
        #       -10 or -20      malloc new frame error
        #       -30             not init error

        if (error.value == 0):
            UINIT8_TYPE = c_uint8 * size.value

            tmp_buf = cast(pbuffer, POINTER(UINIT8_TYPE))

            t = "./tmp/images/test" + str(i) + ".jpg"

            # with open(t, 'wb') as target:
            #    target.write(tmp_buf.contents)

            ffmpegPython.freeImageBuffer(tmp_buf)

            del tmp_buf
            del pbuffer
        else:
            ffmpegPython.destroy()
            break

    ffmpegPython.destroy()
