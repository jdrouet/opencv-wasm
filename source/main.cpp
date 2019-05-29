#include <emscripten/bind.h>

#include "opencv2/core.hpp"
#include "opencv2/core/base.hpp"
#include "opencv2/core/fast_math.hpp"
#include "opencv2/core/bindings_utils.hpp"
#include "opencv2/core/check.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/optim.hpp"
#include "opencv2/core/ovx.hpp"
#include "opencv2/core/persistence.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/photo.hpp"
#include "opencv2/dnn/dict.hpp"
#include "opencv2/dnn/dnn.hpp"
#include "opencv2/dnn/utils/inference_engine.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/video/tracking.hpp"

namespace binding_utils
{
  template <typename T>
  emscripten::val matData(const cv::Mat &mat)
  {
    return emscripten::val(emscripten::memory_view<T>((mat.total() * mat.elemSize()) / sizeof(T), (T *)mat.data));
  }

  void resize_wrapper(const cv::Mat& arg1, cv::Mat& arg2, cv::Size arg3, double arg4, double arg5, int arg6) {
    return cv::resize(arg1, arg2, arg3, arg4, arg5, arg6);
  }
  
  void resize_wrapper_1(const cv::Mat& arg1, cv::Mat& arg2, cv::Size arg3, double arg4, double arg5) {
    return cv::resize(arg1, arg2, arg3, arg4, arg5);
  }
  
  void resize_wrapper_2(const cv::Mat& arg1, cv::Mat& arg2, cv::Size arg3, double arg4) {
    return cv::resize(arg1, arg2, arg3, arg4);
  }
  
  void resize_wrapper_3(const cv::Mat& arg1, cv::Mat& arg2, cv::Size arg3) {
    return cv::resize(arg1, arg2, arg3);
  }

  std::string getBuildInformation() {
    return cv::getBuildInformation();
  }
}

EMSCRIPTEN_BINDINGS(binding_utils)
{
  emscripten::class_<cv::Mat>("Mat")
    .constructor<int, int, int>()

    .property("rows", &cv::Mat::rows)
    .property("cols", &cv::Mat::cols)
    .property("data", &binding_utils::matData<unsigned char>)
    .property("data8S", &binding_utils::matData<char>)
    .property("data16U", &binding_utils::matData<unsigned short>)
    .property("data16S", &binding_utils::matData<short>)
    .property("data32S", &binding_utils::matData<int>)
    .property("data32F", &binding_utils::matData<float>)
    .property("data64F", &binding_utils::matData<double>);

  emscripten::function("getBuildInformation", &binding_utils::getBuildInformation);

  emscripten::function("resize", emscripten::select_overload<void(const cv::Mat&, cv::Mat&, cv::Size, double, double, int)>(&binding_utils::resize_wrapper));
  emscripten::function("resize", emscripten::select_overload<void(const cv::Mat&, cv::Mat&, cv::Size, double, double)>(&binding_utils::resize_wrapper_1));
  emscripten::function("resize", emscripten::select_overload<void(const cv::Mat&, cv::Mat&, cv::Size, double)>(&binding_utils::resize_wrapper_2));
  emscripten::function("resize", emscripten::select_overload<void(const cv::Mat&, cv::Mat&, cv::Size)>(&binding_utils::resize_wrapper_3));

  emscripten::constant("CV_8UC1", CV_8UC1);
  emscripten::constant("CV_8UC2", CV_8UC2);
  emscripten::constant("CV_8UC3", CV_8UC3);
  emscripten::constant("CV_8UC4", CV_8UC4);
}
