#include <stddef.h>
#include <Processing.NDI.Lib.h>
#include <opencv2/opencv.hpp>

int main() {
    NDIlib_send_instance_t my_ndi_send = NDIlib_send_create(nullptr);

    NDIlib_send_destroy(my_ndi_send);

    cv::VideoCapture cap;
    cap.open(0);

    return 0;
}