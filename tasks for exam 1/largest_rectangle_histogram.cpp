
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::min_element;

//Given an array of integers heights representing the histogram's
//bar height where the width of each bar is 1, return the area of
//the largest rectangle in the histogram.

class Solution {
public:
    int calculate_area(int width, vector<int>& heights) {
        int max_area = 0;
        for (int i = 0; i < heights.size() - width + 1; ++i)
        {
            int curr_min = *min_element(heights.begin() + i, heights.begin() + i + width);
            int curr_area = curr_min * width;
            if (max_area < curr_area)
            {
                max_area = curr_area;
            }

        }
        return max_area;
    }

    int largestRectangleArea(vector<int>& heights) {

        int max_area = 0;

        for (int i = 1; i <= heights.size(); ++i)
        {
            int cur_area = calculate_area(i, heights);
            if (cur_area > max_area)
                max_area = cur_area;
        }
        return max_area;
    }
};

int main()
{

}

