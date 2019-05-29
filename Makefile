all:
	docker build -t opencv-wasm .

build: clean
	mkdir build
	cd build && emconfigure cmake ..
	cd build && emmake make

clean:
	rm -rf build
