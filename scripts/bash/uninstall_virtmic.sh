#!/bin/bash

# Uninstall the virtual microphone.

pactl unload-module module-pipe-source
pactl unload-module module-loopback
pactl unload-module module-null-sink

pulseaudio --kill
pulseaudio --start