#pragma once
#include "Nodey.h"

template <typename T>
class Treey
{
private:
	Nodey<T>* root;
	void insertRecur(T val, Nodey<T>* curr);
	int numNodesRecur(Nodey<T>* curr);

public:
	Treey(T root);
	~Treey();
	void insert(T var);
	T remove(T var);
	Nodey<T>* find(T key, Nodey<T>* curr);
	int numNodes(Nodey<T>* curr);
	// getAllAscending
	// getAllDescending
	void emptyTree();
	int height(Nodey<T>* curr);
	void rotateLeft();
	void rotateRight();

};

template<typename T>
inline Treey<T>::Treey(T root)
{
	this->root = new Nodey<T>(root);
}

template<typename T>
inline Treey<T>::~Treey()
{
	if (this->root)
		this->root->destroyWithChildren();
}

template<typename T>
inline void Treey<T>::insert(T var)
{
	if (root == nullptr){
		Nodey* newRooty = new Node(var);
		root = newRooty;
	}
	if (find(var, root) != nullptr) {
		throw "Already exists"
	}
	Node* curr = root;
	while ((curr->left != nullptr && curr->data > var) ||
		(curr->right != nullptr && curr->data < var)) {
		if (curr->data < var) {
			curr = curr->right;
		}
		else {
			curr = curr->left;
		}
	}
	if (curr->data < val) {
		curr->right = new Node(val);
	}
	else {
		curr->left = new Node(val);
	}
	// rebalance
}

template<typename T>
inline void Treey<T>::insertRecur(T val, Nodey<T>* curr)
{
	if (!this->root)
		return this->root = new Nodey<T>(val);

	if (curr->getData() == val)
		throw "Bad shit stupid dumb";

	if (curr->getData() > val) {
		if (curr->left)
			return insertRecur(val, curr->left);
		curr->left = new Nodey<T>(val);
		// rebalance
	}
	else if (curr->getData < val) {
		if (curr->right)
			return insertRecur(val, curr->right);
		curr->right = new Nodey<T>(val);
		// rebalance
	}
}

template<typename T>
inline T Treey<T>::remove(T var)
{
	if (find(var, root) == nullptr) {
		throw "Can't find it"
	}
	Node* prev;
        Node* curr = root;
        while (curr != NULL && curr->data != key){
            prev = curr;
            if (key < curr->data){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }
        if (prev->left == curr){
            //prev->left = NULL;
            if (curr->left != NULL){
                prev->left->data = curr->data;
            }
            else{
                prev->left = curr->right;
            }
        }
        else{
            //prev->right = NULL;
            if (curr->left != NULL){
                prev->right = curr->left;
            }
            else{ 
                prev->right = curr->right;
            }
        }
        int retVal = curr->data;
        delete curr;
        return retVal;
}

template<typename T>
inline Nodey<T>* Treey<T>::find(T key, Nodey<T>* curr)
{
	if (curr == nullptr) {
        // throw error
        return nullptr;
    }
    if (curr->data == key){
        return curr;
    }
    if (key < curr->data){
        return find(key, curr->left);
    }
    return find(key, curr->right);
}

template<typename T>
inline int Treey<T>::numNodes(Nodey<T>* curr)
{
	if (!curr)
		return 0;

	if (curr->left && curr->right)
		return 1 + numNodesRecur(curr->left) + numNodesRecur(curr->right);
	else if (curr->left)
		return 1 + numNodesRecur(curr->left);
	else if (curr->right)
		return 1 + numNodesRecur(curr->right);
	else
		return 1;
}

template<typename T>
inline void Treey<T>::emptyTree()
{
	if (this->root)
		this->root->destroyWithChildren();
}

template<typename T>
inline int Treey<T>::height(Nodey<T>* curr)
{
	if (curr == nullptr)
		return 0;

	int r, l;
	r = height(curr->right) + 1;
	l = height(curr->left) + 1;
	if (r > l)
		return r;
	else
		return l;
}