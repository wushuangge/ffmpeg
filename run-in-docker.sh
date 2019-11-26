#!/usr/bin/env bash

docker stop ffmpeg_python_cmake
docker rm ffmpeg_python_cmake
docker run -it --name ffmpeg_python_cmake --runtime=nvidia -e NVIDIA_DRIVER_CAPABILITIES=compute,utility,video -v "$(pwd)":/opt/ffmpeg_python_cmake truthbean/ffmpeg-node-docker:4.1-10-cuda9.2-ubuntu16-X /bin/bash