# Makefile for building LaTeX documents
# Builds all .tex files into PDFs and cleans temporary files

# LaTeX compiler
LATEX := xelatex
LATEX_FLAGS := -interaction=nonstopmode -halt-on-error

# List of files to exclude from building
EXCLUDED_FILES := psyc1101-psychology-101/chapter_t.tex \
                  math2222-calculus-iii/chapter-13/chapter-13.tex \
                  math2100-foundations-of-mathematics/introduction.tex \
                  cpe3150-micro-embedded-design/lecture5.tex \
                  cs2200-theory-of-computer-science/lecture.tex \
                  cs2200-theory-of-computer-science/lecture5.tex

# Function to find all complete LaTeX documents
define find_tex_files
$(shell find . -name "*.tex" -type f -print0 | \
        xargs -0 grep -l '\\documentclass' 2>/dev/null | \
        grep -v -i -E "(macros|template)" | \
        grep -v " " | \
        grep -v -F $(foreach file,$(EXCLUDED_FILES),-e "$(file)"))
endef

# Find all buildable .tex files
TEX_FILES := $(call find_tex_files)
PDF_FILES := $(TEX_FILES:.tex=.pdf)

# Default target
.PHONY: build
build: $(PDF_FILES)
	@echo "TEX_FILES: $(words $(TEX_FILES)) files found"
	@echo "PDF_FILES: $(words $(PDF_FILES)) targets"

# Pattern rule for building PDFs from .tex files
%.pdf: %.tex
	@echo "Building $< -> $@"
	@cd $(dir $<) && $(LATEX) $(LATEX_FLAGS) $(notdir $<)
	@# Run twice for references
	@cd $(dir $<) && $(LATEX) $(LATEX_FLAGS) $(notdir $<) >/dev/null 2>&1 || true

# Clean temporary LaTeX files but keep PDFs
.PHONY: clean
clean:
	@echo "Cleaning temporary LaTeX files..."
	@find . -type f \( \
		-name "*.aux" -o \
		-name "*.log" -o \
		-name "*.out" -o \
		-name "*.toc" -o \
		-name "*.lof" -o \
		-name "*.lot" -o \
		-name "*.fls" -o \
		-name "*.fdb_latexmk" -o \
		-name "*.synctex.gz" -o \
		-name "*.nav" -o \
		-name "*.snm" -o \
		-name "*.vrb" -o \
		-name "*.bbl" -o \
		-name "*.blg" -o \
		-name "*.idx" -o \
		-name "*.ilg" -o \
		-name "*.ind" -o \
		-name "*.ent" -o \
		-name "*.bcf" -o \
		-name "*.run.xml" -o \
		-name "*.gz" -o \
		-name "*.glo" -o \
		-name "*.gls" -o \
		-name "*.glg" -o \
		-name "*.xdy" -o \
		-name "*.tdo" \
		\) -delete
	@echo "Clean complete."

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  build  - Build all .tex files into PDFs (default)"
	@echo "  clean  - Remove temporary LaTeX files (keeping PDFs)"
	@echo "  help   - Show this help message"
	@echo ""
	@echo "Exclusions:"
	@echo "  - Template and macro files"
	@echo "  - Files with spaces in paths"
	@echo "  - Files without \\documentclass"
	@echo "  - Specifically excluded files:"
	@$(foreach file,$(EXCLUDED_FILES),echo "    $(file)";)