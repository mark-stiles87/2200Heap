//--------------------------------------------------------------------
//
//  Laboratory 12, Programming Exercise 1              PriorityQueue.h
//
//  Class declaration for the heap implementation of the
//  Priority Queue ADT -- inherits the array implementation of the
//  Heap ADT
//
//--------------------------------------------------------------------

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdexcept>
#include <iostream>

using namespace std;

#include "Heap.h"

const int MAX_QUEUE_SIZE = 10;   // Default maximum queue size

template < typename DataType, typename KeyType = int, typename Comparator = Less<KeyType> >
class PriorityQueue : public Heap<DataType>
{
public:

	// Constructor
	PriorityQueue(int maxNumber = MAX_QUEUE_SIZE);
	// Destructor
	~PriorityQueue();

	PriorityQueue(const Heap& other);
	PriorityQueue& operator = (const PriorityQueue& other);

	// Queue manipulation operations
	void enqueue(const DataType &newDataItem);   // Enqueue data element
	DataType dequeue();  // Dequeue data element


	void clear();
	bool isEmpty();
	bool ifFull();

};

template <typename DataType, typename KeyType, typename Comparator>
bool PriorityQueue<DataType, KeyType, Comparator>::isEmpty() const
{
	return 0 == size;
}

template <typename DataType, typename KeyType, typename Comparator>
bool PriorityQueue<DataType, KeyType, Comparator>::isFull() const
{
	return size == maxSize;
}

template <typename DataType, typename KeyType, typename Comparator>
PriorityQueue<DataType, KeyType, Comparator>::~PriorityQueue()
{
	clear();
	delete[] dataItems;
}

template <typename DataType, typename KeyType, typename Comparator>
PriorityQueue<DataType, KeyType, Comparator>::PriorityQueue(int maxNumber = MAX_QUEUE_SIZE)
{
	maxsize = maxNumber;
	size = 0;
	dataItems = new DataType[maxSize];
}

template <typename DataType, typename KeyType, typename Comparator>
PriorityQueue<DataType, KeyType, Comparator>::PriorityQueue(const Heap& other)
{
	this = other;
}

template <typename DataType, typename KeyType, typename Comparator>
void PriorityQueue<DataType, KeyType, Comparator>::clear()
{
	size = 0;
	return;
}

#endif
