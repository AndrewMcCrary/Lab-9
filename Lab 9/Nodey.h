#pragma once

template <typename T>
class Nodey
{
private:
	T data;
public:
	Nodey();
	Nodey(T val, Nodey<T>* right = nullptr, Nodey<T>* left = nullptr);
	Nodey<T>* right;
	Nodey<T>* left;
	T getData() { return this->data; }
	void setData(T val) { this->data = val; }
	void destroyWithChildren();
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
