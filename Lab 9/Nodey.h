#pragma once

template <class T>
class Nodey
{
private:
	T data;
public:
	Nodey<T>();
	Nodey(T val, Nodey<T>* right = nullptr, Nodey<T>* left = nullptr);
	Nodey<T>* right;
	Nodey<T>* left;
	int freq = 1;
	T getData() { return this->data; }
	void setData(T val) { this->data = val; }
	void destroyWithChildren();
	void rotateLeft(Nodey<T>* parent, Nodey<T>* nR, Nodey<T>* nL, Nodey<T>* root);
	void rotateRight(Nodey<T>* grandparent, Nodey<T>* pivot);
	void rotateLR(Nodey<T>* gp, Nodey<T>* parent, Nodey<T>* pivot);
	void rotateRL(Nodey<T>* gp, Nodey<T>* parent, Nodey<T>* pivot);
	bool operator>(Nodey* temp);
	bool operator<(Nodey* temp);
	bool operator==(Nodey* temp);
};

template<typename T>
inline Nodey<T>::Nodey()
{
	this->data = (T)NULL;
	this->right = nullptr;
	this->left = nullptr;
}

template<typename T>
inline Nodey<T>::Nodey(T val, Nodey<T>* right, Nodey<T>* left)
{
	this->data = val;
	this->right = right;
	this->left = left;
}

template<typename T>
inline void Nodey<T>::destroyWithChildren()
{
	if (this->right)
		this->right->destroyWithChildren();

	if (this->left)
		this->left->destroyWithChildren();

	delete this;
}

template<typename T>
inline void Nodey<T>::rotateLeft(Nodey<T>* parent, Nodey<T>* nR, Nodey<T>* nL, Nodey<T>* root)
{
	if (parent == root) {
		Nodey<T>* temp = head->right;
		temp->left = root;
		root->right = NULL;
		root = temp;
	}
	else {
		parent->right = nR;
		nL->right = nR->left;
		nR->left = nL;
	}
}

template<typename T>
inline void Nodey<T>::rotateRight(Nodey<T>* grandparent, Nodey<T>* pivot)
{
	if (grandparent->data > pivot->data) {
		Nodey<T>* temp = grandparent->left;
		grandparent->left = pivot;
		temp->left = pivot->right;
	}
	else {
		Nodey<T>* temp = grandparent->right;
		grandparent->right = pivot;
		temp->left = pivot->right;
		pivot->right = temp;
	}
}

template<typename T>
inline void Nodey<T>::rotateLR(Nodey<T>* gp, Nodey<T>* parent, Nodey<T>* pivot)
{
	node* temp = parent->left
	parent->left = pivot->right
	temp->right = pivot->left
	pivot->right = parent;
	pivot->left = temp;
	if (gp == NULL) head = pivot;
	else if (gp->data < parent->data) gp->right = pivot;
	else gp->left = pivot;
}

template<typename T>
inline void Nodey<T>::rotateRL(Nodey<T>* gp, Nodey<T>* parent, Nodey<T>* pivot)
{
	node* temp = parent->right
	parent->right = pivot->left
	temp->left = pivot->right
	pivot->left = parent;
	pivot->right = temp;
	if (gp == NULL) head = pivot;
	else if (gp->data < parent->data) gp->right = pivot;
	else gp->left = pivot;
}

template<typename T>
inline bool Nodey<T>::operator>(Nodey* temp)
{
	return this->freq > temp->freq;
}

template<typename T>
inline bool Nodey<T>::operator<(Nodey* temp)
{
	return this->freq < temp->freq;
}

template<typename T>
inline bool Nodey<T>::operator==(Nodey* temp)
{
	return this->freq == temp->freq;
}