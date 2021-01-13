
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
#include "TimeCode.h"


TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){     
    this->t += (sec + min * 60 + hr *3600); 
    return;
}

TimeCode::TimeCode(const TimeCode & tc){
    this->t = tc.t;
}

string TimeCode::ToString() const{
    string timeOutput ("");
    timeOutput += to_string(this->GetHours()) + ":" + to_string(this->GetMinutes()) + ":" + to_string(this->GetSeconds());
    return timeOutput;
}
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const{
    hr = this->GetHours();
    min = this->GetMinutes();
    sec = this->GetSeconds();
}
unsigned int TimeCode::GetHours() const{
    return this->t / 3600;
}
unsigned int TimeCode::GetMinutes() const{
    return (this->t - 3600 * this->GetHours()) / 60;
}
unsigned int TimeCode::GetSeconds() const{
    return this->t % 60;
}
void TimeCode::SetHours(unsigned int hours){
    this-> t = this->t - this->GetHours() * 3600 + hours * 3600; 
}
void TimeCode::SetMinutes(unsigned int minutes){
    if(minutes > 59){
        throw invalid_argument("Must set minutes minutes to numbers between 0 and 59");
    }
    this-> t = this->t - this->GetMinutes() * 60 + minutes * 60; 
}
void TimeCode::SetSeconds(unsigned int seconds){
    if(seconds > 59){
        throw invalid_argument("Must set seconds to numbers between 0 and 59");
    }
    this-> t = this->t - this->GetSeconds() + seconds; 
}
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
    long long unsigned int totalSeconds = hr * 3600 + min * 60 + sec;
    return totalSeconds;
}  
// overloading subtract operator

TimeCode TimeCode::operator+(const TimeCode& rhs) const{
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
void TimeCode::reset(){
    this-> t = 0;
}