#!/bin/bash

ffmpeg -re -i "$1" -f s16le -ar 36000 -ac 1 -filter:a "volume=$2" - > ~/.audiodesk/virtmic
