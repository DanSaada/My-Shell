#!/bin/bash
# Dan Saada 208968560



# Check if there are enough parameters
if [ $# -lt 2 ] || [ "$3" == "-r" -a $# -lt 3 ]; then
  echo "Not enough parameters"
  exit 1
fi


folder_path=$1
word=$2

# Making an option to pass zero as current directory
if [ "$1" == "0" ]; then
   folder_path=./
fi

# Check if the -r flag was provided
recursive=0
if [ "$3" == "-r" ]; then
  recursive=1
fi

# Function to compile C files in a directory
function compile_directory {
  local dir_path=$1
  local search_word=$2

  # Remove all compiled files in the folder
  rm -f "$dir_path"/*.out

  # Compile only C files containing the given word
  for file in "$dir_path"/*.c; do
    if grep -iq "$search_word" "$file"; then
      gcc -w -o "${file%.*}.out" "$file"
    fi
  done
}

# Function to search for C files recursively
# Function to search for C files recursively
function search_recursive {
  local current_dir=$1
  local current_word=$2

  # Only search the directory if it contains C files
  if ls "$current_dir"/*.c 1>/dev/null 2>&1; then
    compile_directory "$current_dir" "$current_word"
  fi

  # Recursively call itself for each subdirectory
  for subdir in "$current_dir"/*/; do
    if [ -d "$subdir" ]; then
      (
        search_recursive "$subdir" "$current_word"
      )
    fi
  done
  
  cd ..
}


# If the script was called from outside the folder, cd to the script's directory
if [ $0 != "./$0" ]; then
  cd "$(dirname "$0")"
fi

if [ $recursive -eq 1 ]; then
  search_recursive "$folder_path" "$word"
else
  compile_directory "$folder_path" "$word"
fi


