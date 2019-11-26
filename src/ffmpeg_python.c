#include "./ffmpeg_python.h"

static Video2ImageStream vis;

/**
 * 初始化摄像头
 * 连接摄像头地址，并获取视频流数据
 **/
int init(char *input_filename, bool nobuffer, bool use_gpu, bool use_tcp, int timeout, int *width, int *height) {
    av_log_set_level(AV_LOG_INFO);
    av_log(NULL, AV_LOG_DEBUG, "url %s\n", input_filename);

    // 获取视频流数据，将其存在全局变量中
    vis = open_inputfile(input_filename, nobuffer, use_gpu, use_tcp, timeout);

    if (vis.ret < 0) {
        // 处理错误信息
        av_log(NULL, AV_LOG_ERROR, "init error: %s \n", vis.error_message);
    } else {
        *width = vis.video_codec_context->width;
        *height = vis.video_codec_context->height;
    }

    return vis.ret;
}

/**
 * 视频流取图片数据
 **/
unsigned char *getImageBuffer(int chose_frames, int type, int quality, long *size, int *error) {

    // 处理图片
    if (vis.ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "initReadingVideo method should be invoke first \n");
        *error = -30;
        return NULL;
    }

    FrameData frameData = video2images_stream(vis, quality, chose_frames, type);

    if (frameData.ret == 0 && frameData.file_size == 0) {
        av_log(NULL, AV_LOG_ERROR, "data null ....");
        *error = -6;
        *size = 0;
        return frameData.file_data;
    }

    av_log(NULL, AV_LOG_DEBUG, "result data size: %lu \n", frameData.file_size);

    *size = frameData.file_size;
    *error = frameData.ret;

    return frameData.file_data;
}

void freeImageBuffer(uint8_t *file_data) {
    if (file_data != NULL) {
        av_log(NULL, AV_LOG_DEBUG, "file_data is not null \n");
        usleep(0);
        av_freep(&file_data);
        free(file_data);
        file_data = NULL;
    }
}

/**
 * 释放视频连接
 **/
void destroy() {
    release(vis.video_codec_context, vis.format_context);
    Video2ImageStream _vis = {
        .format_context = NULL,
        .video_stream_idx = -1,
        .video_codec_context = NULL,
        .ret = -1
        };

    vis = _vis;
}

/**
 * rtsp视频录频
 **/
void record(char *input_filename, char *output_filename, int record_seconds, bool use_gpu) {
    int result = record_rtsp(input_filename, output_filename, record_seconds, use_gpu);
    av_log(NULL, AV_LOG_DEBUG, "record rtsp result : %d\n", result);
}
