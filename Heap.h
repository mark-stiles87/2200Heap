//--------------------------------------------------------------------
//
//  Laboratory 12                                             Heap.h
//
//  Class declaration for the array implementation of the Heap ADataType
//
//--------------------------------------------------------------------

#pragma once

#include <stdexcept>
#include <iostream>

using namespace std;

template < typename KeyType = int >
class Less {
public:
	bool operator()(const KeyType &a, const KeyType &b) const { return a < b; }
};

template < typename DataType, typename KeyType = int, typename Comparator = Less<KeyType> >
class Heap
{
public:

	static const int DEFAULT_MAX_HEAP_SIZE = 10;    // Default maximum heap size

	// Constructor
	Heap(int = DEFAULT_MAX_HEAP_SIZE); // Default constructor + basic constr
	Heap(const Heap&);		    // Copy constructor
	Heap& operator= (const Heap&);  // Overloaded assignment operator

	// Destructor
	~Heap();

	// Heap manipulation operations
	void insert(const DataType&);    // Insert a data item
	//Requires: A DataType to insert.
	//Result: The item is inserted and the array is still in heap form.
	DataType remove();  // Remove max priority element
	void clear();                          // Clear heap

	// Heap status operations
	bool isEmpty() const;                  // Heap is empty
	bool isFull() const;                   // Heap is full

	bool operator==(const Heap&) const; //overloaded boolean equality.
	//Requires: Another heap.
	//Result: Returns 1 if the heaps are equivalent or 0 otherwise.

	// Output the heap structure -- used in testing/debugging
	void showStructure() const;

	// Programming exercise #3 operation
	// void writeLevels() const;              // Output in level order

private:

	// Recursive helper of the showStructure() function
	void showSubtree(int index, int level) const;

	void heapifyUp(const int, const DataType&); //Helper for insertion.
	//Requires: an array that is not in heap form.
	//Result: dataItems is in heap form.

	// Data members
	int maxSize,   // Maximum number of elements in the heap
		size;      // Actual number of elements in the heap
	DataType *dataItems; // Array containing the heap elements

	Comparator comparator;
};

template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	dataItems = new DataType[maxSize];
}

template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(const Heap& other)
{
	this = other;
}

template <typename DataType, typename KeyType, typename Comparator>
Heap& Heap<DataType, KeyType, Comparator>::operator=(const Heap& other)
{
	if (this == other)
		return this;
	delete[] dataItems;
	maxSize = other.maxSize;
	dataItems = new DataType[maxSize];
	size = other.size;
	for (int i = 0; i < size; i++)
		dataItems[i] = other.dataItems[i];
	return this;
}

template <typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::operator==(const Heap& other) const
{
	if (size != other.size)
		return 0;
	for (int i = 0; i < size; i++)
	{
		if (dataItems[i] != other.dataItems[i])
			return 0;
	}
	return 1;
}

template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::~Heap()
{
	clear();
	delete[] dataItems;
}

template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::insert(const DataType& newData)
{
	heapifyUp(size, newData);
	size++;
	return;
}

template <typename DataType, typename KeyType, typename Comparator>
DataType Heap<DataType, KeyType, Comparator>::remove()
{
	if (size == 0)
		return;
	else if (size == 1)
	{
		retVal = new dataItems[0];
		delete dataItems[0];

		return retVal;
	}
	else
		const int last = size - 1;
		const int first = 0;

		retVal = new dataItems[first];
		delete dataItems[first];

		dataItems[first] = new dataItems[last];
		delete dataItems[last];

		int i = 0;

		// checks if the current data item is less than one of its children AND stops before end of array is
		// reached

		while ((comparator(i, i + 1) || comparator(i, i + 2)) && comparator(i, size - 3))
		{
			if (comparator(i + 2, i + 1))
			{
				if (comparator(i, i + 1))
				{
					temp = new dataItems[i];
					delete dataItems[i];

					dataItems[i] = new dataItems[i + 1];
					dataItems[i + 1] = temp;
					i = i + 1;
				}
			}
			else if (comparator(i + 1, i + 2))
			{
				if (comparator(i, i + 2))
				{
					temp = new dataItem[i];
					delete dataItems[i];

					dataItems[i] = new dataItems[i + 2];
					dataItems[i + 2] = temp;
					i = i + 2;
				}
			}

		}
		return retVal;
}

template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::clear()
{
	for (int i = 0; i < size; i++)
	{
		if (dataItems[i] != NULL)
			delete dataItems[i];
	}
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::showStructure() const

	// Outputs the priorities of the data items in a heap in both array
	// and tree form. If the heap is empty, outputs "Empty heap". This
	// operation is intended for testing/debugging purposes only.

{
	int j;   // Loop counter

	cout << endl;
	if (size == 0)
		cout << "Empty heap" << endl;
	else
	{
		cout << "size = " << size << endl;       // Output array form
		for (j = 0; j < maxSize; j++)
			cout << j << "\t";
		cout << endl;
		for (j = 0; j < size; j++)
			cout << dataItems[j].getPriority() << "\t";
		cout << endl << endl;
		showSubtree(0, 0);                        // Output tree form
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::showSubtree(int index, int level) const

	// Helper function for the showStructure() function. Outputs the
	// subtree (subheap) whose root is stored in dataItems[index]. Argument
	// level is the level of this dataItems within the tree.

{
	int j;   // Loop counter

	if (index < size)
	{
		showSubtree(2 * index + 2, level + 1);        // Output right subtree
		for (j = 0; j < level; j++)        // Tab over to level
			cout << "\t";
		cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
		if (2 * index + 2 < size)                // Output "connector"
			cout << "<";
		else if (2 * index + 1 < size)
			cout << "\\";
		cout << endl;
		showSubtree(2 * index + 1, level + 1);        // Output left subtree
	}
}

template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::heapifyUp(const int index, const DataType& data)
{
	int child = index, current = index;
	int parent = (child - 1) / 2;
	dataItems[index] = data;
	while (comparator(dataItems[parent], data))
	{
		dataItems[child] = dataItems[parent];
		child = parent;
		parent = (child - 1) / 2;
		current = child;
	}
	dataItems[current] = data;
	return;
}

template <typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
	return 0 == size;
}

template <typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isFull() const
{
	return size == maxSize;
}
