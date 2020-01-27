#include "utils_labeler.h"


void mouse_callback(int event, int x, int y, int flags, void* param) {
    cv::Mat& image = *(cv::Mat*) param;
    switch (event) {
        case cv::EVENT_MOUSEMOVE: {    // when mouse moves, get the current rectangle's width and height
            if (bool_drawing_box) {
                save_rectangle.width = x - save_rectangle.x;
                save_rectangle.height = y - save_rectangle.y;
            }
        }
            break;
        case cv::EVENT_LBUTTONDOWN: {  // left mouse button is pressed down,
            // starting corner's coordinates of the rectangle
            bool_drawing_box = true;
            save_rectangle = cv::Rect(x, y, 0, 0);
        }
            break;
        case cv::EVENT_LBUTTONUP: {   // left mouse button is released
            //draw the rectangle
            bool_drawing_box = false;
            if (save_rectangle.width < 0) {
                save_rectangle.x += save_rectangle.width;
                save_rectangle.width *= -1;
            }

            if (save_rectangle.height < 0) {
                save_rectangle.y += save_rectangle.height;
                save_rectangle.height *= -1;
            }
            draw_rectangle(image, save_rectangle);
        }
            break;
    }

    cv::imshow(window_name, image);
}


void draw_rectangle(cv::Mat& img, cv::Rect box)
{
    // draw a rectangle with random color
    cv::rectangle(img, box.tl(), box.br(), cv::Scalar(random_rgb.uniform(0, 255), random_rgb.uniform(0,255),random_rgb.uniform(0,255)));
}


static void mouse_callback_circles(int event, int x, int y, int, void* imgptr){
    if ( event != 1 ) return;     // only draw on lmouse down
    cv::Mat & img = (*(cv::Mat*)imgptr); // first cast, then deref
    cv::Point pt1 = cv::Point(x, y);
    circle(img, pt1, 1, cv::Scalar(0, 255, 0), 100, 8, 0);
    cv::imshow(window_name, img);
    cv::waitKey(1);
}