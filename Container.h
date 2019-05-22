#pragma once
#include <stdexcept>
#include <functional>

template <typename T>
class Node {
public:
	Node(const T& value, Node<T> * prev, Node<T> * next) : value(value), prev(prev), next(next) {}
	T value;
	Node<T>	* prev;
	Node<T>	* next;
};

class EmptyContainerException : public std::logic_error {
public:
	EmptyContainerException() : std::logic_error("Container is empty") {}
};

template <typename T>
class Container {
public:
	Container() : size(0), front(nullptr), back(nullptr) {}
	Container(const Container& other);
	Container& operator=(const Container& other);
	~Container();
	void pushFront(const T& value);
	void pushBack(const T& value);
	void popFront();
	void popBack();
	const T& getFront() const;
	const T& getBack() const;
	size_t getSize() const;
	bool isEmpty() const;
	void clean();
	void forEach(std::function<void(T&)> func);
	void forEach(std::function<void(const T&)> func) const;
private:
	size_t size;
	Node<T> * front;
	Node<T> * back;
};

template <typename T>
inline Container<T>::Container(const Container& other) : Container() {
	*this = other;
}

template<typename T>
inline Container<T>& Container<T>::operator=(const Container& other) {
	if (this == &other) {
		return *this;
	}
	clean();
	other.forEach([this](const T & elem) {	pushBack(elem); });
	return *this;
}

template<typename T>
inline Container<T>::~Container() {
	clean();
}


template <typename T>
inline void Container<T>::pushFront(const T& value) {
	Node<T> * node = new Node<T>(value, nullptr, front);
	if (isEmpty()) {
		back = node;
	} else {
		front->prev = node;
	}
	front = node;
	++size;
}

template <typename T>
inline void Container<T>::pushBack(const T& value) {
	Node<T> * node = new Node<T>(value, back, nullptr);
	if (isEmpty()) {
		front = node;
	} else {
		back->next = node;
	}
	back = node;
	++size;
}

template <typename T>
inline void Container<T>::popFront() {
	if (isEmpty()) {
		throw EmptyContainerException();
	}
	Node<T> * deleteNode = front;
	if (front == back) {
		front = nullptr;
		back = nullptr;
	}
	else {
		front = deleteNode->next;
		front->prev = nullptr;
	}
	delete deleteNode;
	--size;
}

template <typename T>
inline void Container<T>::popBack() {
	if (isEmpty()) {
		throw EmptyContainerException();
	}
	Node<T> * deleteNode = back;
	if (front == back) {
		front = nullptr;
		back = nullptr;
	}
	else {
		back = deleteNode->prev;
		back->next = nullptr;
	}
	delete deleteNode;
	--size;
}

template <typename T>
inline const T& Container<T>::getFront() const {
	if (isEmpty()) {
		throw EmptyContainerException();
	}
	return front->value;
}

template <typename T>
inline const T& Container<T>::getBack() const {
	if (isEmpty()) {
		throw EmptyContainerException();
	}
	return back->value;
}

template <typename T>
inline size_t Container<T>::getSize() const {
	return size;
}

template <typename T>
inline bool Container<T>::isEmpty() const {
	return size == 0;
}

template <typename T>
inline void Container<T>::clean() {
	while (!isEmpty()) {
		popFront();
	}
}

template <typename T>
inline void Container<T>::forEach(std::function<void(T&)> func) {
	Node<T> * elem = front;
	while (elem != nullptr)	{
		func(elem->value);
		elem = elem->next;
	}
}

template <typename T>
inline void Container<T>::forEach(std::function<void(const T&)> func) const {
	Node<T> * elem = front;
	while (elem != nullptr) {
		func(elem->value);
		elem = elem->next;
	}
}