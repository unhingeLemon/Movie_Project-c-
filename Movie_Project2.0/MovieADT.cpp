#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <limits>
#include <iomanip>
#include "Data.h"

#include <opencv2/opencv.hpp>
using namespace cv;

using namespace std;
using namespace ns;


void showImage(string filePath, string title) {
 	Mat img = imread(filePath);
 	namedWindow(title, WINDOW_NORMAL);
 	imshow(title, img);
 	waitKey(0);

}



// This reads the video file
// and construct it on the linked list
MovieList::MovieList() {
	head = NULL;
	string line;
	ifstream inFile("video.txt", std::ios_base::app);
	// first line is the number of movies
	// so we must skip it
	// and put in in the currentSize var
	getline(inFile, line);
	currentSize = stoi(line);
	MovieNode* newNode, * nodePtr;


	// while it is not the end of file
	while (!inFile.eof()) {
		newNode = new MovieNode;
		getline(inFile, line);

		// cut the id_ to the string 
		// so that only the int will return
		int id = stoi(line.substr(3, line.size()));
		newNode->id = id;
		getline(inFile, line);
		newNode->name = line;
		getline(inFile, line);
		newNode->genre = line;
		getline(inFile, line);
		newNode->production = line;
		getline(inFile, line);
		newNode->numCopies = stoi(line);
		getline(inFile, line);
		newNode->filePath = line;
		newNode->next = NULL;

		if (!head) {
			head = newNode;
		}
		else {
			nodePtr = head;
			while (nodePtr->next)
				nodePtr = nodePtr->next;
			// Insert newNode as the last node
			nodePtr->next = newNode;
		}
	}

	inFile.close();

}

