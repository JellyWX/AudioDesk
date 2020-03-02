#!/bin/bash

ffplay -loglevel panic "$1" -autoexit -nodisp -volume "$2"
