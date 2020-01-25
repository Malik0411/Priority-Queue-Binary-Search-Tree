#include "PriorityQueue.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

// Implement the functions here.
// Constructor initializes heap_ to an array of size "capacity + 1", so that
// there are at most "capacity" elements in the heap.
PriorityQueue::PriorityQueue(unsigned int capacity)
{
	capacity_ = capacity;
	heap_ = new DataType[capacity_+1];
	size_ = 0;
}
  // Destructor.
PriorityQueue::~PriorityQueue()
{
	delete[] heap_;
	heap_ = NULL;
}
  
  // Enqueues "val" into the priority queue. Returns false if failed, true
  // otherwise. Assume no duplicate entries will be entered.
bool PriorityQueue::enqueue(DataType val)
{
	if (full())
		return false;
	
	if (size_ == 0)
	{
		heap_[size_+1] = val;
		size_++;
		return true;
	}
	
	heap_[size_+1] = val;
	size_++;
	
	int i = size_;
	while (heap_[i] > heap_[i/2] && i/2 != 0)
	{
		int temp = heap_[i/2];
		heap_[i/2] = heap_[i];
		heap_[i] = temp;
		i /= 2;
	}
	
	return true;
}
  // Dequeues the top element with the maximum value (priority) and rearranges
  // the resulting heap. Returns false if failed, true otherwise.
bool PriorityQueue::dequeue()
{
	if (empty())
		return false;
	
	int temp_1 = heap_[1];
	heap_[1] = heap_[size_];
	heap_[size_] = temp_1;
	
	heap_[size_] = NULL;
	size_--;
	
	int max = heap_[1], index = 0;
	for (int i = 1; i <= size_; i++)
	{
		if (heap_[i] > max)
		{
			max = heap_[i];
			index = i;
		}
	}
	
	int temp_2 = heap_[1];
	heap_[1] = max;
	heap_[index] = temp_2;
	
	while (heap_[index] > heap_[index/2] && index != 0)
	{
		int temp_3 = heap_[index/2];
		heap_[index/2] = heap_[index];
		heap_[index] = temp_3;
		index /= 2;
	}
			
	return true;
}
  
  // Returns the max element of the priority queue, but does not remove it.
PriorityQueue::DataType PriorityQueue::max() const
{
	if (empty())
		return false;
		
	return heap_[1];
}
  // Returns true if the priority queue is empty; false otherwise.
bool PriorityQueue::empty() const
{
	return (size_ == 0);
}
  // Returns true if the priority queue is full; false otherwise.
bool PriorityQueue::full() const
{
	return (size_ == capacity_);
}
  // Returns the number of elements in the priority queue.
unsigned int PriorityQueue::size() const
{
	return size_;
}
  // Print the contents of the priority queue.
void PriorityQueue::print() const
{
	cout << "(";
	for (int i = 1; i <= size_; i++)
		cout << "[" << heap_[i] << "]";
	cout << ")\n";
}
