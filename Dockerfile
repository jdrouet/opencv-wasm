FROM trzeci/emscripten

ARG OPENCV_VERSION=master

RUN mkdir -p /third-party \
  && wget \
    -c https://github.com/opencv/opencv/archive/$OPENCV_VERSION.zip \
    -O /third-party/opencv-$OPENCV_VERSION.zip \
  && unzip \
    /third-party/opencv-$OPENCV_VERSION.zip \
    -d /third-party/ \
  && mv /third-party/opencv-$OPENCV_VERSION /third-party/opencv \
  && rm /third-party/opencv-$OPENCV_VERSION.zip

WORKDIR /third-party/opencv
RUN python ./platforms/js/build_js.py build_wasm --build_wasm

COPY . /code
WORKDIR /code
RUN make build
