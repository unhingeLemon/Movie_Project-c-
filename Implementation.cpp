#include <iostream>
#include "Data.h"

using namespace std;
using namespace ns;

// basically all our functions *part of main class* will go here
// e.g append,insert,delete,traverse
// VINCENT 

MovieList::MovieList()
{
	head = NULL;
}

// VINCENT
MovieList::~MovieList(){
MovieNode *nodePtr, *nextNode;
	nodePtr = head;
	while (nodePtr != NULL){
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

void MovieList::insertMovie(int cd, string name, string gen, int yr){
   system("clear");
  MovieNode *newNode, *nodePtr;
	// Allocate a new node & store num
	newNode = new MovieNode;
	newNode->code = cd;
  newNode->title = name;
  newNode->genre = gen;
  newNode->year = yr;
	newNode->next = NULL;

  if(!head){
    head = newNode;
  }
  else{
     nodePtr = head;
     	while (nodePtr->next)
	  nodePtr = nodePtr->next; 
	// Insert newNode as the last node
	nodePtr->next = newNode;	
  }
	
}	

// CHARLES
void MovieList::printMovieList(){
  system("clear");
  MovieNode *nodePtr;
	if (head==NULL)
		cout << "The List is empty!" << endl;
	else {
		nodePtr = head;
    cout << "The Movies: \n";
		while (nodePtr){
			cout << endl <<"Code: " << nodePtr->code << endl;
      cout <<"Title: " << nodePtr->title << endl;
      cout <<"Genre: " <<  nodePtr->genre << endl;
      cout <<"Year Released: " <<  nodePtr->year << endl << endl;
	    nodePtr = nodePtr->next;
		}	
	}

}


// VINCENT //delete 
void MovieList::rentMovie(int cd){
   system("clear");
	MovieNode *nodePtr, *previousNode;
	int found = 0;
	// If the list is empty, do nothing.
	if (!head){
		return; 
	}
	// Determine if the first node is the one.
	if (head->code == cd){
		nodePtr = head->next;
		delete head;
		head = nodePtr;
		found = 1;
	}else{
		// Initialize nodePtr to head of list
		nodePtr = head;
		previousNode = NULL;
		// Skip all nodes whose value member is
		// not equal to num.
		while (nodePtr != NULL && nodePtr->code != cd){
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		// Link the previous node to the node after
		// nodePtr, then delete nodePtr.
    if (nodePtr != NULL){
			previousNode->next = nodePtr->next;
			delete nodePtr;
			found = 1;
		}  
	}
  cout << "You have rented the movie with code: " << cd <<"\n\n";
}

// CHARLES
void MovieList::returnMovie(int cd, string name, string gen, int yr){
   system("clear");
 MovieNode *newNode, *nodePtr;
	newNode = new MovieNode;
	newNode->code = cd;
  newNode->title = name;
  newNode->genre = gen;
  newNode->year = yr;
	newNode->next = NULL;

  if(!head){
    head = newNode;
  }
  else{
     nodePtr = head;
     	while (nodePtr->next)
	  nodePtr = nodePtr->next; 
  // Append it again to the list
	nodePtr->next = newNode;	
  }
}



// CHARLES
void MovieList::showMovieDetails(int cd){
   system("clear");
   MovieNode *nodePtr;
	if (head == NULL){
    	cout << "The list is empty!" << endl;
  }else{
    nodePtr = head;
		while (nodePtr){	
			if(nodePtr->code == cd){
        cout << "\nThe information on that Movie code is:  \n";
        cout <<"Code: " << nodePtr->code << endl;
        cout <<"Title: " << nodePtr->title << endl;
        cout <<"Genre: " <<  nodePtr->genre << endl;
        cout <<"Year Released: " <<  nodePtr->year << "\n\n";
        break;
      }
      nodePtr = nodePtr->next;
      /// NAGANA NA TO
      if(nodePtr==NULL) {
          cout << "Invalid Code\n";
          break;
     }
		}
    // VALIDATE THE INPUTTED CODE
	}
}
