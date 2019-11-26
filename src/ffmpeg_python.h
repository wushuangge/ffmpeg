#ifndef FFMPEG_PYTHON_H
#define FFMPEG_PYTHON_H

#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./common.h"
#include "./video2images.c"
#include "./record_rtsp.c"

int init(char *input_filename, bool nobuffer, bool use_gpu, bool use_tcp, int timeout, int *width, int *height);

unsigned char *getImageBuffer(int chose_frames, int type, int quality, long *size, int *error);

void freeImageBuffer(uint8_t *file_data);

void destroy();

void record(char *input_filename, char *output_filename, int record_seconds, bool use_gpu);

#endif // FFMPEG_PYTHON_H

