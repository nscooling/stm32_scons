/* ---------------------------------------------------------------------------*/
/*

  FeabhOS OS abstraction layer - C++

  Template circular buffer

*/
/*
DISCLAIMER:
Feabhas is furnishing this item "as is". Feabhas does not provide any warranty
of the item whatsoever, whether express, implied, or statutory, including, but
not limited to, any warranty of merchantability or fitness for a particular
purpose or any warranty that the contents of the item will be error-free.
In no respect shall Feabhas incur any liability for any damages, including, but
limited to, direct, indirect, special, or consequential damages arising out of,
resulting from, or any way connected to the use of the item, whether or not
based upon warranty, contract, tort, or otherwise; whether or not injury was
sustained by persons or property or otherwise; and whether or not loss was
sustained from, or arose out of, the results of, the item, or any services that
may be provided by Feabhas.
*/
/* ---------------------------------------------------------------------------*/
#ifndef TEMPLATEBUFFER_H
#define TEMPLATEBUFFER_H

#include <cstdint>

using namespace std;

namespace feabhOS
{
  template <typename T = int, size_t sz = 8>
  class Buffer
  {
  public:
    enum Error { OK, FULL, EMPTY };

    Buffer();
    ~Buffer();

    Error add(T value);
    Error get(T& value);
    bool isEmpty();
    void flush();

  private:
    unsigned int read;
    unsigned int write;
    unsigned int numItems;

    T buffer[sz];
  };


  template <typename T, size_t sz>
  Buffer<T, sz>::Buffer() : buffer()
  {
    flush();
  }
  

  template <typename T, size_t sz>
  Buffer<T, sz>::~Buffer()
  {
  }


  template <typename T, size_t sz>
  typename Buffer<T, sz>::Error Buffer<T, sz>::add(T value)
  {
    if(numItems == sz)
    {
      return FULL;
    }
    else
    {
      buffer[write] = value;

      ++numItems;
      ++write;
      if(write == sz) write = 0;

      return OK;
    }
  }


  template <typename T, size_t sz>
  typename Buffer<T, sz>::Error Buffer<T, sz>::get(T& value)
  {
    if(numItems == 0)
    {
      return EMPTY;
    }
    else
    {
      value = buffer[read];

      --numItems;
      ++read;
      if(read == sz) read = 0;

      return OK;
    }
  }


  template <typename T, size_t sz>
  bool  Buffer<T, sz>::isEmpty()
  {
    return (numItems == 0);
  }


  template <typename T, size_t sz>
  void  Buffer<T, sz>::flush()
  {
    read = 0;
    write = 0;
    numItems = 0;
  }
}
#endif // TEMPLATEBUFFER_H