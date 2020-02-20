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

#include "utils_labeler.cpp"


int main() {
    mouse_and_save_callback mouse_params;
    std::string hello = "Let's start this!";
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
    int desired_width=640,desired_height=480;
    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    cv::resizeWindow(window_name, 1280, 720);
    int images_track = cv::createTrackbar(bar_images, window_name, 0,file_names_images.size());
    int class_id  = cv::createTrackbar(bar_classes, window_name, 0, classes_txt.size());

    // open show images flow
    bool next_image_flow = true;
    int image_index = 0;
    std::string image_file_open;
    cv::Mat cloned_image;

    while (image_index < (int) file_names_images.size()) {

        if (next_image_flow) {
            image_file_open = file_names_images.at(image_index);
            std::printf("Labelling image %i of %i <%s>\n", image_index, (int) file_names_images.size(), image_file_open.c_str());

            // image resizing
            cv::Mat preview(cv::Size(100,100), CV_8UC3);
            cv::Mat full_image(cv::Size(1280, 720), CV_8UC3);

            cv::Mat read_image = cv::imread(image_file_open, cv::IMREAD_COLOR);

            cv::Mat test;
            cv::resize(read_image, test, cv::Size(128, 72));

            if (read_image.empty()) {
                throw std::runtime_error("!!! Failed imread(): image not read");
            }
            cloned_image = read_image.clone();
//            next_image_flow = false;

        }

        cv::setTrackbarPos(bar_images, window_name, image_index);
        cv::setTrackbarPos(bar_classes, window_name, 0);
        image_index++;

        cv::setMouseCallback(window_name, mouse_callback, &cloned_image);
        cv::imshow(window_name, cloned_image);
//        mouse_params->img = cloned_image;
//        cv::setMouseCallback(window_name, mouse_callback, (void*)&mouse_params);
//        cv::imshow(window_name, mouse_params.img);

        // save labels to txt file
        std::string delimiter = ".";
        std::string token = image_file_open.substr(0, image_file_open.find(delimiter)); // token is "scott"
        const std::string name_labels = token + ".txt";
//        printf("%s\n", name_labels.c_str());

        std::ofstream save_labels_file(name_labels);
        if(!save_labels_file) {
            std::cout << "Cannot ope file, error!";
            return 1;
        }

        cv::waitKey(0);
    }
}