/*
 * 面试题9：用两个栈实现队列
 * 题目：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail
 * 和deleteHead，分别完成在队列尾部插入结点和在队列头部删除结点的功能。
 */
#include <cstdio>
#include <stack>
#include <stdexcept>
using namespace std;

/*
 * 实现队列类
 */
template <typename T> class CQueue{
  public:
    CQueue(void);
    ~CQueue(void);
    void appendTail(const T& node);
    T deleteHead();
  
  private:
    stack<T> stack1;
    stack<T> stack2;
};

template <typename T> CQueue<T>::CQueue(void){}
template <typename T> CQueue<T>::~CQueue(void){}

template <typename T> void CQueue<T>::appendTail(const T& node){
  stack1.push(node);
}

template <typename T> T CQueue<T>::deleteHead(){
  // 如果栈2为空，先把栈1所有元素依次出栈，并压入栈2
  if(stack2.size() <= 0){
    while(stack1.size() > 0){
      T& data = stack1.top();
      stack1.pop();
      stack2.push(data);
    }
  }

  // 弹出栈2的顶
  if(stack2.size() == 0 )
    throw runtime_error("queue is empty.");
  
  T head = stack2.top();
  stack2.pop();

  return head;
}

/* 
 * 测试代码
 */
void Test(char actual, char excepted){
  if(actual == excepted)
    printf("passed.\n");
  else
    printf("failed.\n");
}

int main(int argc, char* argv[]){
  CQueue<char> queue;

  queue.appendTail('a');
  queue.appendTail('b');
  queue.appendTail('c');

  char head = queue.deleteHead();
  Test(head, 'a');

  head = queue.deleteHead();
  Test(head, 'b');

  queue.appendTail('d');
  head = queue.deleteHead();
  Test(head, 'c');

  queue.appendTail('e');
  head = queue.deleteHead();
  Test(head, 'd');

  head = queue.deleteHead();
  Test(head, 'e');

  return 0;
}