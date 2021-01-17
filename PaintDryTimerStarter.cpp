#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (also duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;

struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry; //this pointer points to a TimeCode
};

// gets time till drying is complete for each DSS struct being referenced
long long int get_time_remaining(DryingSnapShot dss){
	size_t start = dss.startTime;
	size_t end = time(0);

	long long timeElapsed = end - start; // how much time has passed
	long long timeRemaining = dss.timeToDry->GetTimeCodeAsSeconds() - timeElapsed;

	return timeRemaining;
}

//prints DryingSnapShot with relevant information
string drying_snap_shot_to_string(DryingSnapShot dss){
	long long int time_remaining = get_time_remaining(dss);
	string string_time = to_string(time_remaining);
	TimeCode t = TimeCode(0,0,time_remaining);
	return "BATCH-" + dss.name + "(takes " + t.ToString() + " to dry) ";
}

// Uses surface area formula to (4*pi*r^2) to calculate seconds required
double get_sphere_sa(double rad){
	double surface_area = 4 * M_PI * rad * rad;
	return surface_area;
}

//given a surface area, will create a TimeCode pointer that points to a TimeCode set at the Surface Area
TimeCode *compute_time_code(double surfaceArea){
	TimeCode *t = new TimeCode(0,0,surfaceArea); 
	return t;
}
void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);

	DryingSnapShot dss2;
	dss2.startTime = time(0);
	tc = TimeCode(0, 0, 15);
	dss2.timeToDry = &tc;
	ans = get_time_remaining(dss);
	assert(ans > 14 && ans < 16);

	DryingSnapShot dss3;
	dss3.startTime = time(0);
	tc = TimeCode(0, 1, 15);
	dss3.timeToDry = &tc;
	ans = get_time_remaining(dss);
	assert(ans > 74 && ans < 76);

	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);

	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;

	cout << "ALL TESTS PASSED!" << endl;
}	
int main(){
	
	//tests();
	vector<DryingSnapShot> tracker;
	vector<DryingSnapShot> cleaner; //used to help arrange wet items, very challenging to do with just the tracker vector

	cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
	
	string userResponse = "p";
	while(userResponse != "q"){
	
	// at the beginning of every loop, check if any of the batches have finished, remove them from BatchVectors
		for (size_t i = 0; i < tracker.size(); i++){
			DryingSnapShot curr = tracker.at(i);
			// if DSS has finished drying,place it in cleaner vector
			if (get_time_remaining(curr) > 0){
				cleaner.push_back(curr);
			}
		}
		//Delete everything in original tracker to prevent memory leaks
		for(size_t i = 0; i < tracker.size(); i++){
			tracker.at(i).timeToDry = nullptr;
			delete tracker.at(i).timeToDry;	
		}
		tracker.clear(); //reset tracker
		tracker = cleaner; // assign al cleaner objects to tracker
		
		//delete everything in cleaner and reset cleaner vector for further use
		for(size_t i = 0; i < cleaner.size(); i++){
			cleaner.at(i).timeToDry = nullptr;
			delete cleaner.at(i).timeToDry;	
		}
		cleaner.clear();

		//if user wishes to view current batches, print all batches available in tracker vector...
		if(userResponse == "v"){
			for (size_t i = 0; i < tracker.size(); i++){
				DryingSnapShot curr = tracker.at(i);		
				cout << drying_snap_shot_to_string(curr) << endl;
			}
			cout << tracker.size() << " items being tracked.";
		}
		if(userResponse == "a"){
			int randID = rand(); // random name id generated here for each batch
			int radius = (rand() % 40) * 0.25; // selecting random radii for adding
			cout << "radius: " << radius << endl;

			//if user wants to create new DSS...
			DryingSnapShot tss; 			// create a Drying SnapShot called tss
			tss.name = to_string(randID);   // give it identifier
			tss.startTime = time(0);        //set its start time

			tss.timeToDry = compute_time_code(get_sphere_sa(radius)); // creates TimeCode with expected drying duration
			cout << tss.timeToDry->ToString() << endl;

			TimeCode remainingTime = TimeCode(0,0,get_time_remaining(tss)); // creates a temp TimeCode to display time remaining in 00:00:00 format
			cout << "Batch-" << tss.name << "will dry in " << remainingTime.ToString() << endl;
			tracker.push_back(tss); // place DSS in tracker
		}
		cin >> userResponse;
	}

	//when we are done running the program... we have to free the memory remaining on our tracker and helper vectors!!
	//this took days to discover... never forget
		for(size_t i = 0; i < tracker.size(); i++){
			delete tracker.at(i).timeToDry;	
			tracker.at(i).timeToDry = nullptr;	
		}	
		for(size_t i = 0; i < cleaner.size(); i++){
			delete cleaner.at(i).timeToDry;	
			cleaner.at(i).timeToDry = nullptr;
		}
		cleaner.clear();
		tracker.clear();
	
	return 0;
}