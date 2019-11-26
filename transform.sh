#!/usr/bin/env bash

declare -r tmpImagesDir="./tmp/images"
for file_name in ${tmpImagesDir}/*.yuv
do  
    ffmpeg -pix_fmt yuvj420p -s 3072x2048 -i $file_name $file_name.%05d.jpg
done

for file_name in ${tmpImagesDir}/*.rgb
do  
    ffmpeg -pix_fmt rgb24 -s 3072x2048 -i $file_name $file_name.%05d.jpg
done
