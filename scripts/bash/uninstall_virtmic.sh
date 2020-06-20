#!/bin/bash

# Uninstall the virtual microphone.

pactl unload-module module-pipe-source
pactl unload-module module-loopback
pactl unload-module module-null-sink

# Restart for changes to take effect

pulseaudio --kill
pulseaudio --start
