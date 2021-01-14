
#include <iostream>
#include <assert.h>
#include "TimeCode.h"
using namespace std;


void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	
	t = TimeCode::ComponentsToSeconds(0,6,8);
	assert (t == 368);

	t = TimeCode::ComponentsToSeconds(0,0,0);
	assert (t == 0);

	t = TimeCode::ComponentsToSeconds(27,1,6);
	assert (t == 97266);
	
	cout << "PASSED!" << endl << endl;
}

void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	cout << "PASSED!" << endl << endl;
}

void TestSecondaryConstructor(){
	TimeCode tc = TimeCode(23,18,50);
	TimeCode tc1 = TimeCode(tc);
	assert(tc1.ToString() == "23:18:50");

	TimeCode tc3;
	TimeCode tc4 = TimeCode(tc3);
	assert(tc4.ToString() == tc3.ToString());
}

void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	// Random but "safe" inputs
	TimeCode tc2 = TimeCode(3, 17, 42);
	//cout << "tc2: " << tc2.ToString() << endl;
	assert(tc2.ToString() == "3:17:42");
	
	TimeCode tc3 = TimeCode(0, 1, 7);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc3.ToString() == "0:1:7");

	TimeCode tc4 = TimeCode(48, 0, 25);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc4.ToString() == "48:0:25");
	
	cout << "PASSED!" << endl << endl;
}

void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	TimeCode tc2 = TimeCode(0, 1, 7);
	tc2.GetComponents(h, m, s);
	assert(h == 0 && m == 1 && s == 7);

	TimeCode tc3 = TimeCode(48, 0, 55);
	tc3.GetComponents(h, m, s);
	assert(h == 48 && m == 0 && s == 55);
	
	cout << "PASSED!" << endl << endl;
}

void TestGetHours(){
	cout << "Testing GetHours()" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.GetHours() == 0);
	
	// Random but "safe" inputs
	TimeCode tc2 = TimeCode(3, 17, 42);
	assert(tc2.GetHours() == 3);
	
	TimeCode tc3 = TimeCode(5, 1, 7);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc3.GetHours() == 5);

	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}

void TestGetMinutes(){
	cout << "Testing GetMinutes()" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.GetMinutes() == 0);
	
	// Random but "safe" inputs
	TimeCode tc2 = TimeCode(3, 17, 42);
	assert(tc2.GetMinutes() == 17);
	
	TimeCode tc3 = TimeCode(5, 1, 7);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc3.GetMinutes() == 1);

	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}

void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just keep doing more tests
	}
	TimeCode tc6 = TimeCode(48, 5, 0);
	TimeCode tc7 = TimeCode(0, 20, 0);
	TimeCode tc8 = tc6 - tc6;
	assert(tc8.ToString() == "0:0:0");

	tc8 = tc6 - tc7;
	assert(tc8.ToString() == "47:45:0");
	
	cout << "PASSED!" << endl << endl;
}

void TestAdd(){
	cout << "Testing Add" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 + tc2;
	assert(tc3.ToString() == "1:50:0");
	TimeCode tc4 = TimeCode(7887, 25, 52);
	TimeCode tc5 = TimeCode(0, 50, 0);
	TimeCode tc6 = tc4 + tc5;
	assert(tc6.ToString() == "7888:15:52");
	TimeCode tc7 = TimeCode(1, 0, 0);
	TimeCode tc8 = TimeCode(0, 50, 0);
	TimeCode tc9 = tc1 + tc2;
	cout << "PASSED!" << endl << endl;
}

void TestMultiply(){
	cout << "Testing Multiply" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = tc1 * 2;
	assert(tc2.ToString() == "2:0:0");
	tc2 = tc1 * 2.5;
	assert(tc2.ToString() == "2:30:0");	
	TimeCode tc3 = tc1 * 0;
	assert(tc3.ToString() == "0:0:0");	
	tc1.reset();
	tc1.SetMinutes(25);
	tc1 = tc1 * 0.5;
	assert(tc1.ToString() == "0:12:30");
	try{
		TimeCode tc5 = tc1 * (-5) ;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just keep doing more tests
	}
	cout << "PASSED!" << endl << endl;
}

void TestDivide(){
	cout << "Testing Divide" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = tc1 / 2;
	assert(tc2.ToString() == "0:30:0");
	try{
		TimeCode tc5 = tc1 / 0 ;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just keep doing more tests
	}
	try{
		TimeCode tc5 = tc1 / -1 ;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just keep doing more tests
	}

	// more tests
	
	cout << "PASSED!" << endl << endl;
}

