#!/bin/bash
if [ $# -eq 0 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi
filename=$1
if [ ! -f "$filename" ]; then
    echo "File '$filename' not found."
    exit 1
fi
base_name=$(basename -- "$filename")
base_name_no_ext="${base_name%.*}"
gcc -o "./bin/$base_name_no_ext" "$filename"

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

shift

# Run the compiled program
./bin/"$base_name_no_ext" "$@"
