all:
	make dependencies
	make core

dependencies:
	mvn dependency:go-offline

core:
	mvn -o clean compile assembly:single

clean:
	rm -rf ./target
