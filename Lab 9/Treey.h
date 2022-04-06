#pragma once
#include "Nodey.h"

template <class T1, class T2>
class Treey
{
private:
	Nodey<T1, T2>* root = nullptr;

    Nodey<T1, T2>* minValueKey(Nodey<T1, T2>* root);

    int avlHeight(Nodey<T1, T2>* root);
    bool balanceTree(Nodey<T1, T2>* root, Nodey<T1, T2>* p);
    void updateBalanceFactors(Nodey<T1, T2>* root);

    /// <summary>
    /// Rotates to the left.
    /// </summary>
    /// <param name="pivot">The pivot node.</param>
    /// <param name="p">Parent of the pivot.</param>
    /// <param name="gp">Grandparent, nullable.</param>
    void rotateLeft(Nodey<T1, T2>* pivot, Nodey<T1, T2>* p, Nodey<T1, T2>* gp);

    /// <summary>
    /// Rotates to the right.
    /// </summary>
    /// <param name="pivot">The pivot node.</param>
    /// <param name="p">Parent of the pivot.</param>
    /// <param name="gp">Grandparent, nullable.</param>
    void rotateRight(Nodey<T1, T2>* pivot, Nodey<T1, T2>* p, Nodey<T1, T2>* gp);

    /// <summary>
    /// Rotates to the left then the right.
    /// </summary>
    /// <param name="pivot">The pivot node.</param>
    /// <param name="p">Parent of the pivot.</param>
    /// <param name="gp">Grandparent of the pivot, not null.</param>
    /// <param name="ggp">Great grandparent of the pivot, null.</param>
    void rotateLR(Nodey<T1, T2>* pivot, Nodey<T1, T2>* p, Nodey<T1, T2>* gp, Nodey<T1, T2>* ggp);

    /// <summary>
    /// Rotates to the right then the left.
    /// </summary>
    /// <param name="pivot">The pivot node.</param>
    /// <param name="p">Parent of the pivot.</param>
    /// <param name="gp">Grandparent of the pivot, not null.</param>
    /// <param name="ggp">Great grandparent of the pivot, null.</param>
    void rotateRL(Nodey<T1, T2>* pivot, Nodey<T1, T2>* p, Nodey<T1, T2>* gp, Nodey<T1, T2>* ggp);

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
	void insert(T1 key, T2 data);

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

	void getAllAscending(T2* arr, int& i = 0, Nodey<T1, T2>* curr = nullptr);
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

#pragma region Constructors

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

#pragma endregion

template<class T1, class T2>
inline void Treey<T1, T2>::insert(T1 key, T2 data)
{
    Nodey<T1, T2>* current = this->root;
    if (!current) {
        this->root = new Nodey<T1, T2>(key, data);
        return;
    }

    while (1) {
        if (current->getKey() == key)
            throw "Duplicate key error";
        
        if (key < current->getKey()) {
            if (current->left)
                current = current->left;
            else {
                current->left = new Nodey<T1, T2>(key, data, nullptr, nullptr);
                break;
            }
        }
        else {
            if (current->right)
                current = current->right;
            else {
                current->right = new Nodey<T1, T2>(key, data, nullptr, nullptr);
                break;
            }
        }
    }

    this->updateBalanceFactors(this->root);
    this->balanceTree(this->root, nullptr);
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
            min->parent->left = min->right;
        }

