#!/bin/bash

_target="all"
_build_dir="manual_build"

function print_popconda_helper_msg(){
cat <<"EOF"
usage:
    for example:
        $ build_and_run -t 2_sum -- 3 4

    -h, --help: print helpful message

    -t, --target: choose build target and run target

EOF
}


function parse_args_from_console() {
    local prompt_str=$1

    while [ "$1" != "--" ] && [[ $# -gt 0 ]]; do
        case $1 in
            -t | --target)          shift
                                    _target=$1
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

cmake -S `pwd` -B ${_build_dir}
cmake --build ${_build_dir} --target ${_target} || exit 1

if [[ $_target != "all" ]]; then
  `pwd`/${_build_dir}/${_target}/${_target} ${_ARGUMENT}
fi
