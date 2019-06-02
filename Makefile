all: builder
	docker run --rm -it -v $(shell pwd):/code -w /code opencv-wasm make build

builder:
	docker build -t opencv-wasm .

build: clean
	mkdir build
	cd build && emconfigure cmake ..
	cd build && emmake make

clean:
	rm -rf build
