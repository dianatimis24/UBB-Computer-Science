#pragma once

template <typename T>
class DynamicVector {
private:
	T* elements;
	int size, capacity;

	/// A function that resizes the DynamicVector with a given resizing factor.
	void resize(int resizingFactor = 2);

public:
	/// Constructor, with a given initial capacity
	DynamicVector(int initialCapacity = 10);

	/// Copy Constructor
	DynamicVector(const DynamicVector& vector);

	/// Destructor
	~DynamicVector();

	/// Assignment Operator
	DynamicVector& operator=(const DynamicVector& vector);

	/// <summary>
	/// A function that adds an element to the dynamic vector.
	/// </summary>
	/// <param name="element">A reference to the element we want to add</param>
	void addElement(const T& element);

	/// <summary>
	/// A function that removes the element from the given position in the dynamic vector.
	/// </summary>
	/// <param name="position">The position of the element we want to remove</param>
	void removeElement(int position);

	/// <summary>
	/// A function that updates the element from the given position in the dynamic vector with a given element.
	/// </summary>
	/// <param name="position">The position of the element we want to update</param>
	/// <param name="element">A reference to the updated element</param>
	void updateElement(int position, const T& element);

	/// <summary>
	/// A function that searches for a given element in the dynamic vector and returns its position or -1 if the element is not in the vector.
	/// </summary>
	/// <param name="element">A reference to the searched element</param>
	/// <returns>The position of the element or -1, if the element is not in the dynamic vector</returns>
	int returnPosition(const T& element) const;

	/// A function that returns the size of the dynamic vector.
	size_t getSize() const;

	/// <summary>
	/// Operator[] - allows us to use the syntax vector[index] to access the index-th element in the DynamicVector vector.
	/// </summary>
	/// <param name="index">The position of the element in the dynamic vector</param>
	/// <returns>A reference to the element stored at the specified index in the dynamic vector</returns>
	T& operator[](int index);

	/// A function that returns the element from a given position or throws an exception if the position is not valid.
	T getElement(int position) const;

	// Additional Lab Requirements - Lab 5
	friend DynamicVector<T>& operator+(DynamicVector& vector, const T& element) {
		vector.addElement(element);
		return vector;
	}
	friend DynamicVector<T>& operator+(const T& element, DynamicVector& vector) {
		vector.addElement(element);
		return vector;
	}

public:
	class Iterator {
	private:
		T* pointerToVector;

	public:
		Iterator(T* pointerToVector = nullptr) : pointerToVector{pointerToVector} {}

		T& operator*() const { return *pointerToVector; }

		Iterator &operator++()
		{
			++pointerToVector;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator copyIterator = *this;
			pointerToVector++;
			return copyIterator;
		}

		bool operator==(const Iterator& other) const { return pointerToVector == other.pointerToVector; }
		bool operator!=(const Iterator& other) const { return pointerToVector != other.pointerToVector; }
	};

	Iterator begin() const { return Iterator(this->elements); }
	Iterator end() const { return Iterator(this->elements + this->size); }
};

template<typename T>
DynamicVector<T>::DynamicVector(int initialCapacity)
{
	this->size = 0;
	this->capacity = initialCapacity;
	this->elements = new T[initialCapacity];
}

template<typename T>
DynamicVector<T>::DynamicVector(const DynamicVector& vector)
{
	this->size = vector.size;
	this->capacity = vector.capacity;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->size; ++i)
		this->elements[i] = vector.elements[i];
}

template<typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elements;
}

template<typename T>
DynamicVector<T> &DynamicVector<T>::operator=(const DynamicVector& vector)
{
	if (this == &vector)
		return *this;
	this->size = vector.size;
	this->capacity = vector.capacity;
	delete[] this->elements;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->size; ++i)
		this->elements[i] = vector.elements[i];
	return *this;
}

template<typename T>
void DynamicVector<T>::addElement(const T& element)
{
	if (this->size == this->capacity)
		this->resize();
	this->elements[this->size] = element;
	++this->size;
}

template<typename T>
void DynamicVector<T>::removeElement(int position)
{
	if (position < 0 || position >= this->size)
		throw std::invalid_argument("Invalid position!");
	for (int i = position; i < this->size - 1; i++)
		this->elements[i] = this->elements[i + 1];
	--this->size;
}

template<typename T>
void DynamicVector<T>::updateElement(int position, const T& element)
{
	if (position < 0 || position >= this->size)
		throw std::invalid_argument("Invalid position!");
	this->elements[position] = element;
}

template<typename T>
int DynamicVector<T>::returnPosition(const T& element) const
{
	for (int i = 0; i < this->size; i++)
		if (this->elements[i] == element)
			return i;
	return -1;
}

template<typename T>
size_t DynamicVector<T>::getSize() const
{
	return this->size;
}

template<typename T>
T& DynamicVector<T>::operator[](int index)
{
	if (index < 0 || index >= this->size)
		throw std::out_of_range("Index out of range!");
	return this->elements[index];
}

template<typename T>
T DynamicVector<T>::getElement(int position) const
{
	if (position < 0 || position >= this->size)
		throw std::invalid_argument("Invalid position!");
	return this->elements[position];
}

template<typename T>
void DynamicVector<T>::resize(int resizingFactor)
{
	this->capacity *= resizingFactor;
	T* resizedVector = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		resizedVector[i] = this->elements[i];
	delete[] this->elements;
	this->elements = resizedVector;
}
