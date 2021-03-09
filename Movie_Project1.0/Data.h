//CAPILI
#pragma once
using namespace std;

  // the main class will go here
  // EACH NODE DATA:
  // Movie Code
  // Movie Title
  // Movie Genre
  // Year Released
  
namespace ns {
  class MovieList {
  private:
    struct MovieNode{
      int code;
      string title;
      string genre;
      int year;
      struct MovieNode *next;
    };
    
    MovieNode *head;	// List head pointer

  public:
    MovieList();	// Constructor
    ~MovieList(); // Destructor
    void insertMovie(int cd, string name, string gen, int yr);
    void rentMovie(int cd);
    void returnMovie(int cd, string name, string gen, int yr);
    void showMovieDetails(int cd);
    void printMovieList();

  };
}


