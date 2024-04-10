#include "Dictionary.h"
#include <stdexcept>
#include <iostream>

#define RED 1
#define BLACK -1

using namespace std;

Dictionary::Node::Node(keyType k, valType v) : key(k), val(v), parent(nullptr), left(nullptr), right(nullptr), color(1) {}

Dictionary::Dictionary() {
    nil = new Node("", 0);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("\0", -1);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;

    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
    clear();
    delete nil;
}

void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

int Dictionary::size() const {
    return num_pairs;
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::LeftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void Dictionary::RightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nil) {
        root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

void Dictionary::RB_InsertFixUp(Node* z) {
    while (z->parent->color == 1) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == 1) {
                z->parent->color = -1;
                y->color = -1;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = -1;
                z->parent->parent->color = 1;
                RightRotate(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y->color == 1) {
                z->parent->color = -1;
                y->color = -1;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = -1;
                z->parent->parent->color = 1;
                LeftRotate(z->parent->parent);
            }
        }
    }
    root->color = -1;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_Delete(Node* z) {
    Node* y = z;
    Node* x;
    int originalColor = y->color;

    if (z->left == nil) {
        x = z->right;
        RB_Transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        RB_Transplant(z, z->left);
    } else {
        y = findMin(z->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (originalColor == BLACK) {
        RB_DeleteFixUp(x);
    }
}

void Dictionary::RB_DeleteFixUp(Node* x) {
    while (x != root && x->color == -1) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == 1) {
                w->color = -1;
                x->parent->color = 1;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == -1 && w->right->color == -1) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->right->color == -1) {
                    w->left->color = -1;
                    w->color = 1;
                    RightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = -1;
                w->right->color = 1;
                LeftRotate(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == 1) {
                w->color = -1;
                x->parent->color = 1;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == -1 && w->left->color == -1) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->left->color == -1) {
                    w->right->color = -1;
                    w->color = 1;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = -1;
                w->left->color = -1;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = -1;
}

void Dictionary::setValue(keyType k, valType v) {
    Node *y = nil;
    Node *x = root;
    Node *z;

    while (x != nil) {
        y = x;
        if (k == x->key) {
            x->val = v;
            return;
        }
        x = (k < x->key) ? x->left : x->right;
    }

    z = new Node(k, v);
    z->parent = y;

    if (y == nil) {
        root = z;
    } else if (k < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = nil;
    z->right = nil;
    z->color = RED;

    RB_InsertFixUp(z);
    num_pairs++;
}

void Dictionary::remove(keyType k) {
    if (contains(k) == false) {
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    Node* N = search(root, k);
    if (N == current) {
        current = nil;
    }
    RB_Delete(N);
    num_pairs--;
}

bool Dictionary::contains(keyType k) const {
    return search(root, k) != nil;
}

valType& Dictionary::getValue(keyType k) const {
    if( ! contains(k) ){
        throw std::logic_error("Dictionary: getValue(): key " + k + " does not exist");
    }
    Node* node = search(root, k);
    return node->val;
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    while (R != nil && k != R->key) {
        if (k < R->key) {
            R = R->left;
        } else {
            R = R->right;
        }
    }
    return R;
}

std::string Dictionary::to_string() const {
    std::string s;
    inOrderString(s, root);
    return s;
}

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s.append(R->key).append(" : ").append(std::to_string(R->val)).append("\n");
        inOrderString(s, R->right);
    }
}

std::string Dictionary::pre_string() const {
    Dictionary D = *this;
    std::string s = "";
    preOrderString(s, root);
    return s;
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s.append(R->key);
        if (R->color == RED) {
            s.append(" (RED)");
        }
        s.append("\n");
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}


void Dictionary::begin() {
    current = root;
    while (current != nil && current->left != nil){
        current = current->left;
    }
}

void Dictionary::end() {
    if(num_pairs <= 0){
        return;
    }

    current = root;
    while (current != nil && current->right != nil){
        current = current->right;
    }
}

void Dictionary::next() {
    if( ! hasCurrent() ){
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    current = findNext(current);
}

void Dictionary::prev() {
    if( ! hasCurrent() ){
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    current = findPrev(current);
}

bool Dictionary::hasCurrent() const {
    return current == nil ? false : true;
}

keyType Dictionary::currentKey() const {
   if( ! hasCurrent() ){
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal() const {
    if( ! hasCurrent() ){
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    while (R->left != nil) R = R->left;
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    while (R->right != nil) R = R->right;
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) return findMin(N->right);
    Node* P = N->parent;
    while (P != nil && N == P->right) {
        N = P;
        P = P->parent;
    }
    return P;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) return findMax(N->left);
    Node* P = N->parent;
    while (P != nil && N == P->left) {
        N = P;
        P = P->parent;
    }
    return P;
}

bool Dictionary::equals(const Dictionary& D) const{
    return to_string() == D.to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.to_string();
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if( this != &D ){
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}