// Destructor
MovieList::~MovieList() {
	MovieNode* nodePtr, * nextNode;
	nodePtr = head;
	while (nodePtr != NULL) {
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

//case 1
// Add movie to the linked list of movies
void MovieList::addMovie() {


	string title, genre, prod, filePath;
	int numCopies;

	cout << "  Video ID: " << ++currentSize << endl;
	cout << "  Title: ";
	getline(cin >> ws, title);
	cout << "  Genre: ";
	getline(cin >> ws, genre);
	cout << "  Production: ";
	getline(cin >> ws, prod);
a:
	cout << "  Number of Copies: ";
	cin >> numCopies;
	while (!cin.good()) {
		cin.clear();
		cout << "\n  Invalid input!\n";
		cout << "  Input new value again\n\n";
		//from #include <limits>
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "  Number of Copies: ";
		cin >> numCopies;
	}

	cout << "  Filepath/Image: ";
	getline(cin >> ws, filePath);

	MovieNode* newNode, * nodePtr;

	newNode = new MovieNode;

	newNode->id = currentSize;
	newNode->name = title;
	newNode->genre = genre;
	newNode->production = prod;
	newNode->numCopies = numCopies;
	newNode->filePath = filePath;
	newNode->next = NULL;

	if (!head) {
		head = newNode;
	}
	else {
		nodePtr = head;

		while (nodePtr->next)
			nodePtr = nodePtr->next;
		// Insert newNode as the last node
		nodePtr->next = newNode;
	}

}


//case 2
// renting a video process
// updating a node in our linked list
// numCopies--
// then add the rented movie id to 
// the customer_rent txt file
void MovieList::rentMovie() {
	CustomerQueue customerQ;
	int customerId;
	int vidId;
a:
	cout << "  Customer ID: ";
	cin >> customerId;

	if (cin.fail()) {
		cin.clear();
		cout << "\n  Invalid input!\n";
		cout << "  Input new value again\n\n";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		goto a;
	}
	else {
		bool found;
		customerQ.getCustomer(customerId, found);
		if (found == false) {
			return;
		}

		// asking for inputs
		MovieNode* nodePtr;
		cout << "\n  Videos to rent ..\n\n";
	b:
		cout << "  Video ID: ";
		cin >> vidId;
		if (cin.fail())
		{
			cin.clear();
			cout << "\n  Invalid input!\n";
			cout << "  Input new value again\n\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			goto b;
		}
		else {
			// update the movie linked list
			if (head == NULL)
				cout << "  The List is empty!" << endl;
			else {
				nodePtr = head;
				while (nodePtr) {
					if (nodePtr->id == vidId) {
						if (nodePtr->numCopies > 0) {
							int foundCatcher = 0;
							// add video ID dun sa customer rent
							customerQ.addVideoId(vidId, foundCatcher);
							if (foundCatcher != 1) {
								nodePtr->numCopies--;
							}
						}
						else {
							// if negeta
							// prompt the user na wala ng Copies avail
						}
					}
					nodePtr = nodePtr->next;
				}
				getMovie(vidId);
			}
		}
	}
	//asking for customer id


}

// case 3
// deleting the movie id on the 
// customer rented videos
void MovieList::returnMovie() {

	MovieNode* nodePtr;
	CustomerQueue customerQ;
	int customerId;
a:
	cout << "  Customer ID: ";
	cin >> customerId;
	if (cin.fail())
	{
		cin.clear();
		cout << "\n  Invalid input!\n";
		cout << "  Input new value again\n\n";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		goto a;
	}
	else {
		bool found;
		customerQ.getCustomer(customerId, found);
		if (found == false) {
			return;
		}

		int vidId;
	b:
		cout << endl << "  Video ID: ";
		cin >> vidId;
		if (cin.fail())
		{
			cin.clear();
			cout << "\n  Invalid input!\n";
			cout << "  Input new value again\n\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			goto b;
		}
		else {
			if (head == NULL)
				cout << "  The List is empty!" << endl;
			else {
				nodePtr = head;
				while (nodePtr) {
					// to output the requested movie
					if (nodePtr->id == vidId) {

						customerQ.deleteVideoId(vidId);
						nodePtr->numCopies++;
						cout << "  The Video ID " << vidId << " is now returned" << endl;
					}
					nodePtr = nodePtr->next;
				}
				//asking for customer id	   
			}
		}
	}
}

//case 4
// Get Movie Details
void MovieList::getMovie(int searchId) {
	MovieNode* nodePtr;
	if (head == NULL)
		cout << "  The List is empty!" << endl;
	else {
		nodePtr = head;
		while (nodePtr) {
			// to output the requested movie
			if (nodePtr->id == searchId) {
				cout << "  Movie Title: " << nodePtr->name << endl;
				cout << "  Number of Copies: " << nodePtr->numCopies << endl;
				// FOR OPEN CV:
				showImage(nodePtr->filePath, nodePtr->name);
				break;
			}
			nodePtr = nodePtr->next;

		}
		if (!nodePtr) {
			cout << "  MOVIE NOT FOUND!" << endl;
		}


	}
}

// Get the title of the movie
//sub function of the listAllVidRented method
string MovieList::getTitle(int searchId) {
	MovieNode* nodePtr;
	if (head == NULL)
		return "  The List is empty!";
	else {
		nodePtr = head;
		while (nodePtr) {
			// to output the requested movie
			if (nodePtr->id == searchId) {
				return nodePtr->name;
			}
			nodePtr = nodePtr->next;
		}

	}

	return "  TITLE NOT FOUND";

}



//case 5
// Get all the movies
void MovieList::getAllMovies() {
	system("CLS");
	MovieNode* nodePtr;
	if (head == NULL)
		cout << "  The List is empty!" << endl;
	else {
		nodePtr = head;
		cout << "  The Movies: \n";
		cout << endl << setw(2) << "Video ID:" << setw(35) << "Title:" << setw(13) << "Genre:" << setw(27) << "Production:" << setw(14) << "Copies:";
		cout << endl;
		while (nodePtr) {

			cout << setw(5) << nodePtr->id;
			cout << setw(39) << nodePtr->name;
			cout << setw(13) << nodePtr->genre;
			cout << setw(28) << nodePtr->production;
			cout << setw(11) << nodePtr->numCopies;
			cout << endl;
			nodePtr = nodePtr->next;
		}
	}
}
//case 6
void MovieList::checkVideoAvail(int searchId) {
	MovieNode* nodePtr;
	if (head == NULL)
		cout << "  The List is empty!" << endl;
	else {
		nodePtr = head;
		while (nodePtr) {
			// to output the requested movie
			if (nodePtr->id == searchId) {
				if (nodePtr->numCopies > 0) {
					cout << "Number of Copies: " << nodePtr->numCopies;
					cout << " \nAvailable!\n";
					break;
				}
				else {
					cout << "  Not Available!\n";
				}
				break;
			}
			nodePtr = nodePtr->next;

		}
		if (!nodePtr) {
			cout << "  MOVIE NOT FOUND!" << endl;
		}

	}
}


//case 8
// Saving our movie linked list to the
// txt file
void MovieList::saveMovieList() {
	CustomerQueue q;
	ifstream inFile("video.txt");
	remove("videoTemp.txt");
	ofstream outFile("videoTemp.txt");
	string line;

	getline(inFile, line);
	//currentSize = stoi(line);
	outFile << currentSize;

	MovieNode* nodePtr;
	if (head == NULL)
		cout << "  The List is empty!" << endl;
	else {
		nodePtr = head;
		while (nodePtr) {
			getline(inFile, line);
			outFile << endl << "id_" << nodePtr->id << endl;
			outFile << nodePtr->name << endl;
			outFile << nodePtr->genre << endl;
			outFile << nodePtr->production << endl;
			outFile << nodePtr->numCopies << endl;
			outFile << nodePtr->filePath;
			nodePtr = nodePtr->next;
		}
	}


	inFile.close();
	outFile.close();

	remove("video.txt");
	char oldname[] = "videoTemp.txt";
	char newname[] = "video.txt";
	rename(oldname, newname);
}








