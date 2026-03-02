#include <iostream>
#include <cstddef>

template< class T >
T* merge(const T* const* a, size_t sa, size_t* sai, T* c)
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

    T max_el = a[indMax][sai[indMax] - 1];

    for (size_t i = indMax + 1; i < sa; ++i)
    {
      if (sai[i] > 0 && max_el < a[i][sai[i] - 1])
      {
        max_el = a[i][sai[i] - 1];
        indMax = i;
      }
    }

    c[k - 1] = max_el;
    --k;
    --sai[indMax];
    
  }
  return c;
}

int main()
{
  int arr0[] = {13, 69, 228};
  int arr1[] = {52, 420, 666};
  int arr2[] = {911, 1337, 1488};

  const int* a[] = {arr0, arr1, arr2};
  size_t sai[] = {3, 3, 3};
  size_t sa = 3;

  int c[9];

  merge(a, sa, sai, c);

  for (size_t i = 0; i < 9; ++i)
  {
    std::cout << c[i] << " ";
  }
  std::cout << '\n';

  return 0;
}
