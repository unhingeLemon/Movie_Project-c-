#include <iostream>
#include <cstdlib>
#include <string>
#include <limits>
#include <windows.h>
#include "colors.h"
#include "Data.h"


using namespace std;
using namespace ns;



//Menus of Customer Maintenance
void customerMenu() {
    cout << endl;
    cout << "    [1] Add new Customer" << endl;
    cout << "    [2] Show Customer Details" << endl;
    cout << "    [3] List Videos Rented by a Customer" << endl;
}

void vidMenu() {
    cout << "_______________________________________________________\n";
    cout << "__     ___     _              ____  _                 \n";
    cout << " \\ \\   / (_) __| | ___  ___   / ___|| |_ ___  _ __ ___ \n";
    cout << "  \\ \\ / /| |/ _` |/ _ \\/ _ \\  \\___ \\| __/ _ \\| '__/ _ \\\n";
    cout << "   \\ V / | | (_| |  __| (_) |  ___) | || (_) | | |  __/\n";
    cout << "    \\_/  |_|\\__,_|\\___|\\___/  |____/ \\__\\___/|_|  \\___|\n";
    cout << "_______________________________________________________\n\n";

    cout << "  [1] New Video" << endl;
    cout << "  [2] Rent a Video" << endl;
    cout << "  [3] Return a Video" << endl;
    cout << "  [4] Show Video Details" << endl;
    cout << "  [5] Display all Videos" << endl;
    cout << "  [6] Check Video Availability" << endl;
    cout << "  [7] Customer Maintenance" << endl;
    cout << "  [8] Sava and Exit(Save Changes)" << endl;
    cout << "  [9] Exit(Discard Changes)" << endl;
    cout << "\n  Enter choice: ";
}


/////////////////
///MAIN METHOD///
/////////////////
int main() {

    MovieList movie;
    CustomerQueue q;
    char ch;
    int c, z, cc, movid, custid;

    Jump:
    system("CLS");
    cout << endl;
    vidMenu();
    cin >> c;
    cout << endl;

    switch (c) {
    case 1:
        movie.addMovie();
        system("pause");
        goto Jump;
        break;
    case 2:
        movie.rentMovie();
        system("pause");
        goto Jump;
        break;
    case 3:
        movie.returnMovie();
        system("pause");
        goto Jump;
        break;
    case 4:
    t:
        cout << "  Enter movie ID: ";
        cin >> movid;
        if (!cin)
        {
            cin.clear();
            cout << "\n  Invalid input!\n";
            cout << "  Input new value again\n\n";
            cin.ignore();
            goto t;
        }
        else {
            movie.getMovie(movid);
            system("pause");
    
            goto Jump;
        }
        break;
    case 5:
        movie.getAllMovies();
        system("pause");
        goto Jump;
        break;
    case 6:
        cout << "  Enter movie ID: ";
        cin >> movid;
        movie.checkVideoAvail(movid);
        system("pause");
        goto Jump;
        break;
    case 7:
        customerMenu();
        cout << "\n    Enter choice: ";
        cin >> cc;
        cout << endl;
        switch (cc) {
        case 1:
            system("CLS");
            q.addNewCustomer();
            break;
        case 2:
            system("CLS");
            cout << "Enter Customer ID: ";
            cin >> custid;
            bool found;
            q.getCustomer(custid, found);
            break;
        case 3:
            q.listAllVidRented();
            break;
        default:
            cout << "  Invalid Input!";
            break;
        }

        system("pause");
        goto Jump;
        break;
    case 8:
        //b:
        movie.saveMovieList();
        cout << BOLD(FGRN("\n   Changes Saved!\n"));
   
        cout << FRED("\n   Program Terminated!");
        exit(0);
        break;
    case 9:
        cout << FRED("\n   Program Terminated!");
        exit(0);
        break;
    default:
        cin.clear();
        cout << "Invalid Input!";
        cin.ignore();
        goto Jump;
        break;
    }

}

