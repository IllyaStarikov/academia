#!/bin/bash
#
# Build Parent Directory LaTeX Documents
# Finds and builds LaTeX documents from the parent src directory
#

echo "Building Parent Directory LaTeX Documents"
echo "========================================="

# Find all buildable LaTeX documents in parent directory
PARENT_TEX_FILES=$(find ../. -name "*.tex" -type f | grep -v "notes/" | xargs grep -l '\\documentclass' 2>/dev/null | grep -v " ")

echo "Found $(echo "$PARENT_TEX_FILES" | wc -l) buildable LaTeX documents in parent directory"

# Build each document
BUILT_COUNT=0
ERROR_COUNT=0

echo "$PARENT_TEX_FILES" | while IFS= read -r tex_file; do
    if [[ -n "$tex_file" ]]; then
        # Get directory and filename
        dir=$(dirname "$tex_file")
        filename=$(basename "$tex_file" .tex)
        pdf_file="$dir/$filename.pdf"
        
        echo "Processing: $tex_file"
        
        # Check if PDF already exists and is newer than TEX
        if [[ -f "$pdf_file" && "$pdf_file" -nt "$tex_file" ]]; then
            echo "  ✓ PDF already up to date: $pdf_file"
            continue
        fi
        
        # Build the document
        echo "  Building: $tex_file -> $pdf_file"
        cd "$dir" || continue
        
        # Try building with xelatex
        if xelatex -interaction=nonstopmode -halt-on-error "$filename.tex" >/dev/null 2>&1; then
            # Run twice for references
            xelatex -interaction=nonstopmode "$filename.tex" >/dev/null 2>&1 || true
            echo "  ✓ Built successfully: $pdf_file"
            BUILT_COUNT=$((BUILT_COUNT + 1))
        else
            echo "  ✗ Build failed: $tex_file"
            ERROR_COUNT=$((ERROR_COUNT + 1))
        fi
        
        # Return to notes directory
        cd - >/dev/null || exit 1
    fi
done

echo ""
echo "Build Summary:"
echo "  Built: $BUILT_COUNT documents"
echo "  Errors: $ERROR_COUNT documents"
echo ""
echo "Next step: Update master-portfolio.tex to include these documents"