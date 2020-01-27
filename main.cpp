#include <iostream>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/optflow.hpp>
#include <opencv2/video/tracking.hpp>

using namespace cv;


void mouse_callback(int event, int x, int y, int flags, void* param);
void draw_rectangle(Mat& img, Rect box);

Rect save_rectangle;
bool bool_drawing_box = false;
RNG random_rgb(0);  // generate random number for bounding box

void mouse_callback(int event, int x, int y, int flags, void* param) {
    cv::Mat& image = *(cv::Mat*) param;
    switch (event) {
        case EVENT_MOUSEMOVE: {    // when mouse moves, get the current rectangle's width and height
            if (bool_drawing_box) {
                save_rectangle.width = x - save_rectangle.x;
                save_rectangle.height = y - save_rectangle.y;
            }
        }
            break;
        case EVENT_LBUTTONDOWN: {  // left mouse button is pressed down,
            // starting corner's coordinates of the rectangle
            bool_drawing_box = true;
            save_rectangle = Rect(x, y, 0, 0);
        }
            break;
        case EVENT_LBUTTONUP: {   // left mouse button is released
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

    cv::imshow("rABEL", image);
}


void draw_rectangle(cv::Mat& img, cv::Rect box)
{
    //Draw a rectangle with random color
    cv::rectangle(img, box.tl(), box.br(), cv::Scalar(random_rgb.uniform(0, 255), random_rgb.uniform(0,255),random_rgb.uniform(0,255)));
}


int main() {
    String hello = "Let's start this!";
    std::cout << hello << std::endl;
    std::vector<std::string> file_names_images;
    const std::string images_directory = "/home/ionelia/labelRabel/images"; // TODO: add args here
    struct dirent *ep;
    DIR *dir_open_images = opendir(images_directory.c_str());

//    Tracker_optflow tracker_optflow;

    if (dir_open_images != NULL) {
        while ((ep = readdir(dir_open_images))) {
            // ignore subdirectories
            if (ep->d_type & DT_DIR) {
                continue;
            }

            size_t extentions = std::string(ep->d_name).find_last_of(".");
            file_names_images.push_back((std::string) images_directory + "/" + ep->d_name);
            std::cout << file_names_images.back() << std::endl;

        }
        (void) closedir(dir_open_images);

    }

    // sort them so you don't get nuts!
    std::sort(file_names_images.begin(), file_names_images.end());
    std::cout << "Sorted Last: " + file_names_images.back() << std::endl;


    if (file_names_images.empty()) {
        throw std::runtime_error("Image directory is empty!");
    }

    // GUI
    int desiredWidth=640,desiredheight=480;
    std::string const window_name = "rABEL";
    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    cv::resizeWindow(window_name, 1280, 720);
    cv::createTrackbar("image num", "rABEL", 0,file_names_images.size());


    // open show images flow
    bool next_image_flow = true;
    int image_index = 0;
    std::string image_file_open;
    cv::Mat cloned_image;

    while (image_index < (int) file_names_images.size()) {
        if (next_image_flow) {
            std::printf("Labelling image %i of %i...\n", image_index, (int) file_names_images.size());
            image_file_open = file_names_images.at(image_index);

            // image resizing
            cv::Mat preview(cv::Size(100,100), CV_8UC3);
            cv::Mat full_image(cv::Size(1280, 720), CV_8UC3);
//            cv::Mat frame(Size(full_image.cols, full_image.rows + preview.rows), CV_8UC3);

//            cv::Rect full_rect_dst(Point2i(0, preview.rows), Size(frame.cols, frame.rows - preview.rows));
//            cv::Mat full_image_roi = frame(full_rect_dst);

            cv::Mat read_image = cv::imread(image_file_open, cv::IMREAD_COLOR);

            cv::Mat test;
            cv::resize(read_image, test, cv::Size(128, 72));

            if (read_image.empty()) {
                throw std::runtime_error("!!! Failed imread(): image not read");
                // std::cout << "!!! Failed imread(): image not read" << std::endl;
            }
            cloned_image = read_image.clone();
//            next_image_flow = false;

        }
        image_index++;
        // std::cout << image_file_open << std::endl;
        // std::cout << cloned_image.size().width << std::endl;
        cv::setMouseCallback(window_name, mouse_callback, &cloned_image);
        cv::imshow(window_name, cloned_image);
        cv::waitKey(0);
    }
}