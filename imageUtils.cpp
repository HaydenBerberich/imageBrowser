// imageUtils.cpp
#include "imageUtils.h"

// Function to check if a file has a valid image extension
bool isValidImageFile(const std::string& filePath) {
    std::vector<std::string> validExtensions = {".jpg", ".jpeg", ".png", ".bmp", ".tiff", ".tif"};
    std::string extension = filePath.substr(filePath.find_last_of('.'));
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    return std::find(validExtensions.begin(), validExtensions.end(), extension) != validExtensions.end();
}

// Function to display images in specified dimensions
void displayImage(const std::string& filePath, int maxRows, int maxCols, int index) {
    try {
        cv::Mat image = cv::imread(filePath);
        if (image.empty()) {
            std::cerr << "Error: Unable to read image " << filePath << std::endl;
            return;
        }

        double aspectRatio = static_cast<double>(image.cols) / image.rows;
        int newRows = maxRows;
        int newCols = static_cast<int>(newRows * aspectRatio);
        if (newCols > maxCols) {
            newCols = maxCols;
            newRows = static_cast<int>(newCols / aspectRatio);
        }
        cv::resize(image, image, cv::Size(newCols, newRows));

        cv::imshow("Image Browser", image);

        std::cout << std::left
                  << std::setw(10) << index
                  << std::setw(15) << (std::to_string(image.total() * image.elemSize()) + "B")
                  << std::setw(15) << (std::to_string(image.rows) + "x" + std::to_string(image.cols))
                  << std::setw(15) << (std::to_string(image.rows * image.cols))
                  << std::setw(20) << filePath 
                  << std::endl;
    } catch (const cv::Exception& e) {
        std::cerr << "OpenCV error: " << e.what() << std::endl;
    }
}