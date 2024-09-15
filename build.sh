#!/usr/bin/env bash

debug=1
release=0
run=0
out='./build/bin/learnGL'
next_is_out=0
run_args=
add_args=0
next_is_compiler=0
CC=0
glfw=0
main="src/main.c"

# check args
for var in "$@"; do
    if [ $var == "release" ]; then
        debug=0
        release=1
        echo "[release mode]"
    elif [ $var == "run" ]; then
        run=1
    elif [ $var == "cc" ]; then
        next_is_compiler=1
    elif [ $var == "-o" ]; then
        next_is_out=1
    elif [ $var == "glfw" ]; then
        glfw=1
        main="src/glfw-main.c"
    elif [ $var == "--" ]; then
        add_args=1
    fi

    if [[ $next_is_compiler == 1 ]]; then
        CC=$var
        next_is_compiler=0
    fi

    if [[ $next_is_out == 1 ]]; then
        out=$var
        next_is_out=0
    fi

    if [[ $add_args == 1 ]]; then
        run_args="$run_args $var"
    fi
done

compiler_specific_flags=''
if [[ $CC == 0 ]]; then
    if command -v zig &> /dev/null; then
        CC='zig cc'
        compiler_specific_flags='-std=c23 -DZIG_CC'
    elif command -v clang &> /dev/null; then
        CC=clang
        compiler_specific_flags='-std=c23'
    elif command -v gcc &> /dev/null; then
        CC=gcc
        compiler_specific_flags='-std=c2x'
    fi
else
    if [ $CC == "clang" ]; then
        compiler_specific_flags='-std=c23'
    elif [ $CC == "gcc" ]; then
        compiler_specific_flags='-std=c2x'
    elif [ $CC == "zig cc" ]; then
        compiler_specific_flags='-std=c2x'
    fi
fi

# gen_flags="$compiler_specific_flags -Wall -Wextra -lGL -lX11 -lXi -lpthread -ldl -D_GLFW_X11"
gen_flags="$compiler_specific_flags -lc -lGL -lX11 -lXi -lpthread -ldl -lm -lXrandr"
if [[ $glfw == 1 ]]; then
    gen_flags="$gen_flags -D_GLFW_X11 -lrt -D_GNU_SOURCE -DGL_SILENCE_DEPRECATION=199309L -fno-sanitize=undefined" # https://github.com/raysan5/raylib/issues/3674
fi

debug_flags='-g -D_debug'
release_flags='-Drelease -O3'

compile="$CC $gen_flags"
if [[ $debug == 1 ]]; then
    echo "[debug mode]"
    echo -e "  compiler: $CC"
    compile="$compile $debug_flags"
else
    compile="$compile $release_flags"
fi

built=0

$compile $main -o $out && built=1

if [[ $run == 1 ]] && [[ $built == 1 ]]; then
    $out $run_args
fi
