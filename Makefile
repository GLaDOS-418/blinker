export PROJECT_NAME=blinker

.PHONY: build clean rebuild test testprint deps run

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

run: check_project_name check_project_exists
	./build/${PROJECT_NAME}

check_project_name:
	@if [ -z "${PROJECT_NAME}" ]; then \
		echo "Error: PROJECT_NAME is empty. Set a valid project name."; \
		exit 1; \
	fi
check_project_exists:
	@if [ ! -e ./build/${PROJECT_NAME} ]; then \
		echo "Error: ${PROJECT_NAME} executable not found. Run 'make build' first."; \
		exit 1; \
	fi
