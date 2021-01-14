#include <iostream>
#include "TimeCode.h" // for timecode's (duh)
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Creates a vector of substrings originally separated by a delimeter
vector<string> split(string time, char delim){
    vector<string> vctr;
    string currString;
    
    //strings are created based on everything before, in between, and after the delimiter... then added to vector
    for(size_t i = 0; i < time.size(); i++){
        //if the delimeter is not found, add character to current string
        if (time.at(i) != delim) {
            currString += time.at(i);
        }
        //if this is the last string character, break out of the loop and add whatever string we have so far to vector
        if(i == time.size()-1){
            vctr.push_back(currString);
            break;
        }
        //if the delimeter is found, complete the current string and add it to vector
        if(time.at(i) == delim){
            vctr.push_back(currString);
            currString.clear();
        }
    }

    return vctr;     
}

//processes a line of data, finds mission time, and converts it into a TimeCode object
TimeCode parse_string(string line,int colonIndex){
    int start  = colonIndex -2; // Our dataset contains mission times in the following form "10:15" so
    int end = colonIndex + 2;   // colonIndex +2 and colonIndex-2 represent the start and end of mission times
    
    string subString;
    
    //Create a substring containing only the time ... get rid of rest of line being parsed (useless info)
    for(int i = start; i <= end; i++){
        subString += line.at(i);
    }
    
    // We should be left with a substring like "05:20", which we will split into a string vector at the colon
    vector<string> times = split(subString, ':');

    // We should have a vector with 2 elements, the first representing hrs and the second minutes     
    int hr = stoi(times.at(0));  // stoi(string) converts string to int 
    int min  = stoi(times.at(1));

    // Initialize and return a time object with given hours and minutes, seconds set to zero because dataset lacks seconds
    TimeCode t = TimeCode(hr,min,0);
    return t;
}

int main(){
    ifstream nasaFS;                // fileStream
    double totalTime;               // sum of all flight times
    double averageTimeInSeconds;    // self explanatory
    long int count;                 // total # of flights
    long int noTimeCount;           // total # of missions with incomplete data

    //open Nasa datafile
    nasaFS.open("Space_Corrected.csv");
    
    //if file is unable to open, return error code 1
    if (!nasaFS.is_open()) {
       cout << "Could not open file nasa.txt." << endl;
       return 1;
    }
    string currString;
    
    if(!nasaFS.fail()){
        getline(nasaFS,currString); // skip the first line, does not contain numerical data but does have a colon that would cause a program failure
    }
   
    // if there is a next line, keep reading the file (till the end)
    while(!nasaFS.fail()){
        getline(nasaFS,currString);          // reads a line of the file and assigns it to string currString
        size_t index = currString.find(":"); // check: does this line have a colon?
        
        //if we find a colon in a line with valid data, create a TimeCode object with the information
        if(index != std::string::npos){
            TimeCode t = parse_string(currString, index);
            totalTime += t.GetTimeCodeAsSeconds();            // add the current mission's time to thos of all others
            count++;                                          // increase counter for computing average mission time
        }
        else{
            noTimeCount++;  // counter for debugging purposes, if no colon is found, data is broken!
        }
    }

    averageTimeInSeconds = totalTime / count;
    TimeCode t = TimeCode(0,0,averageTimeInSeconds);

    cout << count << " data points" << endl;
    cout << "AVERAGE: " << t.ToString() << endl;

    //close Nasa datafile
    nasaFS.close();

    return 0;
}