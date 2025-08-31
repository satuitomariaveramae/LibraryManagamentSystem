#include <iostream>
#include <vector>
#include <string>
using namespace std;

//book class to store book details
class Book 
{
public:
    string title, author, ISBN;
    bool isAvailable;

	//constructor to initialize book details
    Book(string t, string a, string i) 
	{
        title = t;
        author = a;
        ISBN = i;
        isAvailable = true; //by default, the book is available
    } 
};

//user class to store user details
class User 
{
public:
    int id;
    string name;
    vector<string> borrowedBooks;

	//constructor to initialize user details
    User(int uid, string uname) 
	{
        id = uid;
        name = uname;
    }
};

//global vectors to store books and users
vector<Book> books;
vector<User> users;

//function to add a new book to the library
void addBook() 
{
    string t, a, i;
    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, t); //getting title input
    cout << "Enter Author: ";
    getline(cin, a); //getting author input
    cout << "Enter ISBN: ";
    getline(cin, i); //getting ISBN input

    books.push_back(Book(t, a, i)); //adding new book to the list
    cout << "Book added successfully!\n";
}

//function to display all available books
void displayBooks() 
{
    if (books.empty()) 
	{
        cout << "No books available.\n"; //if no books, show message
        return;
    }
    cout << "\n-------------- Book List --------------\n";
    for (size_t i = 0; i < books.size(); i++) 
	{
        cout << i+1 << ". " << books[i].title << " by " << books[i].author
             << " [ISBN: " << books[i].ISBN << "] "
             << (books[i].isAvailable ? "(Available)" : "(Borrowed)") << "\n";
    }
}

//function to register a new user in the system
void registerUser() 
{
    int id;
    string name;
    cout << "Enter User ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter User Name: ";
    getline(cin, name);

    users.push_back(User(id, name)); //adding user to the list
    cout << "User registered successfully!\n";
}

//function to display all registered users
void displayUsers() 
{
    if (users.empty()) 
	{
        cout << "No users registered.\n"; //if no users, show message
        return;
    }
    cout << "\n-------------- User List --------------\n";
    for (size_t i = 0; i < users.size(); i++) 
	{
        cout << "ID: " << users[i].id << " | Name: " << users[i].name << "\n";
    }
}

//function to borrow a book
void borrowBook() 
{
    if (books.empty() || users.empty()) 
	{
        cout << "Either no books or no users available.\n"; //if no books or users, show message
        return;
    }

    int uid, choice;
    cout << "Enter User ID: ";
    cin >> uid;

    //find user by ID
    int userIndex = -1;
    for (size_t i = 0; i < users.size(); i++) 
	{
        if (users[i].id == uid) 
		{
            userIndex = i;
            break;
        }
    }
    if (userIndex == -1) 
	{
        cout << "User not found!\n"; //if user not found, show message
        return;
    }

    displayBooks();
    cout << "Enter book number to borrow: ";
    cin >> choice;

	//check if book is valid
    if (choice < 1 || choice > (int)books.size()) 
	{
        cout << "Invalid book selection!\n"; //if invalid selection, show message
        return;
    }

    if (!books[choice-1].isAvailable) 
	{
        cout << "Book already borrowed!\n"; //if book is borrowed, show message
        return;
    }

	//borrow the book
    books[choice-1].isAvailable = false;
    users[userIndex].borrowedBooks.push_back(books[choice-1].title);
    cout << "Book borrowed successfully!\n";
}

//function to return a borrowed book
void returnBook() 
{
    int uid;
    cout << "Enter User ID: ";
    cin >> uid;

	//find user by ID
    int userIndex = -1;
    for (size_t i = 0; i < users.size(); i++) 
	{
        if (users[i].id == uid) 
		{
            userIndex = i;
            break;
        }
    }
    if (userIndex == -1) 
	{
        cout << "User not found!\n"; //if user not found, show message
        return;
    }

	//check if the user has borrowed any books
    if (users[userIndex].borrowedBooks.empty()) 
	{
        cout << "User has no borrowed books.\n"; //if no borrowed books, show message
        return;
    }

	//display borrowed books
    cout << "\n---------------- Borrowed Books ----------------\n";
    for (size_t i = 0; i < users[userIndex].borrowedBooks.size(); i++) 
	{
        cout << i+1 << ". " << users[userIndex].borrowedBooks[i] << "\n";
    }

    int choice;
    cout << "Enter book number to return: ";
    cin >> choice;

	//check if selection is valid	
    if (choice < 1 || choice > (int)users[userIndex].borrowedBooks.size()) 
	{
        cout << "Invalid selection!\n"; //if invalid selection, show message
        return;
    }

    string bookTitle = users[userIndex].borrowedBooks[choice-1];

    //find and mark the book as available
    for (size_t i = 0; i < books.size(); i++) 
	{
        if (books[i].title == bookTitle) 
		{
            books[i].isAvailable = true;
            break;
        }
    }

    users[userIndex].borrowedBooks.erase(users[userIndex].borrowedBooks.begin() + (choice-1));
    cout << "Book returned successfully!\n";
}

