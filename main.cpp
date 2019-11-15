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

int main() {
    int hello = 3;
    std::cout << hello << std::endl;
    std::vector<std::string> file_names_images;
    const std::string images_directory = "/home/ionelia/labelRabel/images";
    struct dirent* ep;
    DIR* dir_open_images = opendir(images_directory.c_str());

    if (dir_open_images != NULL) {
        while ((ep = readdir(dir_open_images))) {
            // ignore subdirectories
            if (ep->d_type & DT_DIR) {
                continue;
            }

            size_t extentions = std::string(ep->d_name).find_last_of(".");
            file_names_images.push_back((std::string)images_directory + "/" + ep->d_name);
            std::cout << file_names_images.back() << std::endl;

        }
        (void)closedir(dir_open_images);

    }

    // sort them so you don't get nuts!
    std::sort(file_names_images.begin(), file_names_images.end());
    std::cout << "Sorted Last: " + file_names_images.back() << std::endl;


    if (file_names_images.empty()) {
        throw std::runtime_error("Image directory is empty!");
    }

    cv::namedWindow("labelRabel2D", cv::WINDOW_AUTOSIZE);
    // open show images flow
    bool next_image_flow = true;
    int image_index = 0;
    std::string image_file_open;
    cv::Mat cloned_image;

    while(image_index < (int)file_names_images.size()) {
        if (next_image_flow) {
            std::printf("Labelling image %i of %i...\n", image_index, (int)file_names_images.size());
            image_file_open = file_names_images.at(image_index);
            cv::Mat read_image = cv::imread(image_file_open, cv::IMREAD_COLOR);
            if (read_image.empty()) {
                throw std::runtime_error("!!! Failed imread(): image not read");
                // std::cout << "!!! Failed imread(): image not read" << std::endl;
            }
            cloned_image = read_image.clone();
            next_image_flow = false;

        }
        // std::cout << image_file_open << std::endl;
        // std::cout << cloned_image.size().width << std::endl;
        cv::imshow("labelRabel2D", cloned_image);
        cv::waitKey(1);
    }
}