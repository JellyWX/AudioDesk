#!/usr/bin/env python3

from subprocess import Popen, PIPE
from sys import argv

def get_default_microphone():
    process = Popen(["pacmd", "list-" + argv[1]], stdout=PIPE, encoding="utf-8")

    in_default: bool = False

    for line in process.stdout:
        l = line.strip()

        if len(l) > 0 and l[0] == '*':
            in_default = True

        elif in_default:
            return parse_line(line)

def parse_line(line: str):
    return line.split(':')[1].strip()[1:-1]

print(get_default_microphone())