void TestSetSeconds(){
	cout << "Testing Set Seconds" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	tc.SetSeconds(59);
	assert(tc.ToString() == "0:0:59");
	
	// Random but "safe" inputs
	TimeCode tc2 = TimeCode(5, 2, 1);
	//cout << "tc2: " << tc2.ToString() << endl;
	tc2.SetSeconds(0);
	assert(tc2.ToString() == "5:2:0");
	
	TimeCode tc3 = TimeCode(24, 34, 6);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	tc3.SetSeconds(52);
	assert(tc3.ToString() == "24:34:52");
	
	try{
		tc3.reset();
		tc3.SetSeconds(60);
		assert(false);
	}
	catch(const invalid_argument& e){
	}
	try{
		tc3.reset();
		tc3.SetSeconds(70);
		assert(false);
	}
	catch(const invalid_argument& e){
	}	
	cout << "PASSED!" << endl << endl;
}

void TestSetMinutes(){
	cout << "Testing Set Minutes" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	tc.SetMinutes(59);
	assert(tc.ToString() == "0:59:0");
	
	// Random but "safe" inputs
	TimeCode tc2 = TimeCode(5, 2, 1);
	//cout << "tc2: " << tc2.ToString() << endl;
	tc2.SetMinutes(0);
	assert(tc2.ToString() == "5:0:1");
	
	TimeCode tc3 = TimeCode(24, 34, 6);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	tc3.SetMinutes(52);
	assert(tc3.ToString() == "24:52:6");

	try{
		tc3.reset();
		tc3.SetMinutes(60);
		assert(false);
	}
	catch(const invalid_argument& e){
	}
	try{
		tc3.reset();
		tc3.SetMinutes(70);
		assert(false);
	}
	catch(const invalid_argument& e){
	}	
	
	cout << "PASSED!" << endl << endl;
}

void TestSetHours(){
	cout << "Testing Set Hours" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	tc.SetHours(59);
	assert(tc.ToString() == "59:0:0");
	
	// Random but "safe" inputs
	TimeCode tc2 = TimeCode(5, 2, 1);
	//cout << "tc2: " << tc2.ToString() << endl;
	tc2.SetHours(0);
	assert(tc2.ToString() == "0:2:1");
	
	TimeCode tc3 = TimeCode(24, 34, 6);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	tc3.SetHours(52);
	assert(tc3.ToString() == "52:34:6");

	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}

void TestReset(){
	cout << "Testing reset()" << endl;
	TimeCode tc1 = TimeCode(20,10,6);
	tc1.reset();
	assert(tc1.ToString() == "0:0:0");
	cout << "PASSED!" << endl << endl;

}

void TestComparisonOperators(){
	cout << "Testing TestComparisonOperators () " << endl;
	TimeCode tc1;
	TimeCode tc2 = TimeCode(1,9,7);
	
	assert((tc1 < tc2) == true);
	assert((tc2 > tc1) == true);
	assert((tc2 == tc1) == false );
	assert((tc1 >= tc2) == false);
	assert((tc2 <= tc1) == false);
	assert((tc1 != tc2) == true);	
	
	
	tc1 = tc2; // both are equal test
	assert((tc1 < tc2) == false);
	assert((tc2 > tc1) == false);
	assert((tc2 == tc1) == true );
	assert((tc1 >= tc2) == true);
	assert((tc2 <= tc1) == true);
	assert((tc1 != tc2) == false);

	TimeCode tc3 = TimeCode(1512451,10,12);
	TimeCode tc4 = TimeCode(124,14,9);
	assert((tc4 < tc3) == true);
	assert((tc3 > tc4) == true);
	assert((tc3 == tc4) == false);
	assert((tc3 >= tc4) == true);
	assert((tc4 <= tc3) == true);
	assert((tc4 != tc3) == true);

	cout << "PASSED!" << endl << endl;  
}

void TestGetTimeCodeAsSeconds(){
	cout << "Testing GetTimeCodeAsSeconds() " << endl;
	TimeCode t = TimeCode(294,49,7);
	assert(t.GetTimeCodeAsSeconds() == 1061347);
	t.reset();
	assert(t.GetTimeCodeAsSeconds() == 0);
	t.reset();
	t = TimeCode(10,10,10);
	assert(t.GetTimeCodeAsSeconds() == 36610);
	cout << "PASSED!" << endl << endl;
}

	
int main(){
	TestReset();
	TestSecondaryConstructor();
	TestComparisonOperators();
	TestMultiply();
	TestDivide();
	TestAdd();
	TestSetHours();
	TestSetMinutes();
	TestSetSeconds();
	TestGetHours();
	TestGetMinutes();
	TestGetComponents();
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestSubtract();
	TestGetTimeCodeAsSeconds();
		
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}
