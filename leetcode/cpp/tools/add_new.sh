#!/bin/bash

function print_helper_msg(){
cat <<"EOF"
usage:
    for example:
        $ bash add_new.sh -t LinkedListMultiThreadTest -tmp LinkedList -s multithread

    -h, --help: print helpful message

    -t, --target: The target name.

    -tmp, --template: Choose the template you use. 
                      "LinkedList" or "BinaryTree". 
                      you can find dir name in `temp` dir.

    -s, --subdirectory: Specify the subdirectory where you create the target.

EOF
}


function parse_args_from_console() {
    local prompt_str=$1

    while [ "$1" != "--" ] && [[ $# -gt 0 ]]; do
        case $1 in
            -t | --target)          shift
                                    _target=$1
                                    ;;
            -tmp | --template)      shift
                                    _template=$1
                                    ;;
            -s | --subdirectory)    shift
                                    _subdirectory=$1
                                    ;;
            -h | --help)            print_helper_msg
                                    exit 0
                                    ;;
            *)                      print_helper_msg
                                    exit 0
                                    ;;
        esac
        shift
    done
    shift
    _ARGUMENT=$@
}

parse_args_from_console $@

_target=${_target:-""}
_template=${_template:-"template"}
_subdirectory=${_subdirectory:-""}

if [[ -z ${_target} ]]; then
  echo "target should not be empty."
  exit 1
fi

if [[ -d ${_subdirectory} ]]; then
  _real_target="${_subdirectory}/${_target}"
else
  _real_target=${_target}
fi

if [[ -d ${_real_target} ]]; then
  echo "The ${_real_target} already exsist."
  exit 1
fi

cp -R temp/$_template ${_real_target}

if [[ $OSTYPE == 'darwin'* ]] ;then
  sed -i '' "1 s/^.*$/set(TARGET ${_target})/" "${_real_target}/CMakeLists.txt"
else
  sed -i "1 s/^.*$/set(TARGET ${_target})/" "${_real_target}/CMakeLists.txt"
fi

if [[ ! -d ${_subdirectory} ]];then
  echo "add_subdirectory(${_target})" >> CMakeLists.txt
else
  echo "add_subdirectory(${_target})" >> "${_subdirectory}/CMakeLists.txt"
fi
