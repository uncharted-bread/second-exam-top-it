#include <iostream>

namespace gordejchik
{
  struct CharSequence
  {
    char* data;
    size_t size;

    CharSequence():
      data(nullptr),
      size(0)
    {}

    void free()
    {
      delete[] data;
      data = nullptr;
      size = 0;
    }

    bool append(char ch, size_t count)
    {
      if (count == 0) {
        return true;
      }
      char* newData = nullptr;
      try {
        newData = new char[size + count];
      } catch (const std::bad_alloc&) {
        return false;
      }
      for (size_t i = 0; i < size; ++i) {
        newData[i] = data[i];
      }
      for (size_t i = 0; i < count; ++i) {
        newData[size + i] = ch;
      }
      delete[] data;
      data = newData;
      size += count;
      return true;
    }

    int read(std::istream& in)
    {
      size_t count = 0;
      char ch = '\0';
      while (in >> count) {
        if (!(in >> ch)) {
          return 1;
        }
        if (!append(ch, count)) {
          return 2;
        }
      }
      if (!in.eof()) {
        return 1;
      }
      return 0;
    }

    void printReversed(std::ostream& out) const
    {
      for (size_t i = size; i > 0; --i) {
        out << data[i - 1];
      }
      out << '\n';
    }
  };
}

int main()
{
  gordejchik::CharSequence seq;
  const int result = seq.read(std::cin);
  seq.printReversed(std::cout);
  seq.free();
  if (result == 1) {
    std::cerr << "Invalid input\n";
    return 1;
  }
  if (result == 2) {
    std::cerr << "Memory allocation failed\n";
    return 2;
  }
  return 0;
}
