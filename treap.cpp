#include "Treap.hpp"
#include <cstdlib>
// Constructor for TreapNode
TreapNode::TreapNode(Movie m) : movie(m), priority(rand()), left(nullptr), right(nullptr) {}
// Treap constructor
Treap::Treap() : root(nullptr) {}
// Right rotation
TreapNode* Treap::rightRotate(TreapNode *y) {
    TreapNode *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}
// Left rotation
TreapNode* Treap::leftRotate(TreapNode *x) {
    TreapNode *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
// Insert function
TreapNode* Treap::insert(TreapNode *node, Movie m) {
    if (!node)
        return new TreapNode(m);
    if (m.rating >= node->movie.rating) {
        node->right = insert(node->right, m);
        if (node->right && node->right->priority > node->priority)
            node = leftRotate(node);
    } else {
        node->left = insert(node->left, m);
        if (node->left && node->left->priority > node->priority)
            node = rightRotate(node);
    }
    return node;
}
// Public insert method
void Treap::insert(Movie m) {
    root = insert(root, m);
}
// In-order traversal to get top movies
void Treap::inorder(TreapNode *node, std::vector<Movie> &result, int &count, int limit) {
    if (!node || count >= limit)
        return;
    inorder(node->right, result, count, limit);
    if (count < limit) {
        result.push_back(node->movie);
        count++;
    }
    inorder(node->left, result, count, limit);
}
// Get top movies
std::vector<Movie> Treap::getTopMovies(int limit) {
    std::vector<Movie> result;
    int count = 0;
    inorder(root, result, count, limit);
    return result;
}
