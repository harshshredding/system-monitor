#include <string>

#include "format.h"

using namespace std;
using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long total_seconds[[maybe_unused]]) { 
    int hours = total_seconds/3600;
    int minutes = (total_seconds%3600)/60;
    int seconds = total_seconds%60;
    return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
}
