#!/bin/bash

_target="all"
_build_dir="manual_build"
_debug=""

function print_popconda_helper_msg(){
cat <<"EOF"
usage:
    for example:
        $ build_and_run -t 2_sum -- 3 4

    -h, --help: print helpful message

    -t, --target: choose build target and run target

    -g, --debug: add debug info to programme.

EOF
}


function parse_args_from_console() {
    local prompt_str=$1

    while [ "$1" != "--" ] && [[ $# -gt 0 ]]; do
        case $1 in
            -t | --target)          shift
                                    _target=$1
                                    ;;
            -g | --debug)           shift
                                    _debug="True"
                                    ;;
            -h | --help)            print_popconda_helper_msg
                                    exit 0
                                    ;;
            *)                      print_popconda_helper_msg
                                    exit 0
                                    ;;
        esac
        shift
    done
    shift
    _ARGUMENT=$@
}

parse_args_from_console $@

rm -rf ${_build_dir}
mkdir -p ${_build_dir}

if [[ ${_debug} == "True" ]];then
  cmake -S `pwd` -B ${_build_dir} -DCMAKE_BUILD_TYPE=Debug
else
  cmake -S `pwd` -B ${_build_dir}
fi

cmake --build ${_build_dir} --target ${_target} || exit 1

if [[ $_target != "all" ]]; then
  `pwd`/${_build_dir}/${_target}/${_target} ${_ARGUMENT}
fi
