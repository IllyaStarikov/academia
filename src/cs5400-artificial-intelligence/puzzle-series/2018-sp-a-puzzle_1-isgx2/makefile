run:
	python3 src/main.py ${ARGS}

production:
	python3 -O src/main.py ${ARGS}

test:
	flake8 src/*.py --ignore=E501
	coverage run --source=src -m unittest discover -s tests/
	coverage report -m

.PHONY: clean
clean:
	-@rm -rf src/*.pyc tests/*.pyc
	-@rm -rf src/__pycache__ tests/__pycache__
	-@rm -rf log
