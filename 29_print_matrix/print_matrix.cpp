/*
 * 面试题29：顺时针打印矩阵
 * 题目：输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。
 */
#include <stdexcept>
using namespace std;

/* Solution 顺时针完整一圈，在最内层圈有可能不是完整的四条边，需要判断是否提前结束 */
void print_matrix(int** numbers, int columns, int rows){
  // 判断输入有效
  if(numbers == nullptr || columns <= 0 || rows <= 0)
    throw runtime_error("input invalid.");

  // 边界条件
  int start_row = 0;
  int end_row = rows - 1;
  int start_col = 0;
  int end_col = columns - 1;
  int count = rows * columns;

  while(count > 0){
    // top row
    for(int i = start_col; i <= end_col; i++){
      printf("%d\t", numbers[start_row][i]);
      count--;
    }
    start_row++;

    // right column
    if(start_row > end_row) //如果不存在这条边就结束循环
      break;

    for(int i = start_row; i <= end_row; i++){
      printf("%d\t", numbers[i][end_col]);
      count--;
    }
    end_col--;

    // bottom row
    if(start_col > end_col) //如果不存在这条边就结束循环
      break;

    for(int i = end_col; i >= start_col; i--){
      printf("%d\t", numbers[end_row][i]);
      count--;
    }
    end_row--;

    // left column
    if(start_row > end_row) //如果不存在这条边就结束循环
      break;

    for(int i = end_row; i >= start_row; i--){
      printf("%d\t", numbers[i][start_col]);
      count--;
    }
    start_col++;
  }
}

/*
 * 测试代码
 */
// ====================测试代码====================
void Test(int columns, int rows)
{
  printf("Test Begin: %d columns, %d rows.\n", columns, rows);

  if(columns < 1 || rows < 1)
      return;

  int** numbers = new int*[rows];
  for(int i = 0; i < rows; ++i)
  {
      numbers[i] = new int[columns];
      for(int j = 0; j < columns; ++j)
      {
          numbers[i][j] = i * columns + j + 1;
      }
  }

  print_matrix(numbers, columns, rows);
  printf("\n");

  for(int i = 0; i < rows; ++i)
      delete[] (int*)numbers[i];

  delete[] numbers;
}

int main(int argc, char* argv[])
{
  /*
  1    
  */
  Test(1, 1);

  /*
  1    2
  3    4
  */
  Test(2, 2);

  /*
  1    2    3    4
  5    6    7    8
  9    10   11   12
  13   14   15   16
  */
  Test(4, 4);

  /*
  1    2    3    4    5
  6    7    8    9    10
  11   12   13   14   15
  16   17   18   19   20
  21   22   23   24   25
  */
  Test(5, 5);

  /*
  1
  2
  3
  4
  5
  */
  Test(1, 5);

  /*
  1    2
  3    4
  5    6
  7    8
  9    10
  */
  Test(2, 5);

  /*
  1    2    3
  4    5    6
  7    8    9
  10   11   12
  13   14   15
  */
  Test(3, 5);

  /*
  1    2    3    4
  5    6    7    8
  9    10   11   12
  13   14   15   16
  17   18   19   20
  */
  Test(4, 5);

  /*
  1    2    3    4    5
  */
  Test(5, 1);

  /*
  1    2    3    4    5
  6    7    8    9    10
  */
  Test(5, 2);

  /*
  1    2    3    4    5
  6    7    8    9    10
  11   12   13   14    15
  */
  Test(5, 3);

  /*
  1    2    3    4    5
  6    7    8    9    10
  11   12   13   14   15
  16   17   18   19   20
  */
  Test(5, 4);

  return 0;
}
