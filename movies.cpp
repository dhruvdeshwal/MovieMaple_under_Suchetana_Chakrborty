#include<bits/stdc++.h>
using namespace std;
#include"loadMovies.hpp"
vector<Movie> loadMoviesFromFile(const string &filename) {
    vector<Movie> movies;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return movies;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string title, genres, ratingStr, adultStr, runtimeStr;
        double rating = 0.0, runtime = 0.0;
        bool adult = false;

        try {
            if (line[0] == '"') {
                size_t endQuote = line.find("\",");
                title = line.substr(1, endQuote - 1);
                line = line.substr(endQuote + 2);
            } else {
                size_t firstComma = line.find(',');
                title = line.substr(0, firstComma);
                line = line.substr(firstComma + 1);
            }
            if (line[0] == '"') {
                size_t endQuote = line.find("\",");
                genres = line.substr(1, endQuote - 1);
                line = line.substr(endQuote + 2);
            } else {
                size_t firstComma = line.find(',');
                genres = line.substr(0, firstComma);
                line = line.substr(firstComma + 1);
            }
            stringstream rest(line);
            getline(rest, ratingStr, ',');
            getline(rest, adultStr, ',');
            getline(rest, runtimeStr, ',');
            rating = stod(ratingStr);
            runtime = stod(runtimeStr);
            adult = (adultStr == "True" || adultStr == "true");
            movies.push_back(Movie(title, genres, rating, adult, runtime));
        
        } catch (...) {
            continue;
        }
    }
    file.close();
    return movies;
}
