


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

long long int get_time_remaining(DryingSnapShot dss){
	size_t start = dss.startTime;
	size_t end = time(0);

	long long timeElapsed = end - start; // how much time has passed
	long long timeRemaining = dss.timeToDry->GetTimeCodeAsSeconds() - timeElapsed;
	// cout << "TIME TO DRY " << timeToDry << endl;
	// cout << "START " << start << endl;
	// cout << "END " << end << endl;
	// cout << "TIME ELAPSED " << timeElapsed << endl;
	// cout << "TIME REMAINING " << timeRemaining << endl << endl;


	return timeRemaining;
}

// What is my purpose? 
// You print a string with relevant DryingSnapShot info!
// Oh... my god
string drying_snap_shot_to_string(DryingSnapShot dss){
	long long int time_remaining = get_time_remaining(dss);
	string string_time = to_string(time_remaining);
	TimeCode t = TimeCode(0,0,time_remaining);
	return "BATCH: " + dss.name + "(takes " + t.ToString() + " to dry) ";
}

double get_sphere_sa(double rad){
	double surface_area = 4 * M_PI * rad * rad;
	return surface_area;
}

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

	// add more tests here


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here

	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;

	// add more tests here
	cout << "ALL TESTS PASSED!" << endl;

}



int main(){
	vector<DryingSnapShot> BatchVector;
	char userResponse = 'p';

	while (userResponse != 'q'){
		int randID = rand();


		// at the beginning of every loop, check if any of the batches have finished, remove them from BatchVectors
		for (size_t i = 0; i < BatchVector.size(); i++){
			DryingSnapShot curr = BatchVector.at(i);
			if (get_time_remaining(curr) <= 0){
				cout << "BELOW! " << endl;
				for (size_t j = 0; j < BatchVector.size() ; j++){
					cout << "AAA " << drying_snap_shot_to_string(BatchVector.at(j));
				}
				delete &BatchVector.at(i);
				for (size_t j = 0; j < BatchVector.size() ; j++){
					cout << "AAA " << drying_snap_shot_to_string(BatchVector.at(j));
				}
				BatchVector.erase(BatchVector.begin()+i);
			}
		}

		cin >> userResponse;
		if(userResponse == 'a'){
			int radius = 7; // 
			cout << "radius: " << radius;

			DryingSnapShot tss; // create a Drying SnapShot called tss
			tss.name = to_string(randID); // give it identifier
			tss.startTime = time(0); //set its start time

			// TimeCode tc = *compute_time_code(get_sphere_sa(rad));
			TimeCode tc = TimeCode(0,0,radius); // amount of time till it dries
			tss.timeToDry = &tc;

			cout << tss.timeToDry->ToString() << endl;
			TimeCode remainingTime = TimeCode(0,0,get_time_remaining(tss));
			cout << "Batch-" << tss.name << "will dry in " << remainingTime.ToString() << endl << endl;
			BatchVector.push_back(tss);
		}
		else if(userResponse == 'v'){
			for (size_t i = 0; i < BatchVector.size(); i++){
				DryingSnapShot curr = BatchVector.at(i);
				
				//if this item should be removed
				if (get_time_remaining(curr) <= 0){
					cout << "BELOW ZERO";
					for (size_t j = 0; j < BatchVector.size() ; j++){
					cout << "AAA " << drying_snap_shot_to_string(BatchVector.at(j));
					}
					delete &BatchVector.at(i);
					for (size_t j = 0; j < BatchVector.size() ; j++){
					cout << "AAA " << drying_snap_shot_to_string(BatchVector.at(j));
					}
					BatchVector.erase(BatchVector.begin()+i);
				}	
				cout << "Batch-" <<curr.name << "time remaining: " << get_time_remaining(BatchVector.at(i)) <<endl;
			}
			cout << BatchVector.size() << " items being tracked" << endl << endl;
		}
	}

	tests();
	return 0;
}