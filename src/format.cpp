#include <string>

#include "format.h"

using namespace std;
using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long total_seconds) { 
    int hours = total_seconds/3600;
    int minutes = (total_seconds%3600)/60;
    int seconds = total_seconds%60;
    hours = hours % 100;
    string hours_string = to_string(hours);
    string minutes_string = to_string(minutes);
    string seconds_string = to_string(seconds);
    if (minutes < 10) {
        minutes_string = "0" + minutes_string;
    }
    if (seconds < 10) {
        seconds_string = "0" + seconds_string;
    }
    if (hours < 10) {
        hours_string = "0" + hours_string;
    }
    return hours_string + ":" + minutes_string + ":" + seconds_string;
}
