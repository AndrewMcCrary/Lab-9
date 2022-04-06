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
	Nodey<T1, T2>(T1 key, T2 data = (T2)NULL, Nodey<T1, T2>* right = nullptr, Nodey<T1, T2>* left = nullptr);

	/// <summary>
	/// The right child.
	/// </summary>
	Nodey<T1, T2>* right;

	/// <summary>
	/// The left child.
	/// </summary>
	Nodey<T1, T2>* left;

	/// <summary>
	/// The balance factor.
	/// </summary>
	int balanceFactor = 0;

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
	T2* getDataAddr() { return &(this->data); }

	/// <summary>
	/// Sets the nodes data.
	/// </summary>
	/// <param name="val">The new data.</param>
	void setData(T2 val) { this->data = val; }

	/// <summary>
	/// Destroys all subtrees
	/// </summary>
	void destroyWithChildren();

	bool operator>(Nodey* temp);
	bool operator<(Nodey* temp);
	bool operator==(Nodey* temp);
};


template<class T1, class T2>
inline Nodey<T1, T2>::Nodey(T1 key, T2 data, Nodey<T1, T2>* right, Nodey<T1, T2>* left)
{
	this->key = key;
	this->data = data;
	this->right = right;
	this->left = left;
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