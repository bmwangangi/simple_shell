#!/bin/bash

# Get the maximum PID from /proc/sys/kernel/pid_max
MAX_PID=$(cat /proc/sys/kernel/pid_max)

echo "Maximum Process ID: $MAX_PID"

