//Arranged Code na plus removed some comments
//case 7
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <list>
#include <stdio.h>
#include "Data.h"
using namespace std;
using namespace ns;

// ---------------------------------
// ---CUSTUOMER QUEUE FUNCTIONS ----
// ---------------------------------
CustomerQueue::CustomerQueue() {
	readCustomerFile();
}

// Read the customer.txt
// then put it in a queue
void CustomerQueue::readCustomerFile() {
	string line;
	customerItem newCustomer;

	ifstream inFile("customer.txt");
	while (!inFile.eof()) {

		getline(inFile, line);
		newCustomer.customerId = stoi(line);
		getline(inFile, line);
		newCustomer.name = line;
		getline(inFile, line);
		newCustomer.address = line;
		q.push(newCustomer);
	}
	inFile.close();
}



//ADD NEW CUSTOMER
void CustomerQueue::addNewCustomer() {
	remove("customerTemp.txt");
	remove("customer_rentTemp.txt");
	ifstream inFile1("customer.txt");
	ifstream inFile2("customer_rent.txt");
	ofstream outFile1("customerTemp.txt");
	ofstream outFile2("customer_rentTemp.txt");


	int currentSize = 0;
	string line1;
	string line2;
	while (!inFile1.eof()) {
		for (int i = 0; i < 3; i++) {
			getline(inFile1, line1);
			outFile1 << line1 << endl;
		}
		currentSize++;
	}

	while (!inFile2.eof()) {
		for (int i = 0; i < 2; i++) {
			getline(inFile2, line2);
			outFile2 << line2 << endl;
		}
	}

	string name, address;
	cout << "Customer ID: " << ++currentSize << endl;
	outFile1 << currentSize << endl;
	outFile2 << currentSize << endl;
	cout << "Name: ";
	// ws consumes whitepsaces
	getline(cin >> ws, name);
	cout << "Address: ";
	getline(cin >> ws, address);
	outFile1 << name << endl;
	outFile1 << address;



	inFile1.close();
	inFile2.close();
	outFile1.close();
	outFile2.close();

	remove("customer_rent.txt");
	remove("customer.txt");
	char oldname1[] = "customer_rentTemp.txt";
	char newname1[] = "customer_rent.txt";
	rename(oldname1, newname1);
	char oldname2[] = "customerTemp.txt";
	char newname2[] = "customer.txt";
	rename(oldname2, newname2);

	readCustomerFile();

}



// ADD VIDEO ID 
// TO THE USER ON CUSTOMER_RENT FILE
// stored the vids in list then
// just appended the new video
// sub function for the rentMovie method
void CustomerQueue::addVideoId(int videoId, int& found) {
	list<int> myList;
	list<int>::iterator iter;
	ifstream inFile("customer_rent.txt");
	ofstream outFile("customer_rentTemp.txt");

	string line;
	string vidInString;
	while (!inFile.eof()) {
		getline(inFile, line);

		// To check if end of line
		// so that we don't have
		// extra 1 line on txt
		if (inFile.eof()) {
			outFile << line;
		}
		else {
			outFile << line << endl;
		}
		if (line == to_string(curUser.id)) {
			getline(inFile, line);

			for (int i = 0; i < line.length(); i++) {
				if (line[i] != ',') {
					vidInString += line[i];
				}
				else {
					// ALL THE CONTENTS OF MOVIE IDs 
					// THAT's WRITTEN IN THE TXT FILE
					// WILL BE PUSHED

					if (stoi(vidInString) == videoId) {
						found = 1;
						cout << "You already rented the video id: " << videoId << endl;
						inFile.close();
						outFile.close();
						remove("customer_rentTemp.txt");
						return;
					}
					else {
						myList.push_back(stoi(vidInString));
					}
					vidInString = "";
				}

			}
			myList.push_back(videoId);

			// the content of the list will
			// be output to the file
			for (iter = myList.begin(); iter != myList.end(); iter++)
				outFile << *iter << ",";
			outFile << endl;

		}

	}
	inFile.close();
	outFile.close();

	remove("customer_rent.txt");
	char oldname[] = "customer_rentTemp.txt";
	char newname[] = "customer_rent.txt";
	rename(oldname, newname);

}






