#!/bin/bash

extensionsToDelete=(gz fls fdb_latexmk blg bbl log aux out nav toc snm)

# Compile The Tex Files
for file in *.tex; do
    pdflatex $file batchmode >/dev/null
    echo "$file Compile Successful"
done

# Present The Files
for PDF in *.pdf; do
    open $PDF &
done

wait # Wait all are compiled before presenting pdfs

# Delete Garbage Files
for file in *; do
    filename=$(basename "$file")
    extension="${filename##*.}"
    filename="${filename%.*}"

    for badExtensions in "${extensionsToDelete[@]}" ; do
        if [[ $badExtensions = $extension ]]; then
            rm $file
            echo "$file Deleted"
        fi
    done
done