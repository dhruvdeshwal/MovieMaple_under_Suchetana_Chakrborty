#include "support.hpp"
#include <iostream>
#include <algorithm>
using namespace std;
// Trim whitespace from a string
string trim(const string &str)
{
    string s = str;
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !isspace(ch); }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !isspace(ch); })
                .base(),
            s.end());
    return s;
}

// Convert string to lowercase
string toLowercase(const string &str)
{
    string s = str;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// Filter movies by genre, rating, runtime, and adult flag
vector<Movie> filterByGenreRatingRuntimeAndAdult(const vector<Movie> &movies, const string &genre,double minRating, double minRuntime, double maxRuntime, bool adult)
{
    vector<Movie> filtered;
    string lowerGenre = toLowercase(trim(genre));
    for (const auto &m : movies)
    {
        string lowerMovieGenre = toLowercase(trim(m.genre));
        if (lowerMovieGenre.find(lowerGenre) != string::npos &&
            m.rating >= minRating &&
            m.runtime >= minRuntime &&
            m.runtime <= maxRuntime &&
            m.adult == adult)
        {
            filtered.push_back(m);
        }
    }
    return filtered;
}

// Filter movies by genre and rating
vector<Movie> filterByGenreAndRating(const vector<Movie> &movies, const string &genre, double minRating)
{
    vector<Movie> filtered;
    string lowerGenre = toLowercase(trim(genre));
    for (const auto &m : movies)
    {
        string lowerMovieGenre = toLowercase(trim(m.genre));
        if (lowerMovieGenre.find(lowerGenre) != string::npos && m.rating >= minRating)
        {
            filtered.push_back(m);
        }
    }
    return filtered;
}

// Filter movies by rating
vector<Movie> filterByRating(const vector<Movie> &movies, double minRating)
{
    vector<Movie> filtered;
    for (const auto &m : movies)
    {
        if (m.rating >= minRating)
        {
            filtered.push_back(m);
        }
    }
    return filtered;
}

// Display movies
void displayMovies(const vector<Movie> &movies, int limit)
{
    for (int i = 0; i < min(limit, (int)movies.size()); i++)
    {
        cout << movies[i].title << " | " << movies[i].genre << " | "
                  << movies[i].rating << " | " << movies[i].runtime << " min | "
                  << (movies[i].adult ? "Adult" : "Non-Adult") << std::endl;
    }
    cout << "Press any key to continue.";
    cin.ignore();
    cin.get();
}
