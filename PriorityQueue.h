
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
                bool isFull();
 
};
 
template <typename DataType, typename KeyType, typename Comparator>
bool PriorityQueue<DataType, KeyType, Comparator>::isEmpty()
{
                return 0 == size;
}
 
template <typename DataType, typename KeyType, typename Comparator>
bool PriorityQueue<DataType, KeyType, Comparator>::isFull()
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
 
template <typename DataType, typename KeyType, typename Comparator>
PriorityQueue& PriorityQueue<DataType, KeyType, Comparator>::operator=(const PriorityQueue& other)
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
void PriorityQueue<DataType, KeyType, Comparator>::enqueue(const DataType &newDataItem)
{
                dataItems[size] = newDataItem;
                size++;
                return;
}
 
template <typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue<DataType, KeyType, Comparator>::dequeue()
{
                DataType retVal, temp;
                if (size == 0)
                	return 0;
                else if (size == 1)
                {
                	retVal = dataItems[0];
                	size--;
                	return retVal;
                }
                else
                {
                	retVal = dataItems[0];
                	dataItem[0] = dataItem[size];
                	int i = 0;
                        while (i < size)
                        {
                        	temp = dataItem[i];
                        	dataItem[i] = dataItem[i + 1];
                        	dataItem[i + 1] = temp;
                        	i++;
                        	
                        }
                        
                        delete[] dataItem[size];
                        size--;
                }
}

#endif
