#include <bits/stdc++.h>
#include <windows.h>
#include <cstdlib>
#include "Treap.hpp"
#include "support.hpp"
#include "loadMovies.hpp"

using namespace std;

// Levenshtein Distance Function
int levenshteinDistance(const std::string &a, const std::string &b) {
    int n = a.size(), m = b.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[n][m];
}

// Function to get the closest matching genre
std::string getClosestGenre(const std::string &input) {
    std::vector<std::string> genres = {"action", "crime", "documentary", "comedy", "drama", "horror", "thriller", 
                                       "romance", "science-fiction", "fantasy", "animation", "adventure", "family"};

    std::string userGenre = input;
    std::transform(userGenre.begin(), userGenre.end(), userGenre.begin(), ::tolower);

    // If user input exactly matches a genre, return it immediately
    for (const std::string &genre : genres) {
        if (userGenre == genre) {
            return genre;
        }
    }

    // Find the closest matching genre using Levenshtein distance
    int minDistance = 100; 
    std::string bestMatch = "";
    for (const std::string &genre : genres) {
        int dist = levenshteinDistance(userGenre, genre);
        if (dist < minDistance) {
            minDistance = dist;
            bestMatch = genre;
        }
    }
    return bestMatch;
}

void menu() {
    cout << "\nHello Sir, which type of movie would you like to watch today?" << endl;
    cout << "1. Top Rated Movies" << endl;
    cout << "2. Movies of a Specific Genre" << endl;
    cout << "3. Movies Above a Certain Rating" << endl;
    cout << "4. Movies of a Specific Genre and Rating" << endl;
    cout << "5. Movies of a Specific Genre, Rating, Runtime, and Adult Filter" << endl;
    cout << "6. Exit" << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<Movie> movies = loadMoviesFromFile("cleaned_movies.csv");
    if (movies.empty()) {
        cerr << "No movies loaded. Please check the file and try again." << endl;
        return 1;
    }
    
    Treap treap;
    for (const auto &m : movies) {
        treap.insert(m);
    }

    int choice;
    while (true) {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) { 
            int numMovies;
            cout << "How many top-rated movies would you like to see? ";
            cin >> numMovies;
            if(cin.fail()|| numMovies<=0) {
                cout<<"Enter valid movies to watch !!"<<endl;
                continue;
            }

            vector<Movie> topMovies = treap.getTopMovies(numMovies);
            cout << "\nTop Rated Movies:\n";
            displayMovies(topMovies, numMovies);
        } 
        else if (choice == 2) {
            string genre, c_genre;
            cout << "Available genres: action, comedy, drama, thriller, family, fantasy, etc.\n";
            cout << "Enter Genre: ";
            cin.ignore();
            getline(cin, genre);
            c_genre = getClosestGenre(genre);

            if (c_genre != genre) {
                cout << "Did you mean '" << c_genre << "'? (Y/N): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'N' || confirm == 'n') continue;
            }

            vector<Movie> filtered = filterByGenreAndRating(movies, c_genre, 0.0);
            if (filtered.empty()) {
                cout << "No movies found for the given genre.\n";
                continue;
            }

            int numMovies;
            cout << "How many movies would you like to see? ";
            cin >> numMovies;
            if (numMovies > filtered.size()) {
                cout << "Only " << filtered.size() << " movies available.\n";
                numMovies = filtered.size();
            }
            displayMovies(filtered, numMovies);
        } 
        else if (choice == 3) {
            double minRating;
            cout << "Enter Minimum Rating (0 to 10): ";
            cin >> minRating;
            if (cin.fail() || minRating < 0 || minRating > 10) {
                cout << "Enter a valid rating (between 0 to 10).\n";
                continue;
            }

            vector<Movie> filtered = filterByRating(movies, minRating);
            if (filtered.empty()) {
                cout << "No movies found above this rating.\n";
                continue;
            }

            int numMovies;
            cout << "How many movies would you like to see? ";
            cin >> numMovies;
            if(cin.fail()|| numMovies<=0) {
                cout<<"Enter valid movies to watch !!"<<endl;
                return 0;
            }
            if (numMovies > filtered.size()) {
                cout << "Only " << filtered.size() << " movies available.\n";
                numMovies = filtered.size();
            }
            displayMovies(filtered, numMovies);
        } 
        else if (choice == 4) {
            string genre, c_genre;
            double minRating;
            cout << "Enter Genre: ";
            cin.ignore();
            getline(cin, genre);
            c_genre = getClosestGenre(genre);

            if (c_genre != genre) {
                cout << "Did you mean '" << c_genre << "'? (Y/N): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'N' || confirm == 'n') continue;
            }

            cout << "Enter Minimum Rating (0 to 10): ";
            cin >> minRating;
            if (cin.fail() || minRating < 0 || minRating > 10) {
                cout << "Enter a valid rating (between 0 to 10).\n";
                continue;
            }

            vector<Movie> filtered = filterByGenreAndRating(movies, c_genre, minRating);
            if (filtered.empty()) {
                cout << "No movies found matching the criteria.\n";
                continue;
            }

            int numMovies;
            cout << "How many movies would you like to see? ";
            cin >> numMovies;
            if(cin.fail()|| numMovies<=0) {
                cout<<"Enter valid movies to watch !!"<<endl;
                return 0;
            }
            if (numMovies > filtered.size()) {
                cout << "Only " << filtered.size() << " movies available.\n";
                numMovies = filtered.size();
            }
            displayMovies(filtered, numMovies);
        } 
        else if (choice == 5) {
            string genre , c_genre;
            double minRating, minRuntime, maxRuntime;
            bool adult;
            cout << "Available genres are : action , comedy , drama , thriller , family , fantasy etc "<<endl;
            cout << "Enter Genre: ";
            cin.ignore();
            getline(cin, genre);
            c_genre = getClosestGenre(genre);
            if (c_genre != genre) {
                cout << "Did you mean '" << c_genre << "'? (Y/N): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'N' || confirm == 'n') continue;
            }
            cout << "Enter Minimum Rating: ";
            cin >> minRating;
             if(cin.fail() || minRating<0 || minRating>10){
                cout<<"Enter valid rating (between 0 to 10)"<<endl;
                return 0;
            }
            cout << "Enter Minimum Runtime (in minutes): ";
            cin >> minRuntime;
             if(cin.fail() || minRuntime<0 || minRuntime>210){
                cout<<"Enter valid runtime (between 0 to 210)"<<endl;
                return 0;
            }
            cout << "Enter Maximum Runtime (in minutes): ";
            cin >> maxRuntime;
            if(cin.fail() || maxRuntime<0 || maxRuntime>210){
                cout<<"Enter valid runtime (between 0 to 210)"<<endl;
                return 0;
            }
            cout << "Include Adult Movies? (1 for Yes, 0 for No): ";
            cin >> adult;

            vector<Movie> filtered = filterByGenreRatingRuntimeAndAdult(movies, genre, minRating, minRuntime, maxRuntime, adult);
            if (filtered.empty()) {
                cout << "No movies found matching the criteria.\n";
                continue;
            }
            int numMovies;
            cout << "How many movies would you like to see? ";
            cin >> numMovies;
            if(cin.fail()|| numMovies<=0) {
                cout<<"Enter valid movies to watch !!"<<endl;
                return 0;
            }
            if (numMovies > filtered.size()) {
                cout << "Only " << filtered.size() << " movies available.\n";
                numMovies = filtered.size();
            }
            displayMovies(filtered, numMovies);
        } 
        else if (choice == 6) {
            cout << "Thank you for using the movie recommender!\n";
            break;
        } 
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
