/*
 * 面试题17：打印1到最大的n位数
 * 题目：输入数字n，按顺序打印出从1最大的n位十进制数。比如输入3，则
 * 打印出1、2、3一直到最大的3位数即999。需要考虑大数情况。
 */
#include <cstdio>
#include <memory>

/*
 * 函数声明
 */
bool increment_string(char* number);
void print_string(char* number);

void print_nrange_digits_sol1(int n){
  // 判断输入有效
  if(n <= 0)
    return ;
  
  // 用字符串模拟数字
  char *number = new char[n+1];
  memset(number, '0', n);
  number[n] = '\0';

  while(!increment_string(number)){
    print_string(number);
  }

  delete[] number;
}

bool increment_string(char* number){
  // 用字符串，模拟数字的加法，每次调用+1，并判断是否溢出
  bool isOverFlow = false;
  int nLength = strlen(number);
  int nTakeOver = 0;
  
  // 从最低位开始
  for(int i = nLength-1; i >= 0; i--){
    int nSum = number[i] - '0' + nTakeOver;
    if(i == nLength-1)
      nSum++;

    if(nSum >= 10){
      if(i == 0){
        // trick，当最高位产生进位时，说明溢出了
        isOverFlow = true;
      }else{
        nSum -= 10;
        nTakeOver = 1;
        number[i] = '0' + nSum;
      }
    }else{
      number[i] = '0' + nSum;
      break;
    }
  }

  return isOverFlow;
}

void print_string(char* number){
  // 忽略字符串开头的所有‘0’
  bool isBeginZero = true;
  int nLength = strlen(number);

  for(int i=0; i < nLength; i++){
    if(isBeginZero && number[i] != '0')
      isBeginZero = false;
    
    if(!isBeginZero)
      printf("%c", number[i]);
  }

  printf("\t");
}

/*
 * 测试代码
 */
void Test(int n)
{
    printf("Test for %d begins:\n", n);

    print_nrange_digits_sol1(n);
    // Print1ToMaxOfNDigits_2(n);

    printf("\nTest for %d ends.\n", n);
}

int main(int argc, char* argv[])
{
    Test(1);
    Test(2);
    Test(3);
    Test(0);
    Test(-1);

    return 0;
}