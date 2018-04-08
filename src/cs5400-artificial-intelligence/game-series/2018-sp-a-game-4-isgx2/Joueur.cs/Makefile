
all:
	make dependencies
	make core

dependencies: ;

core:
	dotnet restore
	dotnet build -o build

clean:
	rm -rf build/ obj/ packages/ bin/
