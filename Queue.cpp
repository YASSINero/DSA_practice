#include "Queue.h"
#include <stdexcept>


Queue::~Queue()
{
	delete[] queue;
}

Queue::Queue(const Queue& other): frontInd(other.frontInd), backInd(other.backInd), queue(nullptr), size_(other.size_), count_(other.count_)
{
	if (size_ > 0)
	{
		queue = new int[size_];
		std::memcpy(queue, other.queue, sizeof(int) * size_);
	}
}

Queue::Queue(size_t q_size): frontInd(0), backInd(-1), queue(nullptr), size_(q_size),  count_(0)
{
	if (q_size > 0)
		queue = new int[q_size];

	std::fill_n(queue, static_cast<int>(q_size), -1);

}

bool Queue::isEmpty() const
{
	return frontInd > backInd;
}

int Queue::front() const
{
	return queue[frontInd];
}

size_t Queue::size() const
{
	return size_;
}

size_t Queue::count() const
{
	return count_;
}


void swap(Queue& q1, Queue& q2) noexcept
{
	using std::swap;

	//swap all 
	swap(q1.frontInd, q2.frontInd);
	swap(q1.backInd, q2.backInd);
	swap(q1.queue, q2.queue);
	swap(q1.size_, q2.size_);
	swap(q1.count_, q2.count_);
}

bool Queue::push(int val)
{
	if(backInd < static_cast<int>(size_))
	{
		*(queue + (++backInd)) = val;
		count_++;
		return queue[backInd] == val;
	}
	return false;
}

bool Queue::pop()
{
	if(!isEmpty())
	{
		queue[frontInd++] = 0;
		count_--;
		return true;
	}
	return false;
}