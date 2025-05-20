#ifndef TREAP_HPP
#define TREAP_HPP
#include "loadMovies.hpp"
#include <vector>
struct TreapNode
{
    Movie movie;
    int priority;
    TreapNode *left, *right;
    TreapNode(Movie m);
};
class Treap
{
private:
    TreapNode *root;
    TreapNode *rightRotate(TreapNode *y);
    TreapNode *leftRotate(TreapNode *x);
    TreapNode *insert(TreapNode *node, Movie m);
    void inorder(TreapNode *node, std::vector<Movie> &result, int &count, int limit);

public:
    Treap();
    void insert(Movie m);
    std::vector<Movie> getTopMovies(int limit);
};

#endif
