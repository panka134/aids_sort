#include "generator.h"
#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

void heapify(int tab[], int parent, int heapsize)
  {
    int l = 2*parent+1, r = 2*parent+2, largest;

    if(l<heapsize && tab[l]>tab[parent])
      largest = l;
    else
      largest = parent;
    if(r<heapsize && tab[r]>tab[largest])
      largest = r;

    if (largest!=parent)
    {
      swap(tab[largest], tab[parent]);
      heapify(tab, largest, heapsize);
    }

  }

void build_heap(int tab[], int n)
  {
    for(int i=n/2-1; i>=0; i--)
      heapify(tab, i, n);
  }

void heap(int tab[], int heapsize)
{
  build_heap(tab, heapsize);

  for(int i=heapsize-1; i>0; i--)
  {
    swap(tab[0], tab[i]);
    heapsize--;
    heapify(tab, 0, heapsize);
  }
}


int main()
{
  int n = 1000;
  char shape;
  int numbers[10000];
  fstream file;

  cin>>shape;

  file.open("heap.txt", ios::out);
  do
  {
    if(shape!='q')
    {
      mgenerate(numbers, n, shape);

      /*cout<<"generated: ";
      for (int i=0; i<n; i++)
          cout << numbers[i] <<" ";
      cout<<endl;*/

      auto start = chrono::steady_clock::now();
      heap(numbers, n);
      auto end = chrono::steady_clock::now();

    //   cout<<"sorted: ";
    //   for (int i=0; i<n; i++)
    //       cout << numbers[i] <<" ";
    //   cout<<endl;
    //
    cout <<n<<" time: " << chrono::duration_cast<chrono::microseconds>(end - start).count()
    << " μs" << endl;
      file<<chrono::duration_cast<chrono::microseconds>(end - start).count()<<endl;
      n+=200;
    }
  }while (shape !='q' && n<=10000);
  return 0;
}
