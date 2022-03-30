#pragma once
#include "Nodey.h"

template <typename T>
class Treey
{
private:
	Nodey<T>* root = nullptr;

public:
    Treey();
	Treey(T root);
	~Treey();
	void insert(T val, Nodey<T>* curr = nullptr);
	T remove(T var);
	Nodey<T>* find(T key, Nodey<T>* curr);
	int numNodes(Nodey<T>* curr);
	void getAllAscending(Nodey<T>* curr, Nodey<T>* tempArr[]);
	void getAllDescending(Nodey<T>* curr, Nodey<T>* tempArr[]);
	void emptyTree();
	int height(Nodey<T>* curr, Nodey<T>* parent);
};

template<typename T>
inline Treey<T>::Treey()
{
}

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
inline void Treey<T>::insert(T val, Nodey<T>* curr)
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

    return 1 + numNodes(curr->left) + numNodes(curr->right);
}

template<typename T>
inline void Treey<T>::getAllAscending(Nodey<T>* curr, Nodey<T>* tempArr[])
{
    static int index = 0; 
	if(curr == null){
       return;
    }
    getAllAscending(curr->left, index);   
    tempArr[index++] = curr->getData();  
    getAllAscending(curr->right, index);
}

// to call:
// int numberNodes = OurTree->numNodes(root);
// Nodey<T> *GAA = new Nodey<T>*[numberNodes];
// OurTree->getAllAscending(root, GAA);

template<typename T>
inline void Treey<T>::getAllDescending(Nodey<T>* curr, Nodey<T>* tempArr[])
{
	static int index = 0; 
	if(curr == null){
       return;
    }
    getAllDescending(curr->right, index);   
    tempArr[index++] = curr->getData();  
    getAllDescending(curr->left, index);
}

template<typename T>
inline void Treey<T>::emptyTree()
{
	if (this->root)
		this->root->destroyWithChildren();
}

template<typename T>
inline int Treey<T>::height(Nodey<T>* curr, Nodey<T>* parent)
{
	int R, L;

	if (curr == nullptr) return 0;
	R = this->height(curr->right, curr) + 1;
	L = this->height(curr->left, curr) + 1;
	
	if (R - L > 1) {
		int CR = this->height(curr->right->right, curr);
		int CL = this->height(curr->right->left, curr);

		if (CL > CR)
			
	}
    if (R > L) return R;
    return L;
}

/*
int Height(node* curr, node* parent) {
        int R, L;
        if (curr == NULL) return 0;
        R = Height(curr->right, curr) + 1;
        L = Height(curr->left, curr) + 1;
                                                        //if (R > L) return R;
                                                        //return L;
        if (R - L > 1) {
            int CR = Height(curr->right->right, curr);
            int CL = Height(curr->right->left, curr);
            if (CL > CR) {
                RotateRL(parent, curr, curr->right->left);
            } else {
                RotateLeft(parent, curr, curr->right);
            }
        }
    }

    void RotateRL(node* gp, node* parent, node* pivot){
        node* temp = parent->right
        parent->right = pivot->left
        temp->left = pivot->right
        pivot->left = parent;
        pivot->right = temp;
        if (gp == NULL) head = pivot;
        else if (gp->data < parent->data) gp->right = pivot;
        else gp->left = pivot;
    }

    void RotateLR(node* gp, node* parent, node* pivot){
        node* temp = parent->left
        parent->left = pivot->right
        temp->right = pivot->left
        pivot->right = parent;
        pivot->left = temp;
        if (gp == NULL) head = pivot;
        else if (gp->data < parent->data) gp->right = pivot;
        else gp->left = pivot;
    }

    void RotateLeft(node parent, node nR, node nL) {
        if (parent == root) {
            node temp = head->right;
            temp->left = root;
            root->right = NULL;
            root = temp;
        } else {
            parent->right = nR;
            nL->right = nR->left;
            nR->left = nL;
        }
    }

	void RotateRight(node *grandparent, node* pivot) {
        if (grandparent->data > pivot->data) {
            node *temp = grandparent->left;
            grandparent->left = pivot;
            temp->left = pivot->right;
        } else {
            node *temp = grandparent->right;
            grandparent->right = pivot;
            temp->left = pivot ->right;
            pivot->right = tmep;
        }
    }



*/