#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;


class MovieList {
private:
  struct MovieNode{
    // VIDEO ID
    // MOVIE TITLE
    // GENRE
    // PRODUCTION
    // NUMBER OF COPIES
    // MOVIE IMAGE FILEPATH
    int id;
    // string ang ID para di tayo mahirapan isearch
    // pm me for more info haha
    // or see the video.txt
    string name;
    string genre;
    string production;
    int numCopies;
    string filePath;
    struct MovieNode *next; 
  };
  

  
  MovieNode *head; // List head pointer


public:
  MovieList();	// Constructor
  ~MovieList(); // Destructor
  void getAllMovies();
  void getMovie(int searchId,bool rented);
  string getTitle(int searchId);
  void rentVideo();
  void returnVideo();
 

};


// SHOULD BE ON QUEUE DAW
class CustomerQueue{
	private:
	  // CUSTOMER ID
	
		struct customerItem{
			int customerId;
			string name;
			string address;
			//rentedvids must be in stack
			string rentedVids;
			
		};
	  
		struct rentStack{
			int videoId;
			rentStack *next;
		};
		rentStack *top;
		
	
		struct currentUser{
		int id;
		string address;
		string name;
		};
	  queue<customerItem> q;
	  currentUser curUser;
	 
	
	
	public:
	  CustomerQueue();	// Constructor
	  //~CustomerQueue();	// Destructor
	  void getCustomer(int searchId);
	  void readCustomerFile();
	  void listAllVidRented();
	  void pushRentStack(int id);
	  bool isStackEmpty();
	  void returnVid(int &num);

};



// this reads the video file
// and construct it on the linked list
MovieList::MovieList(){
	head = NULL;
  string line;
  ifstream inFile("video.txt", std::ios_base::app);
  // first line is the number of movies
  getline (inFile, line);

    MovieNode *newNode, *nodePtr;
	// Allocate a new node & store num

  // while it is not the end of file
  while(!inFile.eof()){
    newNode = new MovieNode;
    getline (inFile, line);
    // cut the id_ to the string 
    // so that only the int will return
    int id = stoi(line.substr(3,line.size()));
    newNode->id = id;
    getline (inFile, line);
    newNode->name = line;
    getline (inFile, line);
    newNode->genre = line;
    getline (inFile, line);
    newNode->production = line;
    getline (inFile, line);
    newNode->numCopies = stoi(line);
    getline (inFile, line);
    newNode->filePath = line;
    newNode->next = NULL;

    if(!head){
      head = newNode;
    } else{
      nodePtr = head;
      while (nodePtr->next)
      nodePtr = nodePtr->next; 
      // Insert newNode as the last node
      nodePtr->next = newNode;	
    }  
  }
  inFile.close();
  
}

MovieList::~MovieList(){
  MovieNode *nodePtr, *nextNode;
    nodePtr = head;
    while (nodePtr != NULL){
      nextNode = nodePtr->next;
      delete nodePtr;
      nodePtr = nextNode;
    }
}


void MovieList::getAllMovies(){
  system("clear");
  MovieNode *nodePtr;
	if (head==NULL)
		cout << "The List is empty!" << endl;
	else {
		nodePtr = head;
    cout << "The Movies: \n";
		while (nodePtr){
			cout << endl <<"ID: " << nodePtr->id << endl;
      cout <<"TITLE: " << nodePtr->name << endl;
      cout <<"GENRE: " <<  nodePtr->genre << endl;
      cout <<"PRODUCTION: " <<  nodePtr->production << endl;
      cout <<"NUMBER OF COPIES: " <<  nodePtr->numCopies << endl;
      cout <<"FILEPATH/IMAGE: " <<  nodePtr->filePath << endl << endl;
	    nodePtr = nodePtr->next;
		}	
	}
}

void MovieList::getMovie(int searchId,bool rented){
  MovieNode *nodePtr;
  if (head==NULL) 
    cout << "The List is empty!" << endl;
  else {
    nodePtr = head;
    while (nodePtr){
      // to output the requested movie
      if(nodePtr->id == searchId){
        cout << "Movie Title: " << nodePtr->name << endl;
        cout << "Number of Copies: " << nodePtr->numCopies << endl;
        // if it is rented
        if(rented){
          nodePtr->numCopies--;
        }
      } 
      nodePtr = nodePtr->next;
    }
  }
}
string MovieList::getTitle(int searchId){
  MovieNode *nodePtr;
  if (head==NULL) 
    return "The List is empty!";
  else {
    nodePtr = head;
    while (nodePtr){
      // to output the requested movie
      if(nodePtr->id == searchId){
        return nodePtr->name;
      } 
      nodePtr = nodePtr->next;
    }

  }
	  
return "TITLE NOT FOUND";
	
}

