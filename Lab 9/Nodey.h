#pragma once

template <class T1, class T2>
class Nodey
{
private:
	T1 key;
	T2 data;
public:
	/// <summary>
	/// Creates a new node, key cannot be changed once created.
	/// </summary>
	/// <param name="key">The lookup key.</param>
	/// <param name="data">The data for the node.</param>
	/// <param name="right">The left child.</param>
	/// <param name="left">The right child.</param>
	Nodey<T1, T2>(T1 key, T2 data = (T2)NULL, Nodey<T1, T2>* right = nullptr, Nodey<T1, T2>* left = nullptr, Nodey<T1, T2>* parent = nullptr);

	/// <summary>
	/// The right child.
	/// </summary>
	Nodey<T1, T2>* right;

	/// <summary>
	/// The left child.
	/// </summary>
	Nodey<T1, T2>* left;

	/// <summary>
	/// Gets the nodes lookup key.
	/// </summary>
	/// <returns>The lookup key.</returns>
	T1 getKey() { return this->key; }

	/// <summary>
	/// Gets the nodes data.
	/// </summary>
	/// <returns>The data.</returns>
	T2 getData() { return this->data; }

	/// <summary>
	/// Gets a pointer to the nodes data.
	/// </summary>
	/// <returns>The data pointer.</returns>
	T2 getDataAddr() { return &(this->data); }

	/// <summary>
	/// Sets the nodes data.
	/// </summary>
	/// <param name="val">The new data.</param>
	void setData(T2 val) { this->data = val; }

	/// <summary>
	/// Destroys all subtrees
	/// </summary>
	void destroyWithChildren();

	//void rotateLeft(Nodey<T>* parent, Nodey<T>* nR, Nodey<T>* nL, Nodey<T>* root);
	//void rotateRight(Nodey<T>* grandparent, Nodey<T>* pivot);
	//void rotateLR(Nodey<T>* gp, Nodey<T>* parent, Nodey<T>* pivot);
	//void rotateRL(Nodey<T>* gp, Nodey<T>* parent, Nodey<T>* pivot);

	bool operator>(Nodey* temp);
	bool operator<(Nodey* temp);
	bool operator==(Nodey* temp);
};


template<class T1, class T2>
inline Nodey<T1, T2>::Nodey(T1 key, T2 data, Nodey<T1, T2>* right, Nodey<T1, T2>* left, Nodey<T1, T2>* parent)
{
	this->key = key;
	this->data = data;
	this->right = right;
	this->left = left;
	this->parent = parent;
}

template<class T1, class T2>
inline void Nodey<T1, T2>::destroyWithChildren()
{
	if (this->right)
		this->right->destroyWithChildren();

	if (this->left)
		this->left->destroyWithChildren();

	delete this;
}

//template<typename T>
//inline void Nodey<T>::rotateLeft(Nodey<T>* parent, Nodey<T>* nR, Nodey<T>* nL, Nodey<T>* root)
//{
//	if (parent == root) {
//		Nodey<T>* temp = head->right;
//		temp->left = root;
//		root->right = NULL;
//		root = temp;
//	}
//	else {
//		parent->right = nR;
//		nL->right = nR->left;
//		nR->left = nL;
//	}
//}

//template<typename T>
//inline void Nodey<T>::rotateRight(Nodey<T>* grandparent, Nodey<T>* pivot)
//{
//	if (grandparent->data > pivot->data) {
//		Nodey<T>* temp = grandparent->left;
//		grandparent->left = pivot;
//		temp->left = pivot->right;
//	}
//	else {
//		Nodey<T>* temp = grandparent->right;
//		grandparent->right = pivot;
//		temp->left = pivot->right;
//		pivot->right = temp;
//	}
//}
//
//template<typename T>
//inline void Nodey<T>::rotateLR(Nodey<T>* gp, Nodey<T>* parent, Nodey<T>* pivot)
//{
//	node* temp = parent->left
//	parent->left = pivot->right
//	temp->right = pivot->left
//	pivot->right = parent;
//	pivot->left = temp;
//	if (gp == NULL) head = pivot;
//	else if (gp->data < parent->data) gp->right = pivot;
//	else gp->left = pivot;
//}
//
//template<typename T>
//inline void Nodey<T>::rotateRL(Nodey<T>* gp, Nodey<T>* parent, Nodey<T>* pivot)
//{
//	node* temp = parent->right
//	parent->right = pivot->left
//	temp->left = pivot->right
//	pivot->left = parent;
//	pivot->right = temp;
//	if (gp == NULL) head = pivot;
//	else if (gp->data < parent->data) gp->right = pivot;
//	else gp->left = pivot;
//}

template<class T1, class T2>
inline bool Nodey<T1, T2>::operator>(Nodey* temp)
{
	return this->key > temp->key;
}

template<class T1, class T2>
inline bool Nodey<T1, T2>::operator<(Nodey* temp)
{
	return this->key < temp->key;
}

template<class T1, class T2>
inline bool Nodey<T1, T2>::operator==(Nodey* temp)
{
	return this->key == temp->key;
}