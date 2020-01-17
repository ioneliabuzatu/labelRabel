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


//class Gui_labeler {
//
//
//public:
//    const int flow_error;
//    // constructors
//    Gui_labeler(int window_size=15, int max_level=3, int iterations 10000; int flow_error_ = -1) :
//        flow_error((flow_error_ > 0) ? flow_error_ : (window_size*4))
//    {
//
//        something1 = cv::SparsePyrLKOpticalFlow::create();
//
//    }
//
//};


int main() {
    int hello = 3;
    std::cout << hello << std::endl;
    std::vector<std::string> file_names_images;
    const std::string images_directory = "/home/ionelia/labelRabel/images";
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
        cv::imshow(window_name, cloned_image);
        cv::waitKey(0);
    }
}