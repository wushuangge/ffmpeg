#!/usr/bin/env pwsh

docker stop ffmpeg_python_cmake
docker rm ffmpeg_python_cmake
docker run -it --name ffmpeg_python_cmake -v ${pwd}:/opt/ffmpeg_python_cmake ubuntu:16.04 /bin/bash