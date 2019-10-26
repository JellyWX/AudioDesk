#!/bin/bash

# This script will create a virtual microphone for PulseAudio to use and set it as the default device.

# Delete existing virtual microphone
rm "~/.audiodesk/virtmic" -f

# Get the current default devices
DSRC=`python3 scripts/python/get_default_device.py sources`
DSNK=`python3 scripts/python/get_default_device.py sinks`

echo "Default input: ${DSRC}"
echo "Default output: ${DSNK}"

# Create a null sink that can be looped back into by the sources that require mixing
pactl load-module module-null-sink sink_name=audiodesk_mixer

# Loopback current default microphone into mixer
pactl load-module module-loopback source="$DSRC" sink=audiodesk_mixer

# Load the "module-pipe-source" module to read audio data from a FIFO special file.
echo "Creating virtual microphone."
pactl load-module module-pipe-source source_name=virtmic file=~/.audiodesk/virtmic format=s16le rate=36000 channels=1

# Loopback virtual microphone into mixer
pactl load-module module-loopback source=virtmic sink=audiodesk_mixer

# Temporarily set the virtmic as the default source device.
echo "Setting the mixer as the default device."
pactl set-default-source audiodesk_mixer.monitor

# Restore the default source device.
echo "Restoring the default source."
pactl set-default-sink "$DSNK"