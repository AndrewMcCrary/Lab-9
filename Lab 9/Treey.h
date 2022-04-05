#pragma once
#include "Nodey.h"

template <class T1, class T2>
class Treey
{
private:
	Nodey<T1, T2>* root = nullptr;

    Nodey<T1, T2>* minValueKey(Nodey<T1, T2>* root);

    int avlHeight(Nodey<T1, T2>* root);

public:
    /// <summary>
    /// Empty constructor.
    /// </summary>
    Treey();

	/// <summary>
	/// Constructor, creates a root node.
	/// </summary>
	/// <param name="rootKey">The root's key.</param>
	/// <param name="rootData">The root's data.</param>
	Treey(T1 rootKey, T2 rootData);
	~Treey();

	/// <summary>
	/// Inserts a new node, using key-data pair.
	/// </summary>
	/// <param name="key">The node's key.</param>
	/// <param name="data">The node's data.</param>
	void insert(T1 key, T2 data, Nodey<T1, T2>* root = nullptr);

	/// <summary>
	/// Removes a node with the specified key and returns it's data.
	/// </summary>
	/// <param name="key">The node's key.</param>
	/// <returns>The node's data.</returns>
	T2 remove(T1 key, Nodey<T1, T2>* root = nullptr, Nodey<T1, T2>* parent = nullptr);

	/// <summary>
	/// Finds a node and returns a pointer to it's data.
	/// </summary>
	/// <param name="key">The node's key.</param>
	/// <returns>A pointer to the node's data.</returns>
	T2* find(T1 key, Nodey<T1, T2>* root = nullptr);

	/// <summary>
	/// Returns the number of nodes.
	/// </summary>
	int numNodes(Nodey<T1, T2>* curr = nullptr);

	void getAllAscending(Nodey<T1, T2>* curr, Nodey<T1, T2>* tempArr[]);
	void getAllDescending(Nodey<T1, T2>* curr, Nodey<T1, T2>* tempArr[]);

	/// <summary>
	/// Deletes all nodes within the tree, starting at the root.
	/// </summary>
	void emptyTree();

	/// <summary>
	/// Returns the height of the tree.
	/// </summary>
	int height(Nodey<T1, T2>* root);
};


template<class T1, class T2>
inline Treey<T1, T2>::Treey()
{
}


template<class T1, class T2>
inline Treey<T1, T2>::Treey(T1 rootKey, T2 rootData)
{
    this->root = new Nodey<T1, T2>(rootKey, rootData);
}


template<class T1, class T2>
inline Treey<T1, T2>::~Treey()
{
	if (this->root)
		this->root->destroyWithChildren();
}


template<class T1, class T2>
inline void Treey<T1, T2>::insert(T1 key, T2 data, Nodey<T1, T2>* root)
{
	if (!this->root)
		return this->root = new Nodey<T1, T2>(key);

	if (root->getKey() == key)
		throw "Duplicate key error";

	if (key < root->getKey()) {
		if (root->left)
			return this->insert(key, data, root->left);
		else
            root->left = new Nodey<T1, T2>(key, data, nullptr, nullptr, root);
	}
	else {
		if (root->right)
			return this->insert(key, data, root->right);
		else 
            root->right = new Nodey<T1, T2>(key, nullptr, nullptr, root);
	}

    // TODO: Rebalance here
}


template<class T1, class T2>
inline T2 Treey<T1, T2>::remove(T1 key, Nodey<T1, T2>* root, Nodey<T1, T2>* parent)
{
    if (root == nullptr && this->root)
        return this->remove(key, this->root, nullptr);
    else
        throw "The tree is empty";

    if (key == root->getKey()) {
        T2 data = root->getData();

        // Assumes root is not this->root
        if (!root->left) { // Right child case or no child
            if (parent->left == root)
                parent->left = root->right;
            else
                parent->right = root->right;

            delete root;
        }
        else if (!root->right) { // Left child case or no child
            if (parent && parent->left == root)
                parent->left = root->left;
            else
                parent->right = root->left;

            delete root;
        }
        else { // Both child case
            // Find min child on the right and replace with 
            Nodey<T1, T2>* min = minValueKey(root->right);
            root->key = min->getKey();
            root->data = min->getData();
            delete min;
            min->parent->left = min->right
        }

        // TODO: Rebalance here

        return data;
    }

    if (key < root->getKey()) {
        if (!root->left)
            throw "The key does not exist";
        return remove(key, root->left, root);
    }
    else {
        if (!root->right)
            throw "The key does not exist";
        return remove(key, root->right, root);
    }
}


template<class T1, class T2>
inline Nodey<T1, T2>* Treey<T1, T2>::minValueKey(Nodey<T1, T2>* root)
{
    // Minimum key must not have a left child to be minimum
    while (root->left)
        root = root->left;

    return root;
}


template<class T1, class T2>
inline int Treey<T1, T2>::avlHeight(Nodey<T1, T2>* root)
{
    int h = 0;
    if (root) {
        int l = avlHeight(root->left), r = avlHeight(root->right);
        int h = max(l, r) + 1;
    }
    return h;
}



template<class T1, class T2>
inline T2* Treey<T1, T2>::find(T1 key, Nodey<T1, T2>* root)
{
    if (!root && this->root)
        return this->find(key, this->root);
    else
        throw "The tree is empty";

    if (root->getKey() == key)
        return root->getDataAddr();

    if (key < root->getKey()) {
        if (!root->left)
            throw "The key does not exist";
        return find(key, root->left);
    }
    else {
        if (!root->right)
            throw "The key does not exist";
        return find(key, root->right);
    }
}


template<class T1, class T2>
inline int Treey<T1, T2>::numNodes(Nodey<T1, T2>* root)
{
	if (!root)
		return 0;

    return 1 + numNodes(root->left) + numNodes(root->right);
}


template<class T1, class T2>
inline void Treey<T1, T2>::getAllAscending(Nodey<T1, T2>* curr, Nodey<T1, T2>* tempArr[])
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
// Nodey<T1, T2> *GAA = new Nodey<T1, T2>*[numberNodes];
// OurTree->getAllAscending(root, GAA);


template<class T1, class T2>
inline void Treey<T1, T2>::getAllDescending(Nodey<T1, T2>* curr, Nodey<T1, T2>* tempArr[])
{
	static int index = 0; 
	if(curr == null){
       return;
    }
    getAllDescending(curr->right, index);   
    tempArr[index++] = curr->getData();  
    getAllDescending(curr->left, index);
}


template<class T1, class T2>
inline void Treey<T1, T2>::emptyTree()
{
	if (this->root)
		this->root->destroyWithChildren();
}


template<class T1, class T2>
inline int Treey<T1, T2>::height(Nodey<T1, T2>* root)
{
    int r, l;

    if (root == nullptr)
        return 0;

    l = this->height(root->left);
    r = this->height(root->right);

    return l > r ? l + 1 : r + 1;
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