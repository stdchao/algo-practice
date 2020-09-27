/*
 * 面试题15：二进制中1的个数
 * 题目：请实现一个函数，输入一个整数，输出该数二进制表示中1的个数。例如
 * 把9表示成二进制是1001，有2位是1。因此如果输入9，该函数输出2。
 */
#include <cstdio>

int one_in_binary_solution1(int n){
  int count = 0;

  // 算法：如果右移数字n，需要考虑符号问题；用一个flag=1不断左移，并同数字n做与运算,
  // 直至flag超出usigned int范围变为0
  unsigned int flag = 1;
  while(flag){
    if(n & flag)
      count++;
    
    flag = flag << 1;
  }

  return count;
}

int one_in_binary_solution2(int n){
  int count = 0;

  // 算法：数字减1后，与原数字做与运算，即可以去掉原数字最右的1
  while(n){
    count++;

    n = (n - 1) & n;
  }

  return count;
}

/*
 * 测试代码
 */
// ====================测试代码====================
void Test(int number, unsigned int expected)
{
    int actual = one_in_binary_solution1(number);
    if (actual == expected)
        printf("Solution1: Test for %x passed.\n", number);
    else
        printf("Solution1: Test for %x failed.\n", number);

    actual = one_in_binary_solution2(number);
    if (actual == expected)
        printf("Solution2: Test for %x passed.\n", number);
    else
        printf("Solution2: Test for %x failed.\n", number);

    printf("\n");
}

int main(int argc, char* argv[])
{
    // 输入0，期待的输出是0
    Test(0, 0);

    // 输入1，期待的输出是1
    Test(1, 1);

    // 输入10，期待的输出是2
    Test(10, 2);

    // 输入0x7FFFFFFF，期待的输出是31
    Test(0x7FFFFFFF, 31);

    // 输入0xFFFFFFFF（负数），期待的输出是32
    Test(0xFFFFFFFF, 32);

    // 输入0x80000000（负数），期待的输出是1
    Test(0x80000000, 1);

    return 0;
}