#include <iostream>
#include <deque>
using namespace std;

template <typename T>
class TrackingDeque : public deque<T>
{
  public:
    TrackingDeque();
    ~TrackingDeque();
    void push_back(T target);
    void push_front(T target);
  private:
    int max;
};

template <typename T>
TrackingDeque<T>::TrackingDeque() : max(0) {}

template <typename T>
TrackingDeque<T>::~TrackingDeque()
{
  cout << "--> " << max << " <--" << endl;
}

template <typename T>
void TrackingDeque<T>::push_back(T target)
{
  deque<T>::push_back(target);
  if(deque<T>::size() > max)
    max = deque<T>::size();
}

template <typename T>
void TrackingDeque<T>::push_front(T target)
{
  deque<T>::push_front(target);
  if(deque<T>::size() > max)
    max = deque<T>::size();
}

