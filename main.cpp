#include <iostream>
#include <cstddef>
#include <stdexcept>

// ВАРИАНТ III

/*
  НЕДОСТАТКИ ЯВНОГО ИНТЕРФЕЙСА:
  1. Нет информации о размерах выходного массива. Функция по сути доверяет человеку, что массив достаточного размера, иначе при ошибке выход за границы
  2. Функция предполагает, что подмассивы отсортированы по убыванию, но это по сути никак не отражено в интерфейсе
  3. Ну и также, функция не проверяет, что подмассивы действительно отсортированы
  Ну и все, наверное...
*/

template< class T >
T* merge(const T* const* a, size_t sa, const size_t* sai, T* c)
{
  size_t count = 0;

  for (size_t i = 0; i < sa; ++i)
  {
    count += sai[i];
  }

  size_t k = count;

  while (k > 0)
  {
    size_t indMax = 0;

    while (indMax < sa && sai[indMax] == 0)
    {
      ++indMax;
    }

    T max_el;
    try
    {
      max_el = a[indMax][sai[indMax] - 1]; //конструктор копирования
    }
    catch(...)
    {
      std::cerr << "Exception in copy constructor" << '\n';
      throw;
    }

    for (size_t i = indMax + 1; i < sa; ++i)
    {
      try
      {
        if (sai[i] > 0 && max_el < a[i][sai[i] - 1]) //оператор сравнения(меньше)
        {
          max_el = a[i][sai[i] - 1]; //оператор присваивания
          indMax = i;
        }
      }
      catch(...)
      {
        std::cerr << "Failed to compare or copy element from array" << '\n';
        throw;
      }
    }
    try
    {
      c[k - 1] = max_el; //оператор присваивания
    }
    catch(...)
    {
      std::cerr << "Exception in copy operation" << '\n';
      throw;
    }
    --k;
    --sai[indMax];
  }
  return c + count;
}

int main()
{
  try
  {
    int* arr0 = new int[3]{13, 69, 228};
    int* arr1 = new int[3]{52, 420, 666};
    int* arr2 = new int[3]{911, 1337, 1488};

    const int* a[] = {arr0, arr1, arr2};
    size_t sai[] = {3, 3, 3};
    size_t sa = 3;

    int* c = new int[9];

    merge(a, sa, sai, c);

    std::cout << "Merged array: ";
    for (size_t i = 0; i < 9; ++i)
    {
      std::cout << c[i] << " ";
    }
    std::cout << '\n';

    delete[] arr0;
    delete[] arr1;
    delete[] arr2;
    delete[] c;
  }

  catch(const std::bad_alloc& e)
  {
    std::cerr << "Memory allocation failed: " << e.what() << '\n';
    return 1;
  }
  catch(const std::exception& e)
  {
    std::cerr << "Standard exception: " << e.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown exception" << '\n';
    return 1;
  }

  return 0;
}