//function to display borrowed books for a specific user
void displayBorrowedBooksForUser() 
{
    int uid;
    cout << "Enter User ID: ";
    cin >> uid;

    int userIndex = -1;
    for (size_t i = 0; i < users.size(); i++) 
	{
        if (users[i].id == uid) 
		{
            userIndex = i;
            break;
        }
    }
    if (userIndex == -1)
	{
        cout << "User not found!\n"; //if user not found, show message
        return;
    }

    cout << "\n-------------- Borrowed Books for " << users[userIndex].name << " --------------\n";
    if (users[userIndex].borrowedBooks.empty()) 
	{
        cout << "No borrowed books.\n"; //if no borrowed books, show message
    } else 
	{
        for (size_t i = 0; i < users[userIndex].borrowedBooks.size(); i++) 
		{
            cout << i+1 << ". " << users[userIndex].borrowedBooks[i] << "\n"; //display borrowed books
        }
    }
}

//function to remove a book from the library
void removeBook() 
{
    if (books.empty()) 
	{
        cout << "No books available to remove.\n"; //if no books, show message
        return;
    }

    displayBooks();
    int choice;
    cout << "Enter book number to remove: ";
    cin >> choice;

	//check if selection is valid
    if (choice < 1 || choice > (int)books.size()) 
	{
        cout << "Invalid selection!\n"; //if invalid selection, show message
        return;
    }

    books.erase(books.begin() + (choice - 1)); //remove book from the list
    cout << "Book removed successfully!\n";
}

//function to remove a user from the system
void removeUser() 
{
    if (users.empty()) 
	{
        cout << "No users available to remove.\n"; //if no users, show message
        return;
    }

    displayUsers();
    int uid;
    cout << "Enter User ID to remove: ";
    cin >> uid;

    int userIndex = -1;
    for (size_t i = 0; i < users.size(); i++) 
	{
        if (users[i].id == uid) 
		{
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) 
	{
        cout << "User not found!\n"; //if user not found, show message
        return;
    }

    users.erase(users.begin() + userIndex);
    cout << "User removed successfully!\n";
}

int main()
{
    int choice;

    do {
        cout << "\n================ Main Menu ================\n";
        cout << "1. Book\n"; //book menu option
        cout << "2. Library User\n"; //user menu option
        cout << "3. Librarian Access\n"; //librarian menu option
        cout << "4. Exit\n"; //exit program
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: { //book menu
            int bChoice;
            do {
                cout << "\n---------------- Book Menu ----------------\n";
                cout << "1. Display Books\n"; //shows book
                cout << "2. Exit\n"; //go back to main menu
                cout << "Enter choice: ";
                cin >> bChoice;

                switch (bChoice) {
                case 1:
                    displayBooks();
                    break;
                case 2:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << "Invalid choice! Try again.\n";
                }
            } while (bChoice != 2);
            break;
        }

        case 2: { //user menu
            int uChoice;
            do {
                cout << "\n------------ Library User Menu ------------\n";
                cout << "1. Display Users\n"; //show users
                cout << "2. Exit\n"; //go back to main menu
                cout << "Enter choice: ";
                cin >> uChoice;

                switch (uChoice) {
                case 1:
                    displayUsers();
                    break;
                case 2:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << "Invalid choice! Try again.\n";
                }
            } while (uChoice != 2);
            break;
        }

        case 3: { //librarian menu
            int lChoice;
            do {
                cout << "\n---------- Librarian Access Menu ----------\n";
                cout << "1. Add Book\n"; //add book
                cout << "2. Remove Book\n"; //remove book
                cout << "3. Register User\n"; //register a book
                cout << "4. Remove User\n"; //remove a book
                cout << "5. Borrow Book\n"; //borrow a book
                cout << "6. Return Book\n"; //return a book
                cout << "7. Display All Books\n"; //show all books
                cout << "8. Display All Users\n"; //show all users
                cout << "9. Display Borrowed Books for a User\n"; //display borrowed books for a user
                cout << "10. Exit\n"; //go back to main menu
                cout << "Enter choice: ";
                cin >> lChoice;
                
                switch (lChoice) {
                case 1: addBook(); break; //add book
                case 2: removeBook(); break; //remove book
                case 3: registerUser(); break; //register book
                case 4: removeUser(); break; //remove book
                case 5: borrowBook(); break; //borrow book
                case 6: returnBook(); break; //return book
                case 7: displayBooks(); break; //display books
                case 8: displayUsers(); break; //display users
                case 9: displayBorrowedBooksForUser(); break; //display borrowed books for user
                case 10: cout << "Returning to Main Menu...\n"; break;
                default: cout << "Invalid choice! Try again.\n";
                }
            } while (lChoice != 10);
            break;
        }

        case 4:
            cout << "Exiting program... Goodbye!\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
