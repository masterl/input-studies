#!/bin/bash

readonly PROJECT_ROOT=$( cd "$( dirname "$0" )" && pwd )
readonly FILE_PATH="$1"

readonly FILE_DIR=$(dirname $FILE_PATH)

readonly EXECUTABLE="$FILE_DIR/program.bin"

readonly COMPILE_COMMAND="g++ -Wall -std=c++14 $FILE_PATH -o $EXECUTABLE"

readonly GIT_STATUS_COMMAND="git status"
readonly PRINT_LINE="echo \\\"==================================================\\\""

entr_command="entr -d sh -c \""
entr_command="$entr_command tput reset;"
entr_command="$entr_command echo \\\"Compiling...\\\";"
entr_command="$entr_command $PRINT_LINE;"
entr_command="$entr_command $COMPILE_COMMAND;"
entr_command="$entr_command echo; $PRINT_LINE;"
entr_command="$entr_command echo \\\"Running GIT Status...\\\";"
entr_command="$entr_command $PRINT_LINE;"
entr_command="$entr_command $GIT_STATUS_COMMAND;"
entr_command="$entr_command echo;"
entr_command="$entr_command date;"
entr_command="$entr_command\""

readonly FULL_COMMAND_STRING="echo $FILE_PATH | $entr_command"

while true; do
  eval "$FULL_COMMAND_STRING"
done
