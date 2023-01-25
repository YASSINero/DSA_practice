#pragma once

#include <algorithm>
#include <memory>

template<typename T>
class Queue
{
	int frontInd, backInd;
	T *queue;
	size_t size_, count_;


public:
	Queue() = default;
	Queue(size_t q_size): frontInd(0), backInd(-1), queue(nullptr), size_(q_size), count_(0)
	{
		if (q_size > 0)
			queue = new T[q_size];

		std::fill_n(queue, static_cast<int>(q_size), -1);

	}

	~Queue() { delete[] queue; }

	Queue(const Queue& other) : frontInd(other.frontInd), backInd(other.backInd), queue(nullptr), size_(other.size_), count_(other.count_)
	{
		if (size_ > 0)
		{
			queue = new T[size_];
			std::memcpy(queue, other.queue, sizeof(T) * size_);
		}
	}

public:
	bool push(T val)
	{
		if (backInd < static_cast<int>(size_))
		{
			*(queue + (++backInd)) = val;
			count_++;
			return queue[backInd] == val;
		}
		return false;
	}

	bool pop()
	{
		if (!isEmpty())
		{
			queue[frontInd++] = 0;
			count_--;
			return true;
		}
		return false;
	}

	bool isEmpty() const
	{
		return frontInd > backInd;
	}

	auto front() const
	{
		return queue[frontInd];
	}

	size_t size() const
	{
		return size_;
	}

	size_t count() const
	{
		return count_;
	}


public:

	Queue& operator=(Queue otherQ)
	{
		swap(*this, otherQ);

		return *this;
	}

	friend Queue operator+(Queue<T> left_q, const Queue<T> &other_q)
	{
		//Todo Provide commented explanation & perfect logic 
		if(left_q.isEmpty() || other_q.isEmpty())
		{
			return other_q.isEmpty() ? left_q : other_q;
		}

		Queue<T> tempQ(left_q.size_ + other_q.size_);

		tempQ.count_ = left_q.count_ + other_q.count_;

		qMerge(left_q, other_q, tempQ);

		for(size_t i = 0; i < tempQ.size_; i++)
		{
			if(tempQ.queue[i])
			{
				tempQ.frontInd = static_cast<int>(i);
				break;
			}
		}


		tempQ.backInd = static_cast<int>(tempQ.count_) != 0 ? static_cast<int>(tempQ.count_) : tempQ.frontInd - 1;

		return tempQ;
	}


private:
		//Todo Perfect loop, see online gdb for ideas
	static void qMerge(const Queue& q1, const Queue& q2, Queue& dest_q)
	{
		auto uniqTemp = std::make_unique<T[]>(q1.size_ + q2.size_);
		std::fill(uniqTemp.get(), uniqTemp.get() + q1.size_ + q2.size_, -1);

		std::swap_ranges(q1.queue, q1.queue + q1.size_, uniqTemp.get());

		int* range1 = uniqTemp.get()+1, * range2 = q2.queue;

		//then copy from q2
		//Todo test simplified loop
		while (*range2 == (*range1 != -1 ? *range2 : 0))
		{
			range1 = *range1 != -1 ? range1 + 1 : range1;
			range2 = *range2 == 0 ? range2 + 1 : range2;
		}

		std::memcpy(range1, range2, q2.size_);

		dest_q.queue = uniqTemp.release();	//data in this line is as wanted

	}

	friend void swap(Queue<T>& q1, Queue<T>& q2) noexcept
	{
		using std::swap;

		//swap all 
		swap(q1.frontInd, q2.frontInd);
		swap(q1.backInd, q2.backInd);
		swap(q1.queue, q2.queue);
		swap(q1.size_, q2.size_);
		swap(q1.count_, q2.count_);
	}

};
