// imageUtils.h
#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <algorithm>

// Function to check if a file has a valid image extension
bool isValidImageFile(const std::string& filePath);

// Function to display images in specified dimensions
void displayImage(const std::string& filePath, int maxRows, int maxCols, int index);

#endif // IMAGEUTILS_H