// renting a video process
void MovieList::rentVideo(){
  CustomerQueue customerQ;
  int customerId;
  int vidId;

  //asking for customer id
  cout << "Customer ID: ";
  cin >> customerId;
  customerQ.getCustomer(customerId);

  // asking for inputs
  cout << "\nVideos to rent ..\n\n";
  cout << "Video ID: ";
  cin >> vidId;
  // to output the movie
  
  getMovie(vidId,true);

}


// renting a video process
void MovieList::returnVideo(){
	MovieNode *nodePtr, *previousNode;
	int vidId;
	cout << "Video ID: ";
	cin >> vidId;
	// Determine if the first node is the one.
	if (head->id == vidId){
		nodePtr = head->next;
		delete head;
		head = nodePtr;
		cout << "Video ID: " << vidId <<  " is now returned"<< endl;
		getAllMovies();
	}else{
		// Initialize nodePtr to head of list
		nodePtr = head;
		previousNode = NULL;
		// Skip all nodes whose value member is
		// not equal to num.
		while (nodePtr != NULL && nodePtr->id != vidId){
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		// Link the previous node to the node after
		// nodePtr, then delete nodePtr.
		if (nodePtr !=NULL){
			previousNode->next = nodePtr->next;
			delete nodePtr;
			cout << "Video ID: " << vidId << " is now returned"<< endl;
		}
	}
}


// ---------------------------------
// ---CUSTUOMER QUEUE FUNCTIONS ----
// ---------------------------------
CustomerQueue::CustomerQueue(){
  readCustomerFile();
}


// Read the customer.txt
// then put it in a queue
void CustomerQueue::readCustomerFile(){
string line;

  ifstream inFile("customer.txt");
  while(!inFile.eof()){
    customerItem newCustomer;
    getline (inFile, line);
    newCustomer.customerId = stoi(line);
    getline (inFile, line);
    newCustomer.name = line;
    getline (inFile, line);
    newCustomer.address = line;
    getline (inFile, line);
    newCustomer.rentedVids = line;

    q.push(newCustomer);
  }
  inFile.close();
}


// this is to output the queue
void CustomerQueue::getCustomer(int searchId){
  int size = q.size();


  for(int i=0;i<size;i++){
    if(q.front().customerId == searchId){
      // output the info about the user
      cout << "Name: "<< q.front().name << endl;
      cout << "Address: "<< q.front().address << endl;

      // make the login user the current user;
      curUser.id = q.front().customerId;
      curUser.name = q.front().name;
      curUser.address = q.front().address;
    } 
    q.pop();
  }
  // re-innitialize queue
  readCustomerFile();
}


void CustomerQueue::listAllVidRented(){
	// Read the customer_rent
	ifstream inFile("customer_rent.txt");
	string id;
	// ask for an ID
	cout << "Cutomer ID: ";
	cin >> id;
	getCustomer(stoi(id));
	string line;
	
	string vidInString; 

	while(!inFile.eof()){
	
		getline (inFile, line);
		string idFtext = line;
		
		if(idFtext == id){
			getline (inFile, line);
			for(int i = 0;i < line.length();i++){
				if(line[i] != ','){
					
					vidInString += line[i];
					
					
				} else {
					// ALL THE CONTENTS OF MOVIE IDs 
					// THAT's WRITTEN IN THE TXT FILE
					// WILL BE PUSHED
					pushRentStack(stoi(vidInString));
					vidInString = "";
				}
			}
		}
		
	}
	
	
	// TO OUTPUT THE ID AND MOVIE TITLE
	MovieList movie;
	int catcher;
	string titleCatcher;
	while(!isStackEmpty()){
		returnVid(catcher);
		cout << "Video ID: " << catcher << endl;

		cout << "TITLE: " << movie.getTitle(catcher) << endl << endl;
	}
	
	
	inFile.close();
	
}

// CUSTOMER RENT FUNCTIONS





void CustomerQueue::pushRentStack(int id){
	rentStack *newNode;
	// Allocate a new node & store Num
	newNode = new rentStack;
	newNode->videoId = id;

	// If there are no nodes in the list
	// make newNode the first node
	if (isStackEmpty()){
		top = newNode;
		newNode->next = NULL;
	} else{ // Otherwise, insert NewNode before top
		newNode->next = top;
		top = newNode;
	}
}

bool CustomerQueue::isStackEmpty(){
	bool status;
	if (!top)
		status = true;
	else
		status = false;
	return status;
}

void CustomerQueue::returnVid(int &num){
	rentStack *temp;
	if (isStackEmpty()){
		cout << "The stack is empty.\n";
	}else{ // pop value off top of stack
		num = top->videoId;
		temp = top->next;
		delete top;
		top = temp;
	}
}






int main(){
  MovieList movie;
  CustomerQueue q;
  //movie.getAllMovies();
  //movie.returnVideo();
  q.listAllVidRented();

}










