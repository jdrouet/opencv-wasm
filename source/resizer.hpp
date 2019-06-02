#include <algorithm>

#include "opencv2/core.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/flann/flann.hpp"
#include "opencv2/ml.hpp"
#include "opencv2/photo.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgcodecs.hpp"

#define SMALL_SIZE 400

class Resizer {
private:
  cv::Mat input;
public:
  Resizer(cv::Mat input);
  void run();
};
