/*
 * 面试题5：替换空格
 * 题目：请实现一个函数，把字符串中的每个空格替换成"%20"。例如输入“We are happy.”，
 * 则输出“We%20are%20happy.”。
 */

#include <iostream>
#include <cstdio>
// #include <cstring>
using namespace std;


/*
 * 参数：
 *  str 字符串数组
 *  length 字符串数组长度，大于或等于字符串实际长度
 * 返回值：
 *  true 输入有效，且替换成功
 *  false 输入无效，或者替换不成功
 * 复杂度：
 *  时间 O(n)
 *  空间 O(1)
 */
bool replace_space(char str[], int length){
  // 判断输入有效
  if(str == nullptr || length <= 0)
    return false;
  
  // 算法：先计算替换后需要的数组长度，然后从后向前重新填写整个字符串数组
  int old_length = 0;
  int blank_length = 0;
  int new_length = 0;

  for(int i=0; str[i] != '\0'; i++){
    // 统计原字符串的长度，以及其中空格的个数
    ++old_length;
    if(str[i] == ' ')
      ++blank_length;
  }
  new_length = old_length + 2*blank_length;

  if(new_length > length)
    // 如果新字符串长度大于字符串数组长度，则需要重新分配存储才能完成操作，这里先不考虑
    return false;

  // 以new_length和old_length为起始索引，从后向前填写新字符串
  int index_of_old = old_length;
  int index_of_new = new_length;
  while(index_of_old >= 0 && index_of_new > index_of_old){
    if(str[index_of_old] == ' '){
      str[index_of_new--] = '0';
      str[index_of_new--] = '2';
      str[index_of_new--] = '%';
    }else{
      str[index_of_new--] = str[index_of_old];
    }
    --index_of_old;
  }

  // 替换成功，返回true
  return true;
}

/*
 * 测试代码
 */
void test(const char* testName, char str[], int length, const char expected[]){
  if(testName != nullptr)
    printf("%s begins: ", testName);
  
  if(replace_space(str, length)){
    if(strcmp(str, expected) == 0){
      printf("passed-replace success.\n");
    }else{
      printf("faild-repalce not correct.\n");
    }
  }else{
    if(expected == nullptr && str == nullptr){
      printf("passed-input invalid.\n");
    }else{
      printf("faild.\n");
    }
  }
}

// 测试用例
// 空格在句子中间
void Test1()
{
    const int length = 100;

    char str[length] = "hello world";
    test("Test1", str, length, "hello%20world");
}

// 空格在句子开头
void Test2()
{
    const int length = 100;

    char str[length] = " helloworld";
    test("Test2", str, length, "%20helloworld");
}

// 空格在句子末尾
void Test3()
{
    const int length = 100;

    char str[length] = "helloworld ";
    test("Test3", str, length, "helloworld%20");
}

// 连续有两个空格
void Test4()
{
    const int length = 100;

    char str[length] = "hello  world";
    test("Test4", str, length, "hello%20%20world");
}

// 传入nullptr
void Test5()
{
    test("Test5", nullptr, 0, nullptr);
}

// 传入内容为空的字符串
void Test6()
{
    const int length = 100;

    char str[length] = "";
    test("Test6", str, length, "");
}

//传入内容为一个空格的字符串
void Test7()
{
    const int length = 100;

    char str[length] = " ";
    test("Test7", str, length, "%20");
}

// 传入的字符串没有空格
void Test8()
{
    const int length = 100;

    char str[length] = "helloworld";
    test("Test8", str, length, "helloworld");
}

// 传入的字符串全是空格
void Test9()
{
    const int length = 100;

    char str[length] = "   ";
    test("Test9", str, length, "%20%20%20");
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    return 0;
}