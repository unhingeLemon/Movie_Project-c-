#include <iostream>
#include "Data.h"
#include <ctime>
#include <cstdlib>
#include <string> 
#include <limits>
using namespace std;
using namespace ns;

// So we will have data.h and Implementation.cpp
// We are simply following the template given

// QUESTIONS
// 1 CAP
// 2 VINCENT
// 3 CHARLES
// SEND NA LANG SA GC SAGOT

// This file will be our main file
// We will write here our menus:


//CAPILI
int menu(){
  int ch;
  cout << "1. Insert a New Movie" << endl;
  cout << "2. Rent a Movie" << endl; 
  cout << "3. Return a Movie" << endl; 
  cout << "4. Show Movie Details" << endl; 
  cout << "5. Print Movie List" << endl; 
  cout << "6. Quit the Program" << endl;
  cout << "\nEnter your choice: ";
  cin >> ch;
  
  return ch;
}

//CAPILI
// This code will simply generate 5 random ints
int randomCode() {
    srand(time(0)); 
    string code;
    int c;
    for(int i=0;i<5;i++){
        c =  (rand() % 10) + 1;   
        code += to_string(c);
    }
    // String to int
    int c1 = stoi(code);
    return c1;
}

// For validating year
// to make sure that the user will
// only enter int
int enterYear(){
    int year = -1;
    bool valid= false;
    do{
      cout << "Enter Year: " << flush;
      cin >> year;
      if (cin.good()){
          //everything went well, we'll get out of the loop and return the value
          valid = true;
      }else{
          //something went wrong, we reset the buffer's state to good
          cin.clear();
          //and empty it
          cin.ignore(numeric_limits<streamsize>::max(),'\n');
          cout << "Invalid input; please re-enter." << endl;
      }
    } while (!valid);

    return (year);
}


//CAPILI
int main(){
  MovieList list;

  // Append the first 2 movies
  list.insertMovie(12345, "The Old Guard", "Action", 2020);
  list.insertMovie(67891, "Extraction", "Action/Thriller", 2020);

  //vars for inputs
  string title,genre;
  int year;

  bool loop = 1;

  do{
    int choice = menu();
    switch(choice){
      case 1:
        cout << "Enter Title: ";
  
        getline(cin >> ws,title);
        cout << "Enter Genre: ";
        getline(cin >> ws,genre);
        year = enterYear();
        list.returnMovie(randomCode(),title,genre,year);
        system("clear");
        break;
  
      case 2:
        int cd;
        cout << "Enter the Movie Code: ";
        cin >> cd;
        list.rentMovie(cd);
        break;
      case 3:
        cout << "Enter Title: ";
        getline(cin >> ws,title);
        cout << "Enter Genre: ";
        getline(cin >> ws,genre);
        year = enterYear();
        list.returnMovie(randomCode(),title,genre,year);
        system("clear");
        break;
      case 4:
        int enteredCode;
        cout << "Enter the movie code: ";
        cin >> enteredCode;
        list.showMovieDetails(enteredCode);
        break;
      case 5:
        list.printMovieList();
        break;
      case 6:
        cout << "\nThank You For Using The Program!\nWill Now Exit.\n\n";
        loop = false;
        break;
        
      default:
        cout << "Invalid choice";
        break;
    }
  } while(loop);
}

