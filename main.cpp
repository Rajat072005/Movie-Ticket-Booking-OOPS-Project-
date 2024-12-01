#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Movie {
private:
    string name;
    string genre;
    string showtime;
    int availableSeats;

public:
    Movie(string name = "", string genre = "", string showtime = "", int availableSeats = 0)
        : name(name), genre(genre), showtime(showtime), availableSeats(availableSeats) {}

    void displayMovieDetails() const {
        cout << "Movie: " << name << "\nGenre: " << genre << "\nShowtime: " << showtime
             << "\nAvailable Seats: " << availableSeats << endl;
    }

    string getName() const { return name; }
    int getAvailableSeats() const { return availableSeats; }

    void updateSeats(int seatsBooked) {
        availableSeats -= seatsBooked;
    }

    void saveToFile(ofstream &out) const {
        out << name << endl;
        out << genre << endl;
        out << showtime << endl;
        out << availableSeats << endl;
    }

    void loadFromFile(ifstream &in) {
        getline(in, name);
        getline(in, genre);
        getline(in, showtime);
        in >> availableSeats;
        in.ignore();
    }
};

class Ticket {
private:
    int ticketID;
    string movieName;
    int numberOfTickets;
    float totalPrice;

public:
    Ticket(int ticketID = 0, string movieName = "", int numberOfTickets = 0, float totalPrice = 0.0)
        : ticketID(ticketID), movieName(movieName), numberOfTickets(numberOfTickets), totalPrice(totalPrice) {}

    void generateTicket(float pricePerTicket) {
        totalPrice = numberOfTickets * pricePerTicket;
    }

    void displayTicketDetails() const {
        cout << "\nTicket ID: " << ticketID << "\nMovie: " << movieName
             << "\nNumber of Tickets: " << numberOfTickets
             << "\nTotal Price: $" << totalPrice << endl;
    }

    string getMovieName() const { return movieName; }

    int getNumberOfTickets() const { return numberOfTickets; }
};

class Cinema {
private:
    vector<Movie> movies;

public:
    void addMovie() {
        string name, genre, showtime;
        int availableSeats;

        cout << "Enter Movie Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Movie Genre: ";
        getline(cin, genre);
        cout << "Enter Showtime: ";
        getline(cin, showtime);
        cout << "Enter Available Seats: ";
        cin >> availableSeats;

        Movie newMovie(name, genre, showtime, availableSeats);
        movies.push_back(newMovie);
        cout << "Movie added successfully!\n";
    }

    void displayMovies() {
        cout << "\nAvailable Movies:\n";
        for (const auto &movie : movies) {
            movie.displayMovieDetails();
            cout << "--------------------------\n";
        }
    }

    void bookTicket() {
        string movieName;
        int seats;
        cout << "Enter the movie name you want to book tickets for: ";
        cin.ignore();
        getline(cin, movieName);

        for (auto &movie : movies) {
            if (movie.getName() == movieName) {
                cout << "Enter number of seats to book: ";
                cin >> seats;

                if (seats <= movie.getAvailableSeats()) {
                    movie.updateSeats(seats);
                    float pricePerTicket = 10.0;
                    Ticket newTicket(rand() % 1000 + 1, movieName, seats, pricePerTicket);
                    newTicket.generateTicket(pricePerTicket);
                    newTicket.displayTicketDetails();
                    cout << "Booking successful!\n";
                    return;
                } else {
                    cout << "Not enough available seats.\n";
                    return;
                }
            }
        }
        cout << "Movie not found!\n";
    }

    void saveMoviesToFile(const string &filename) {
        ofstream out(filename, ios::out);
        for (const auto &movie : movies) {
            movie.saveToFile(out);
        }
        out.close();
    }

    void loadMoviesFromFile(const string &filename) {
        ifstream in(filename, ios::in);
        Movie movie;
        while (in) {
            movie.loadFromFile(in);
            if (in) movies.push_back(movie);
        }
        in.close();
    }
};

int main() {
    Cinema cinema;
    string filename = "movies.txt";

    cinema.loadMoviesFromFile(filename);

    int choice;
    do {
        cout << "\n1. Add Movie\n";
        cout << "2. Display Movies\n";
        cout << "3. Book Ticket\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits <streamsize> ::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 4.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cinema.addMovie();
                break;
            case 2:
                cinema.displayMovies();
                break;
            case 3:
                cinema.bookTicket();
                break;
            case 4:
                cinema.saveMoviesToFile(filename);
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice, try again!\n";
        }
    } while (choice != 4);

    return 0;
}
