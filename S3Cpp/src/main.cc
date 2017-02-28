//============================================================================
// Name        : cppS3.cpp
// Author      : cheng.zhang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>

#include "op_s3.h"
using namespace std;


int main() {
	string accessKey = "0555b35654ad1656d804";
	string secretKey = "h7GhxuBLTrlhVUyxSPUKUV8r/2EI4ngqJxD7iBdBYLhwluN30JaT3Q==";
	string endPoint  = "http://localhost:8000";
	HttpS3 hs;
	OpS3 os(accessKey,secretKey,endPoint,&hs);

	cout<< os.listBucket()<<endl;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
