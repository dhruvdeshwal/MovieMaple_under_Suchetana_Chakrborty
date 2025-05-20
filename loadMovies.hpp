#ifndef LOAD_MOVIES_HPP
#define LOAD_MOVIES_HPP

#include<bits/stdc++.h>
// #include"Movie.hpp"
using namespace std; 
struct Movie {
    string title;
    string genre;
    double rating;
    bool adult;
    double runtime;
    Movie(string t, string g, double r, bool a, double rt)
        : title(t), genre(g), rating(r), adult(a), runtime(rt) {}
};
vector<Movie> loadMoviesFromFile(const string& filename);

#endif