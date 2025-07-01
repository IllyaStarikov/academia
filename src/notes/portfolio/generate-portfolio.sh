#!/bin/bash
#
# Generate Master Portfolio - Auto-discovery script
# Automatically finds PDFs and generates LaTeX includes for master-portfolio.tex
#

echo "Academic Portfolio Generator"
echo "Discovering academic documents..."

# Find all PDF files, excluding the master portfolio itself
PDFS=$(find . -name "*.pdf" -type f | grep -v "master-portfolio.pdf" | sort)

# Count files
PDF_COUNT=$(echo "$PDFS" | grep -c "pdf")
echo "Found $PDF_COUNT PDF documents"

# Create auto-generated includes file
cat > portfolio-includes.tex << EOF
% Auto-generated includes for master portfolio
% Generated on $(date)
% Found $PDF_COUNT PDF documents

EOF

echo "Generating course sections..."

# Function to get course category
get_category() {
    local path="$1"
    case "$path" in
        ./cs1*|./cs2*|./cs3*|./cs4*|./cs5*) echo "Computer Science" ;;
        ./math*) echo "Mathematics" ;;
        ./phys*) echo "Physics" ;;
        ./cpe*) echo "Computer Engineering" ;;
        ./phil*) echo "Philosophy" ;;
        ./psyc*) echo "Psychology" ;;
        ./stat*) echo "Statistics" ;;
        ./teach*) echo "Teaching Materials" ;;
        *) echo "Other" ;;
    esac
}

# Function to clean up title
clean_title() {
    local filename="$1"
    echo "$filename" | sed 's/-/ /g' | sed 's/_/ /g' | sed 's/\.pdf$//' | \
    awk '{for(i=1;i<=NF;i++) $i=toupper(substr($i,1,1)) tolower(substr($i,2));}1'
}

# Generate by directory structure
current_category=""
current_course=""

echo "$PDFS" | while IFS= read -r pdf; do
    if [[ -n "$pdf" ]]; then
        # Extract directory path
        dir=$(dirname "$pdf")
        course=$(echo "$dir" | cut -d'/' -f2)
        category=$(get_category "$dir")
        
        # Clean up course name
        course_name=$(echo "$course" | sed 's/-/ - /g' | tr '[:lower:]' '[:upper:]')
        
        # Get document title
        filename=$(basename "$pdf")
        title=$(clean_title "$filename")
        
        echo "Processing: $course -> $title"
    fi
done

# Generate a simpler structure
cat > portfolio-includes.tex << 'EOF'
% Auto-generated includes for master portfolio

\chapter{Computer Science Courses}

\section*{CS 1510 - Data Structures}
EOF

# Add specific includes for major documents
echo "$PDFS" | grep "cs1510" | while IFS= read -r pdf; do
    if [[ -n "$pdf" ]]; then
        filename=$(basename "$pdf" .pdf)
        title=$(echo "$filename" | sed 's/-/ /g' | sed 's/_/ /g' | awk '{for(i=1;i<=NF;i++) $i=toupper(substr($i,1,1)) tolower(substr($i,2));}1')
        echo "\\includepdfdoc{$title}{$pdf}" >> portfolio-includes.tex
    fi
done

cat >> portfolio-includes.tex << 'EOF'

\section*{CS 3800 - Operating Systems}
EOF

echo "$PDFS" | grep "cs3800" | while IFS= read -r pdf; do
    if [[ -n "$pdf" ]]; then
        filename=$(basename "$pdf" .pdf)
        title=$(echo "$filename" | sed 's/-/ /g' | sed 's/_/ /g' | awk '{for(i=1;i<=NF;i++) $i=toupper(substr($i,1,1)) tolower(substr($i,2));}1')
        echo "\\includepdfdoc{$title}{$pdf}" >> portfolio-includes.tex
    fi
done

cat >> portfolio-includes.tex << 'EOF'

\chapter{Mathematics}

\section*{Mathematics Courses}
EOF

echo "$PDFS" | grep "math" | head -10 | while IFS= read -r pdf; do
    if [[ -n "$pdf" ]]; then
        filename=$(basename "$pdf" .pdf)
        title=$(echo "$filename" | sed 's/-/ /g' | sed 's/_/ /g' | awk '{for(i=1;i<=NF;i++) $i=toupper(substr($i,1,1)) tolower(substr($i,2));}1')
        echo "\\includepdfdoc{$title}{$pdf}" >> portfolio-includes.tex
    fi
done

echo ""
echo "Portfolio generation complete!"
echo "Files generated:"
echo "  - portfolio-includes.tex (auto-generated includes)"
echo ""
echo "To build the master portfolio:"
echo "  make portfolio"