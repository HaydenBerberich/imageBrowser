// imageBrowser.cpp
// Hayden Berberich
// 9-9-24
#include <iostream>
#include <opencv2/opencv.hpp>
#include <iomanip>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "imageUtils.h"

// Function to browse images based on user input
void browseImages(const std::vector<std::string>& files, int maxRows, int maxCols) {
    std::cout << std::left
              << std::setw(10) << "Index"
              << std::setw(15) << "File Size" 
              << std::setw(15) << "Size" 
              << std::setw(15) << "Pixels" 
              << std::setw(20) << "File" 
              << std::endl;

    int index = 0;
    while (true) {
        displayImage(files[index], maxRows, maxCols, index + 1);

        char key = static_cast<char>(cv::waitKey(0));
        if (key == 'q') {
            break;
        } else if (key == 'n' || key == ' ') {
            if (index < files.size() - 1) {
                index++;
            }
        } else if (key == 'p') {
            if (index > 0) {
                index--;
            }
        }
    }
}

// Function to traverse directory and build vector of image files
void traverseDirectory(const std::string& dirPath, std::vector<std::string>& files) {
    DIR* dir = opendir(dirPath.c_str());
    if (!dir) {
        std::cerr << "Error: Unable to open directory " << dirPath << std::endl;
        return;
    }

    struct dirent* entry;

    // Loop through each entry in the directory
    while ((entry = readdir(dir)) != nullptr) {
        std::string entryName = entry->d_name;

        if (entryName == "." || entryName == "..") {
            continue;
        }

        std::string fullPath = dirPath;
        if (fullPath.back() != '/') {
            fullPath += '/';
        }
        fullPath += entryName;

        struct stat entryStat;
        if (lstat(fullPath.c_str(), &entryStat) == -1) {
            std::cerr << "Error: Unable to get status of " << fullPath << std::endl;
            continue;
        }

        if (S_ISDIR(entryStat.st_mode)) {
            traverseDirectory(fullPath, files);
        } else {
            if (isValidImageFile(fullPath)) {
                files.push_back(fullPath);
            }
        }
    }

    closedir(dir);
}

int main(int argc, char** argv) {
    // Command line parsing
    const cv::String keys =
        "{help h usage ? |      | print this message   }"
        "{rows           |720   | maximum number of rows in the display window }"
        "{cols           |1080  | maximum number of columns in the display window }"
        "{@dir           |      | input directory (required) }";

    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Image Browser");

    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    if (!parser.check()) {
        parser.printErrors();
        return 1;
    }

    int rows = parser.get<int>("rows");
    int cols = parser.get<int>("cols");
    cv::String dir = parser.get<cv::String>("@dir");

    if (dir.empty()) {
        std::cerr << "Error: Input directory is required." << std::endl;
        return 1;
    }

    std::vector<std::string> files;
    traverseDirectory(dir, files);

    browseImages(files, rows, cols);

    return 0;
}