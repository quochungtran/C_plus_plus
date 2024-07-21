// Stack : FIFO (first in first out)
// queue<data_type> variable

#include <queue>

int main()
{
    queue<int> q;
    q.push(5);
    q.push(7);
    q.push(3);

    q.pop();
    cout << q.front();
    cout << q.size();
    cout << q.empty();

    q1.swap(q2);
    return 0;
}