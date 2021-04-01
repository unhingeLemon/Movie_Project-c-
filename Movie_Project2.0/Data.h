#pragma once
using namespace std;
#include <queue>

namespace ns {
	// NEED 2 ADTs 


	class MovieList {
	private:
		struct MovieNode {
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
			struct MovieNode* next;
		};
		int currentSize;
		MovieNode* head; // List head pointer


	public:
		MovieList();	// Constructor
		~MovieList(); // Destructor
		void getAllMovies();
		void getMovie(int searchId);
		string getTitle(int searchId);
		void rentMovie();
		void returnMovie();
		void addMovie();
		void checkVideoAvail(int searchId);
		void saveMovieList();

	};


	// SHOULD BE ON QUEUE DAW
	class CustomerQueue {
	private:
		// CUSTOMER ID

		struct customerItem {
			int customerId;
			string name;
			string address;
			//rentedvids must be in stack
			//string rentedVids;
		};

		struct currentUser {
			int id;
			string address;
			string name;
		};

		queue<customerItem> q;
		currentUser curUser;




	public:
		CustomerQueue();	// Constructor
		//~CustomerQueue();	// Destructor
		void getCustomer(int searchId, bool& found);
		void readCustomerFile();
		void listAllVidRented();
		void deleteVideoId(int videoId);
		void addVideoId(int videoId, int& found);
		void addNewCustomer();
	};



}