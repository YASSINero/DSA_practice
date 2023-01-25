#include <iostream>
#include <vector>

#include "Queue.h"

int main()
{
    Queue<int> q(15), q2(20);

    q.push(18);
    q2.push(19);
    
    q.pop();
    q2.pop();
    
    q.push(24);
    q2.push(25);
    
    q.push(49);
    q2.push(50);
    
    q = q + q2;

    Queue<int> q3(q);
    

}

