#include <algorithm>
#include "resizer.hpp"

int roundThis(double value) {
  return static_cast <int> (std::floor(value));
}

Resizer::Resizer(cv::Mat input) {
  this->input = input;
}

void Resizer::run() {
  const cv::_InputArray inputArray(this->input);
  cv::Size srcSize = inputArray.size();
  cv::UMat src(inputArray.getUMat());

  double ratio = std::min(SMALL_SIZE / srcSize.width, SMALL_SIZE / srcSize.height);
  int height = roundThis(ratio * srcSize.height);
  int width = roundThis(ratio * srcSize.width);
  const cv::Size dstSize(width, height);

  cv::UMat dst(dstSize, this->input.type());
  cv::resize(src, dst, dstSize, 0, 0, cv::INTER_CUBIC);
}
