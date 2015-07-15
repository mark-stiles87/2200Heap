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

template < typename KeyType=int >
class Less {
  public:
    bool operator()(const KeyType &a, const KeyType &b) const { return a < b; }
};

template < typename DataType, typename KeyType=int, typename Comparator=Less<KeyType> >
class Heap
{
  public:

    static const int DEFAULT_MAX_HEAP_SIZE = 10;    // Default maximum heap size

    // Constructor
    Heap (int = DEFAULT_MAX_HEAP_SIZE); // Default constructor + basic constr
    Heap (const Heap&);		    // Copy constructor
    Heap& operator= (const Heap&);  // Overloaded assignment operator

    // Destructor
    ~Heap ();

    // Heap manipulation operations
	void insert(const DataType& newDataItem);    // Insert a data item
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

	void heapify(); //Helper for insertion and removal.
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
