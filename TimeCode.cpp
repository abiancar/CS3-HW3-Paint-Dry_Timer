
#include <iostream>
#include <string>
#include "TimeCode.h"
using namespace std;


//constructors
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){     
    this->t += (sec + min * 60 + hr *3600);  // hr * 3600 because 60*60 = 3600, min * 60 because 1min = 60 sec
    return;
}
TimeCode::TimeCode(const TimeCode & tc){
    this->t = tc.t; // simply copy the time of a different timeCode
}

void TimeCode::SetHours(unsigned int hours){
    this-> t = this->t - this->GetHours() * 3600 + hours * 3600; // subtracts only the amount of seconds from previous hour, then adds seconds for new hour
}
void TimeCode::SetMinutes(unsigned int minutes){
    //if minutes is 60 or greater, we would get 0:60:0, which is invalid... throw error
    if(minutes > 59){
        throw invalid_argument("Must set minutes minutes to numbers between 0 and 59");
    }
    this-> t = this->t - this->GetMinutes() * 60 + minutes * 60; // subtracts only the amount of seconds from previous minute setting, then adds seconds for new minute setting
}
void TimeCode::SetSeconds(unsigned int seconds){
    //if seconds is 60 or greater, we would get 0:0:60, which is invalid... throw error
    if(seconds > 59){
        throw invalid_argument("Must set seconds to numbers between 0 and 59");
    }
    this-> t = this->t - this->GetSeconds() + seconds; 
}

void TimeCode::reset(){
    this-> t = 0; // not rocket science, just set the time of this TimeCode back to default value
}

unsigned int TimeCode::GetHours() const{
    return this->t / 3600; // Integer division allows for isolation of hours from seconds
}
unsigned int TimeCode::GetMinutes() const{
    return (this->t - 3600 * this->GetHours()) / 60; // Integer division allows for isolation of minutes from seconds
}
unsigned int TimeCode::GetSeconds() const{
    return this->t % 60; // Modular division allows for isolation of a number between 0 and 59 that represents the seconds in hr:min:sec
}

void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const{
    // Using Get methods to update variables passed by reference
    hr = this->GetHours();
    min = this->GetMinutes();
    sec = this->GetSeconds();
}
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
    long long unsigned int totalSeconds = hr * 3600 + min * 60 + sec; //same logic as constructor
    return totalSeconds;
}

string TimeCode::ToString() const{
    string timeOutput ("");
    timeOutput += to_string(this->GetHours()) + ":" + to_string(this->GetMinutes()) + ":" + to_string(this->GetSeconds());
    return timeOutput;
}  

// overloading operators
TimeCode TimeCode::operator+(const TimeCode& rhs) const{
    // we cannot add objects directly without redefining what addition is ... here we define
    // the sum of two TimeCodes as the result of adding their respective times (t) 
    TimeCode timeTotal;
    timeTotal.t = this->t + rhs.t;
    return timeTotal; 
}
TimeCode TimeCode::operator-(const TimeCode& rhs) const{
    TimeCode timeTotal;
        if(this->t < rhs.t){
            throw invalid_argument("Negative arguments not allowed");
        }
        timeTotal.t = this->t - rhs.t;
        return timeTotal; 
}
TimeCode TimeCode::operator*(const double a) const{
    TimeCode timeTotal;
    if(a < 0){
        throw invalid_argument("Cannot multiply by a negative number");
    }
    timeTotal.t = this->t * a;
    return timeTotal; 
}
TimeCode TimeCode::operator/(const double a) const{
    TimeCode timeTotal;
    if(a < 0){
        throw invalid_argument("Cannot divide by a negative number");
    }
    if(a == 0){
        throw invalid_argument("Cannot divide by zero!!!");
    }
    timeTotal.t = this->t / a;
    return timeTotal; 
}

// overloading comparison operators
bool TimeCode::operator==(const TimeCode& other) const{
    if (this->t == other.t){return true;}
    return false;
}
bool TimeCode::operator!=(const TimeCode& other) const{
    if(this->t != other.t){return true;}
    return false;
}
bool TimeCode::operator<(const TimeCode& other) const{
    if(this->t < other.t){return true;}
    return false;
}
bool TimeCode::operator<=(const TimeCode& other) const{
    if(this->t <= other.t){return true;}
    return false;
}
bool TimeCode::operator>(const TimeCode& other) const{
    if(this->t > other.t){return true;}
    return false;
}
bool TimeCode::operator>=(const TimeCode& other) const{
    if(this->t >= other.t){return true;}
    return false;
}
