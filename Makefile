.PHONY: build clean rebuild test testout

build:
	./project_build.sh
clean:
	/bin/rm -r build/
rebuild: clean build
	echo "rebuilding..."
test:
	cd ./build && ctest -C Debug && cd ..
testprint:
	cd ./build && ctest --rerun-failed --output-on-failure -C Debug && cd ..
deps:
	# export CC=gcc && \
	# export CXX=g++ && \
	conan install . --output-folder=./build --build=missing --profile default