// GET CUSTOMER DATA
// Used Queue as data structure
void CustomerQueue::getCustomer(int searchId, bool& found) {
	found = false;
	int size = q.size();
	for (int i = 0; i < size; i++) {
		if (q.front().customerId == searchId) {
			found = true;
			// output the info about the user
			cout << "Name: " << q.front().name << endl;
			cout << "Address: " << q.front().address << endl << endl;

			// make the login user the current user;
			curUser.id = q.front().customerId;
			curUser.name = q.front().name;
			curUser.address = q.front().address;
		}
		q.pop();
	}
	if (found == false) {
		cout << "Customer ID not found!\n";
	}
	// re-innitialize queue
	readCustomerFile();
}

// DELETE VIDEO ID 
// TO THE USER ON CUSTOMER_RENT FILE
// used linked list to store the videos
// the deleted video id is skip in pushing the vids
// sub function in the returnMovie method
void CustomerQueue::deleteVideoId(int videoId) {
	list<int> myList;
	list<int>::iterator iter;

	ifstream inFile("customer_rent.txt");
	ofstream outFile("customer_rentTemp.txt", std::ios_base::app);

	string line;
	string vidInString;
	while (!inFile.eof()) {
		getline(inFile, line);



		// To check if end of line
		// so that we don't have
		// extra 1 line on txt
		if (inFile.eof()) {
			outFile << line;
		}
		else {
			outFile << line << endl;
		}

		if (line == to_string(curUser.id)) {
			getline(inFile, line);
			for (int i = 0; i < line.length(); i++) {

				if (line[i] != ',') {

					vidInString += line[i];

				}
				else {
					// ALL THE CONTENTS OF MOVIE IDs 
					// THAT's WRITTEN IN THE TXT FILE
					// WILL BE PUSHED

					if (stoi(vidInString) != videoId) {
						myList.push_back(stoi(vidInString));
					}
					vidInString = "";
				}

			}
			// the content of the list will
			// be output to the file
			for (iter = myList.begin(); iter != myList.end(); iter++)
				outFile << *iter << ",";
			outFile << endl;
		}
	}
	inFile.close();
	outFile.close();

	remove("customer_rent.txt");
	char oldname[] = "customer_rentTemp.txt";
	char newname[] = "customer_rent.txt";
	rename(oldname, newname);

}




// LIST ALL THE VIDEO RENTED BY A CUSTOMER
// USED STACK AS DATA STRUCTURE
// stored the video IDs rented by a customer
void CustomerQueue::listAllVidRented() {
	//init stack
	stack< int > rentStack;

	// Read the customer_rent
	ifstream inFile("customer_rent.txt");
	string id;
	// ask for an ID
	cout << "Cutomer ID: ";
	cin >> id;
	bool found;
	getCustomer(stoi(id), found);
	cout << endl;
	if (found == false) {
		return;
	}
	string line;

	string vidInString;

	while (!inFile.eof()) {

		getline(inFile, line);
		string idFtext = line;

		if (idFtext == id) {
			getline(inFile, line);
			for (int i = 0; i < line.length(); i++) {
				if (line[i] != ',') {

					vidInString += line[i];


				}
				else {
					// ALL THE CONTENTS OF MOVIE IDs 
					// THAT's WRITTEN IN THE TXT FILE
					// WILL BE PUSHED
					rentStack.push(stoi(vidInString));
					vidInString = "";
				}
			}
		}
	}
	// TO OUTPUT THE ID AND MOVIE TITLE
	MovieList movie;
	int catcher;
	string titleCatcher;
	while (!rentStack.empty()) {
		cout << "Video ID: " << rentStack.top() << endl;
		cout << "Title: " << movie.getTitle(rentStack.top()) << endl << endl;
		rentStack.pop();
	}

	inFile.close();

}
