# Makefile for building LaTeX documents
# Builds all .tex files into PDFs and cleans temporary files

# LaTeX compiler
LATEX := xelatex
LATEX_FLAGS := -interaction=nonstopmode -shell-escape

# List of files to exclude from building
EXCLUDED_FILES := psyc1101-psychology-101/chapter_t.tex \
                  portfolio/math2222-calculus-iii/chapter-13/chapter-13.tex \
                  math2222-calculus-iii/chapter-13/chapter-13.tex \
                  portfolio/math2100-foundations-of-mathematics/introduction.tex \
                  math2100-foundations-of-mathematics/introduction.tex \
                  cpe3150-micro-embedded-design/lecture5.tex \
                  cs2200-theory-of-computer-science/lecture.tex \
                  cs2200-theory-of-computer-science/lecture5.tex \
                  cs3800-operating-systems/exams/exam-1/cheatsheet.tex \
                  math2222-calculus-iii/master.tex

# Function to find all complete LaTeX documents
define find_tex_files
$(shell find . portfolio/ -name "*.tex" -type f -print0 | \
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

# Force rebuild all documents
.PHONY: rebuild
rebuild: clean-pdfs build

# Count target - just show statistics without building
.PHONY: count
count:
	@echo "TEX_FILES: $(words $(TEX_FILES)) files found"
	@echo "PDF_FILES: $(words $(PDF_FILES)) targets"

# Pattern rule for building PDFs from .tex files
%.pdf: %.tex
	@echo "Building $< -> $@"
	@cd $(dir $<) && $(LATEX) $(LATEX_FLAGS) $(notdir $<) || echo "Warning: $< failed to compile"
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

# Clean PDFs to force rebuild
.PHONY: clean-pdfs
clean-pdfs:
	@echo "Removing all generated PDFs..."
	@find . -name "*.pdf" -not -path "./portfolio/joe-miner.png" -delete
	@echo "PDFs removed."

# Master portfolio target
.PHONY: portfolio
portfolio: master-portfolio.pdf

# Force rebuild portfolio
.PHONY: portfolio-rebuild
portfolio-rebuild:
	@echo "Force rebuilding portfolio..."
	@rm -f portfolio/master-portfolio.pdf master-portfolio.pdf
	@$(MAKE) rebuild
	@$(MAKE) portfolio

master-portfolio.pdf: portfolio/master-portfolio.tex $(PDF_FILES)
	@echo "Building master academic portfolio..."
	@echo "All individual documents built: $(words $(PDF_FILES)) PDFs"
	@cd portfolio && $(LATEX) $(LATEX_FLAGS) master-portfolio.tex
	@cd portfolio && $(LATEX) $(LATEX_FLAGS) master-portfolio.tex >/dev/null 2>&1 || true
	@cp portfolio/master-portfolio.pdf .

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  build              - Build all .tex files into PDFs (default)"
	@echo "  rebuild            - Force rebuild all documents (cleans PDFs first)"
	@echo "  count              - Show file count without building"
	@echo "  portfolio          - Build master academic portfolio"
	@echo "  portfolio-rebuild  - Force rebuild entire portfolio from scratch"
	@echo "  clean              - Remove temporary LaTeX files (keeping PDFs)"
	@echo "  clean-pdfs         - Remove all generated PDFs"
	@echo "  help               - Show this help message"
	@echo ""
	@echo "Portfolio workflow:"
	@echo "  1. make count              # Check file discovery"
	@echo "  2. make portfolio-rebuild  # Force rebuild everything"
	@echo "  OR: make portfolio         # Build incrementally"
	@echo ""
	@echo "TEX_FILES: $(words $(TEX_FILES)) files found"