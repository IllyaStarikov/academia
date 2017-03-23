all: requirements.pdf

pdf: requirements.pdf

requirements.pdf: clean requirements.pdf
	pdflatex requirements
	makeglossaries requirements
	pdflatex requirements

clean:
	-@rm -f *.aux
	-@rm -f *.bbl
	-@rm -f *.blg
	-@rm -f *.brf
	-@rm -f *.dvi
	-@rm -f *.glg
	-@rm -f *.glo
	-@rm -f *.gls
	-@rm -f *.idx
	-@rm -f *.ilg
	-@rm -f *.ind
	-@rm -f *.log
	-@rm -f *.out
	-@rm -f *.ps
	-@rm -f *.toc
	-@rm -f *.xdy
	-@rm -f requirements.pdf
