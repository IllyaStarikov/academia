#!/bin/bash

# Check if src directory exists
if [ ! -d "./src" ]; then
    echo "Error: ./src directory not found"
    exit 1
fi

# Iterate through each subdirectory in src/
for dir in ./src/*/; do
    # Check if it's actually a directory
    if [ -d "$dir" ]; then
        # Extract just the directory name (remove ./src/ prefix and trailing /)
        subdir_name=$(basename "$dir")
        
        # Add all contents of the subdirectory
        git add "$dir"*
        
        # Check if there are any changes to commit
        if git diff --cached --quiet; then
            echo "No changes to commit in $subdir_name"
        else
            # Commit with the message "Add <subdir>"
            git commit -m "Add $subdir_name"
            echo "Committed: Add $subdir_name"
        fi
    fi
done

