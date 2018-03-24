# Please do not change this file - the build may fail if you do

all: dependencies core

dependencies:
ifeq (,$(wildcard ./build/CMakeCache.txt))
	@mkdir build || true
	@cd build && cmake .. -DCMAKE_BUILD_TYPE:STRING=RelWithDebInfo
endif

core:
	@cmake --build build/

clean:
	@rm -rf build
