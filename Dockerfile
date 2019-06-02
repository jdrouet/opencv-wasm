FROM trzeci/emscripten

ARG OPENCV_VERSION=4.1.0

RUN mkdir -p /third-party \
  && wget \
    -c https://github.com/opencv/opencv/archive/$OPENCV_VERSION.tar.gz \
    -O /third-party/opencv-$OPENCV_VERSION.tar.gz \
  && tar \
    -C /third-party/ \
    -xvf /third-party/opencv-$OPENCV_VERSION.tar.gz \
  && mv /third-party/opencv-$OPENCV_VERSION /third-party/opencv \
  && rm /third-party/opencv-$OPENCV_VERSION.tar.gz

WORKDIR /third-party/opencv
RUN python ./platforms/js/build_js.py build_wasm --build_wasm
