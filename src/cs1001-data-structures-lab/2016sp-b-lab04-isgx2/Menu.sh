#!/bin/bash
mainMenu() {
    echo "v) View file"
    echo "e) Edit file"
    echo "c) Compile file"
    echo "x) Execute file"
    echo "q) Quit"

    input=""
    while [[ $input != "q" ]]; do
            read input
            case $input in
                v)
                    less "$1"
                    ;;
                e)
                    vim "$1"
                    ;;
                c)
                    g++ "$1" -o build
                    ;;
                x)
                    "./build"
                    ;;
                q)
                    break
                    ;;

                *)
                    echo "Error, Invalid Argument"
                    ;;
        esac
        done
}

if [[ -e $1 ]]; then
    for arg in "$@"; do
        mainMenu $arg
    done
else
    for file in *; do
        mainMenu $file
    done
fi