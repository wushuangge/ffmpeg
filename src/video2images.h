#ifndef FFMPEG_PYTHON_VIDEO2IMAGES_H
#define FFMPEG_PYTHON_VIDEO2IMAGES_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libavutil/pixfmt.h>

#include <jpeglib.h>

#include "./common.c"

typedef struct Video2ImageStream {
    AVFormatContext *format_context;
    AVStream *video_stream;
    int video_stream_idx;
    AVCodecContext *video_codec_context;
    int ret;
    char *error_message;
    int frame_rate;
} Video2ImageStream;

enum ImageStreamType {
    YUV = 0,
    RGB,
    JPEG
};

typedef struct FrameData {
    unsigned long file_size;
    unsigned char *file_data;
    int ret;
    char *error_message;
} FrameData;

enum FrameStatus {
    START = 0,
    END = 1,
    GRAB = 2,
    PENDIING = 3
};

typedef struct FrameTimeOut {
    time_t count_time;
    time_t grab_time;
    int status;
} FrameTimeOut;

Video2ImageStream open_inputfile(const char *filename, const bool nobuffer, const bool use_gpu, const bool use_tcp, const int timeout);

int init_filters(const char *filters_descr, AVCodecContext *dec_ctx, AVRational time_base,
                    AVFilterContext *buffersink_ctx, AVFilterContext *buffersrc_ctx);

FrameData video2images_stream(Video2ImageStream vis, int quality, int chose_frames, enum ImageStreamType type);

void release(AVCodecContext *video_codec_context, AVFormatContext *format_context);

#endif // FFMPEG_PYTHON_VIDEO2IMAGES_H
