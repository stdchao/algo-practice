#pragma once

#include <stack>
#include <assert.h>
using namespace std;

template <typename T> class StackWithMin{
  public:
    StackWithMin() {}
    virtual ~StackWithMin() {}

    void push(const T& value);
    void pop();

    const T& top() const;
    const T& min() const;

    bool empty() const;
    size_t size() const;

  private:
    stack<T> mData;
    stack<T> mMins; // 辅助栈存储最小值
};

template <typename T> void StackWithMin<T>::push(const T& value){
  mData.push(value);

  // 当新元素比之前的最小元素小时，把新元素插入辅助栈里；否则把之前的最小元素重复插入辅助栈里
  if(mMins.size() == 0 || mMins.top() > value){
    mMins.push(value);
  }else{
    mMins.push(mMins.top());
  }
}

template <typename T>void StackWithMin<T>::pop(){
  assert(mData.size() > 0 && mMins.size() > 0);

  mData.pop();
  mMins.pop();
}

template <typename T>const T& StackWithMin<T>::top() const{
  return mData.top();
}

template <typename T>const T& StackWithMin<T>::min() const{
  assert(mData.size() > 0 && mMins.size() > 0);

  return mMins.top();
}

template <typename T>bool StackWithMin<T>::empty() const{
  return mData.empty();
}

template <typename T>size_t StackWithMin<T>::size() const{
  return mData.size();
}