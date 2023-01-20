#pragma once

#include <algorithm>
#include <memory>


class Queue
{
public:
	Queue() = default;
	Queue(size_t);

	~Queue();
	Queue(const Queue& other);

public:
	bool push(int);
	bool pop();
	bool isEmpty() const;
	int	 front() const;
	size_t size() const;
	size_t count() const;

public:

	Queue& operator=(Queue otherQ)
	{
		swap(*this, otherQ);

		return *this;
	}


private:
	int frontInd, backInd;
	int *queue;

	size_t size_, count_;

private:
	static void qMerge(const Queue& q1, const Queue& q2, Queue& dest_q)
	{
		//int* qTemp = new int[q1.size_ + q2.size_];

		auto uniqTemp = std::make_unique<int[]>(q1.size_ + q2.size_);

		//or Todo swap pointers / ranges
		//std::swap(*q1.queue, *q2.queue);
		std::swap_ranges(q1.queue, q1.queue + q1.size_, uniqTemp.get());

		//then copy from q2
		for(size_t i = 0; i < q1.size_; i++)
		{
			if(i > 0 ? uniqTemp.get()[i] == -1 : false)
			{
				for (size_t j = 0; j < q2.size_; j++)
				{

					if (q2.queue[j])
					{
						std::swap_ranges(q2.queue + j, q2.queue + q2.size_, uniqTemp.get() + i);
						break;
					}
				}
				break;
			}
		}

		dest_q.queue = uniqTemp.release();	//data in this line is as wanted

/*Todo:				However it looks like the memory gets freed bc of uniqPtr*/
	}

	friend void swap(Queue& ,Queue&) noexcept;

	friend Queue operator+(Queue left_q, const Queue &other_q)
	{
		//Todo Provide commented explanation & perfect logic 
		if(left_q.isEmpty() || other_q.isEmpty())
		{
			return other_q.isEmpty() ? left_q : other_q;
		}

		Queue tempQ(left_q.size_ + other_q.size_);

		tempQ.count_ = left_q.count_ + other_q.count_;
		
		//Todo qMerge is imperfect
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
};