        this->updateBalanceFactors(this->root);
        this->balanceTree(this->root, nullptr);

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
inline T2* Treey<T1, T2>::find(T1 key, Nodey<T1, T2>* root)
{
    if (!root && this->root)
        return this->find(key, this->root);
    else
        return nullptr;

    if (root->getKey() == key)
        return root->getDataAddr();

    if (key < root->getKey()) {
        if (!root->left)
            return nullptr;
        return find(key, root->left);
    }
    else {
        if (!root->right)
            return nullptr;
        return find(key, root->right);
    }
}


template<class T1, class T2>
inline int Treey<T1, T2>::numNodes(Nodey<T1, T2>* root)
{
    if (!this->root)
        return 0;

    if (!root)
        return this->numNodes(this->root);

    int i = 0;
    if (root->left)
        i += numNodes(root->left);

    if (root->right)
        i += numNodes(root->right);

    return 1 + i;
}


template<class T1, class T2>
inline void Treey<T1, T2>::getAllAscending(T2* arr, int& i, Nodey<T1, T2>* curr)
{
    if (curr == nullptr)
        return this->getAllAscending(arr, i, this->root);
    else if (!this->root)
        throw "The tree is empty";

    if (curr->left)
        getAllAscending(arr, i, curr->left);

    arr[i++] = curr->getData();

    if (curr->right)
        getAllAscending(arr, i, curr->right);
}


// to call:
// int numberNodes = OurTree->numNodes(root);
// Nodey<T1, T2> *GAA = new Nodey<T1, T2>*[numberNodes];
// OurTree->getAllAscending(root, GAA);


template<class T1, class T2>
inline void Treey<T1, T2>::getAllDescending(Nodey<T1, T2>* curr, Nodey<T1, T2>* tempArr[])
{
	static int index = 0; 
	if(curr == NULL){
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

#pragma region Balancing

template<class T1, class T2>
inline int Treey<T1, T2>::avlHeight(Nodey<T1, T2>* root)
{
    int h = 0;
    if (root) {
        int l = avlHeight(root->left), r = avlHeight(root->right);
        h = std::max(l, r) + 1;
    }
    return h;
}

template<class T1, class T2>
inline bool Treey<T1, T2>::balanceTree(Nodey<T1, T2>* root, Nodey<T1, T2>* p) {
    if (!root)
        return false;

    if (abs(root->balanceFactor) >= 2) {
        // rebalance cases
        if (root->balanceFactor < 0 && root->right->balanceFactor < 0)
            this->rotateLeft(root->right, root, p);
        else if (root->balanceFactor > 0 && root->left->balanceFactor > 0)
            this->rotateRight(root->left, root, p);
        else if (root->balanceFactor < 0 && root->right->balanceFactor > 0)
            this->rotateRL(root->right->left, root->right, root, p);
        else if (root->balanceFactor > 0 && root->left->balanceFactor < 0)
            this->rotateLR(root->left->right, root->left, root, p);

        return true;
    }
    else {
        return balanceTree(root->left, root) || balanceTree(root->right, root);
    }
}

template<class T1, class T2>
inline void Treey<T1, T2>::updateBalanceFactors(Nodey<T1, T2>* root) {
    if (!root)
        return;
    root->balanceFactor = this->avlHeight(root->left) - this->avlHeight(root->right);
    this->updateBalanceFactors(root->left);
    this->updateBalanceFactors(root->right);
}

#pragma endregion

#pragma region Rotations

template<class T1, class T2>
inline void Treey<T1, T2>::rotateLeft(Nodey<T1, T2>* pivot, Nodey<T1, T2>* p, Nodey<T1, T2>* gp) { // Child (pivot) rotates up and left
    // Grandparent points to pivot
    if (gp && gp->getKey() > pivot->getKey())
        gp->left = pivot;
    else if (gp && gp->getKey() < pivot->getKey())
        gp->right = pivot;
    else
        this->root = pivot;

    p->right = pivot->left;
    pivot->left = p;
}

template<class T1, class T2>
inline void Treey<T1, T2>::rotateRight(Nodey<T1, T2>* pivot, Nodey<T1, T2>* p, Nodey<T1, T2>* gp) { // Left child of the root become new root from subtree perspective 
        // Grandparent points to pivot
    if (gp && gp->getKey() > pivot->getKey())
        gp->left = pivot;
    else if (gp && gp->getKey() < pivot->getKey())
        gp->right = pivot;
    else
        this->root = pivot;

    p->left = pivot->right;
    pivot->right = p;
}

template<class T1, class T2>
inline void Treey<T1, T2>::rotateLR(Nodey<T1, T2>* pivot, Nodey<T1, T2>* p, Nodey<T1, T2>* gp, Nodey<T1, T2>* ggp) {
    this->rotateLeft(pivot, p, gp);
    this->rotateRight(pivot, gp, ggp);
}

template<class T1, class T2>
inline void Treey<T1, T2>::rotateRL(Nodey<T1, T2>* pivot, Nodey<T1, T2>* p, Nodey<T1, T2>* gp, Nodey<T1, T2>* ggp) {
    this->rotateRight(pivot, p, gp);
    this->rotateLeft(pivot, gp, ggp);
}

#pragma endregion