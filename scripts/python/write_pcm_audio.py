#!/usr/bin/env python3

from sys import argv

def write_pcm(path: str, location):
    f = open(path, 'rb')

    bits = f.read(2)

    frames = []

    while bits:
        frames.append(bits)

        bits = f.read(2)

    f.close()

    for frame in frames:
        location.write(frame)


def write_to_sink(audio: str, path_sink: str):
    f = open(path_sink, 'wb')

    write_pcm(audio, f)

    f.close()

write_to_sink(argv[1], argv[2])