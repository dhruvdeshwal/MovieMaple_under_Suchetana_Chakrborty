#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include "loadMovies.hpp"
#include <vector>
#include <string>
using namespace std;
string trim(const string &str);
string toLowercase(const string &str);
vector<Movie> filterByGenreRatingRuntimeAndAdult(const vector<Movie> &movies, const string &genre,double minRating, double minRuntime, double maxRuntime, bool adult);
vector<Movie> filterByGenreAndRating(const vector<Movie> &movies, const string &genre, double minRating);
vector<Movie> filterByRating(const vector<Movie> &movies, double minRating);
void displayMovies(const vector<Movie> &movies, int limit);

#endif
