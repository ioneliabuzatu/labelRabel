void mouse_callback(int event, int x, int y, int flags, void* param);
void draw_rectangle(cv::Mat& img, cv::Rect box);


cv::Rect save_rectangle;
bool bool_drawing_box = false;
cv::RNG random_rgb(0);  // generate random number for bounding box

std::string const window_name = "rABEL";
std::string const bar_images = "Image id";
std::string const bar_classes= "Class id";


static std::vector<std::string> classes_txt = {"car", "truck", "person", "motorbike", "bicycle"};
