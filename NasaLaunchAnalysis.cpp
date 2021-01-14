#include <iostream>
#include "TimeCode.h" // for timecode's (duh)
#include <fstream>
#include <string>
#include <vector>
using namespace std;




vector<string> split(string time, char delim){
    vector<string> vctr;
    string currString;
    
    cout << "CURR STRING: " << time << endl;
    for(size_t i = 0; i < time.size(); i++){
        if (time.at(i) != delim) {
            currString += time.at(i);
        }
        if(i == time.size()-1){
            vctr.push_back(currString);
            break;
        }
        if(time.at(i) == delim){
            vctr.push_back(currString);
            currString.clear();
        }
    }

    return vctr;     
    
}
TimeCode parse_string(string line,int index){
    int start  = index -2;
    int end = index + 2;
    
    string subString;
    for(int i = start; i <= end; i++){
        subString += line.at(i);
    }
    vector<string> times = split(subString, ':');

    for (size_t i = 0; i < times.size(); i++){
        // cout <<  times.at(i) << " ";
    }

    int hr = stoi(times.at(0));
    int min  = stoi(times.at(1));

    // cout << "HOURS:" << hr << " MINUTES:" << min << endl;

    cout << endl;

    // cout << subString << endl;

    //convert substring to vector, split at ":" delimiter
    //convert each substring to integers represeting hours and minutes
    TimeCode t = TimeCode(hr,min,0);
    return t;
}

//go through each line
//at each line, create a string
//find the ":" string, indicating time
//return the time via a timeCode back to the main function
//represent the timeCode in seconds
//add all the timeCode times together
//compute average

int main(){
    ifstream nasaFS;
    double totalTime;
    // double averageTime;
    long int count; 
    long int noTimeCount;   

    nasaFS.open("Space_Corrected.csv");
    
    //if file is unable to open, return error code 1
    if (!nasaFS.is_open()) {
       cout << "Could not open file nasa.txt." << endl;
       return 1;
    }
    string currString;
    if(!nasaFS.fail()){
    getline(nasaFS,currString);
    }
    // if there is a next line, keep reading the file (till the end)
    while(!nasaFS.fail()){
        getline(nasaFS,currString);
        
        size_t index = currString.find(":");
        if(index != std::string::npos){
            TimeCode t = parse_string(currString, index);
            totalTime += t.GetTimeCodeAsSeconds();
            count++;
        }
        else{
            noTimeCount++;
        }
    }
    cout << "TOTAL TIME: " << totalTime << endl;
    cout << "COUNT: " << count << endl;
    double averageTimeInSeconds = totalTime / count;
    TimeCode t = TimeCode(0,0,averageTimeInSeconds);
    cout << "AVERAGE TIME IN SECONDS: " << averageTimeInSeconds << endl;
    cout << "AVERAGE TIME -- " << t.ToString() << endl;

    cout << "Entries without valid time: " << noTimeCount << endl;
    cout << "TOTAL ENTRIES PROCESSED: " << count + noTimeCount << endl;

    //read first 


    nasaFS.close();


    return 0;
}