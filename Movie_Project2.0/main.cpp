#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <list>
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
  

  int currentSize;
  MovieNode *head; // List head pointer


public:
  MovieList();	// Constructor
  ~MovieList(); // Destructor
  void getAllMovies();
  void getMovie(int searchId );
  string getTitle(int searchId);
  void rentMovie();
  void returnMovie();
  void addMovie();

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
			//string rentedVids;
			
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
	  void deleteVideoId(int videoId);
	  void addVideoId(int videoId, int &found);
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

void MovieList::addMovie(){
	ifstream inFile("video.txt");
	string line;
	getline (inFile, line);
	currentSize = stoi(line);
	currentSize++;
	
	string title,genre,prod,filePath;
	int numCopies;

	cout <<"Video ID: " << currentSize << endl;
	cout <<"Title: " ;
	cin >> title;
	cout <<"Genre: " ;
	cin >> genre;
	cout <<"Production: ";
	cin >> prod;
	cout <<"Number of Copies: " ;
	cin >> numCopies;
	cout <<"Filepath/Image: " ;
	cin >> filePath;
	
	MovieNode *newNode, *nodePtr;
	
	newNode = new MovieNode;
	
	newNode->id = currentSize;
    newNode->name = title;
    newNode->genre = genre;
    newNode->production = prod;
    newNode->numCopies = numCopies;
    newNode->filePath = filePath;
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



void MovieList::getAllMovies(){
  system("clear");
  MovieNode *nodePtr;
	if (head==NULL)
		cout << "The List is empty!" << endl;
	else {
		nodePtr = head;
    cout << "The Movies: \n";
		while (nodePtr){
			cout << endl <<"Video ID: " << nodePtr->id << endl;
			cout <<"Title: " << nodePtr->name << endl;
			cout <<"Genre: " <<  nodePtr->genre << endl;
			cout <<"Production: " <<  nodePtr->production << endl;
			cout <<"Number of Copies: " <<  nodePtr->numCopies << endl;
			cout <<"Filepath/Image: " <<  nodePtr->filePath << endl << endl;
	  		nodePtr = nodePtr->next;
		}	
	}
}

void MovieList::getMovie(int searchId ){
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
        break;
      } 
      nodePtr = nodePtr->next;
 
    }
   if (!nodePtr) {
	cout << "MOVIE NOT FOUND!" << endl;
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
void MovieList::rentMovie(){
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
  
	MovieNode *nodePtr;

	// update the movie linked list
	if (head==NULL) 
		cout << "The List is empty!" << endl;
	else {
		nodePtr = head;
		while (nodePtr){
		  if(nodePtr->id == vidId){
		  	if(nodePtr->numCopies > 0){
		    	int foundCatcher = 0;
		    	customerQ.addVideoId(vidId,foundCatcher);
		    	if(foundCatcher != 1){
		    		nodePtr->numCopies--;
				}
			}
		  } 
		  nodePtr = nodePtr->next;
		}

	}
	getMovie(vidId);



}


// renting a video process
void MovieList::returnMovie(){
	
	MovieNode *nodePtr;
	CustomerQueue customerQ;
	int customerId;
	
	//asking for customer id
	cout << "Customer ID: ";
	cin >> customerId;
	customerQ.getCustomer(customerId);
	int vidId;
	cout << "Video ID: ";
	cin >> vidId;
    if (head==NULL) 
    	cout << "The List is empty!" << endl;
  else {
    nodePtr = head;
    while (nodePtr){
      // to output the requested movie
      if(nodePtr->id == vidId){
      
      		customerQ.deleteVideoId(vidId);
			nodePtr->numCopies++;
     		cout << "The Video ID " << vidId << " is now returned"<< endl;
		


      } 
      nodePtr = nodePtr->next;
    }
  }
}







// ---------------------------------
// ---CUSTUOMER QUEUE FUNCTIONS ----
// ---------------------------------
CustomerQueue::CustomerQueue(){
  readCustomerFile();
}

//delete the video ID from customer_rent.txt
void CustomerQueue::deleteVideoId(int videoId){
	list<int> myList;
    list<int>::iterator iter;

	ifstream inFile("customer_rent.txt");
	ofstream outFile("customer_rentTemp.txt", std::ios_base::app);
	
	string line;
	string vidInString;
	while(!inFile.eof()){
		getline (inFile, line);
		
		// To check if end of line
		// so that we don't have
		// extra 1 line on txt
		if(inFile.eof()){
			outFile << line;
		} else {
			outFile << line << endl;
		}
		
		if(line == to_string(curUser.id)){
			getline (inFile, line);
			for(int i = 0;i < line.length();i++){
			
				if(line[i] != ','){
					
					vidInString += line[i];
		
				} else {
					// ALL THE CONTENTS OF MOVIE IDs 
					// THAT's WRITTEN IN THE TXT FILE
					// WILL BE PUSHED
					
					if(stoi(vidInString) != videoId){
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
	
	remove( "customer_rent.txt" );
	char oldname[] ="customer_rentTemp.txt";
	char newname[] ="customer_rent.txt";
	rename( oldname , newname );

}

// Add video to the customer on customer_rent.txt
void CustomerQueue::addVideoId(int videoId, int &found){
	list<int> myList;
    list<int>::iterator iter;
	ifstream inFile("customer_rent.txt");
	ofstream outFile("customer_rentTemp.txt");
	
	string line;
	string vidInString;
	while(!inFile.eof()){
		getline (inFile, line);
		
		// To check if end of line
		// so that we don't have
		// extra 1 line on txt
		if(inFile.eof()){
			outFile << line;
		} else {
			outFile << line << endl;
		}
		if(line == to_string(curUser.id)){
			getline (inFile, line);
	
			for(int i = 0;i < line.length();i++){
				if(line[i] != ','){
					vidInString += line[i];
				} else {
					// ALL THE CONTENTS OF MOVIE IDs 
					// THAT's WRITTEN IN THE TXT FILE
					// WILL BE PUSHED
					
					if(stoi(vidInString) == videoId){
						found = 1;
						cout << "You already rented: " << videoId << endl;
			     		inFile.close();
						outFile.close();
			     		remove( "customer_rentTemp.txt" );
			     		return;
			    	} else {
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

	remove( "customer_rent.txt" );
	char oldname[] ="customer_rentTemp.txt";
	char newname[] ="customer_rent.txt";
	rename( oldname , newname );

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
    //getline (inFile, line);
    //newCustomer.rentedVids = line;

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
  //movie.returnMovie();
  //q.listAllVidRented();
  //movie.getMovie(14);
 // movie.returnMovie();
  //movie.getMovie(14);
  //movie.rentMovie();
	movie.addMovie();
	movie.getAllMovies();
}










