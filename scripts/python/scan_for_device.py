#!/usr/bin/env python3

from subprocess import Popen, PIPE
from sys import argv
import re

def scan_for_device():
    process = Popen(["pacmd", "list-sources"], stdout=PIPE, encoding="utf-8")
    r = re.compile('^\\s+name: <(.*)>')

    for line in process.stdout:
        matches = r.match(line)
        if matches is not None and matches.groups()[0] == argv[1]:
            return 1

    return 0

print(scan_for_device())