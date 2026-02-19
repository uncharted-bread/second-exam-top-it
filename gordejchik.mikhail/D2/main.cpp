#include <iostream>
#include <cstring>

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
      char ch = '\0';
      while (in >> ch) {
        if (!append(ch, 1)) {
          return 2;
        }
      }
      if (!in.eof()) {
        return 1;
      }
      return 0;
    }

    void printPairs(std::ostream& out) const
    {
      if (size == 0) {
        out << '\n';
        return;
      }
      size_t i = 0;
      while (i < size) {
        const char current = data[i];
        size_t count = 0;
        while (i < size && data[i] == current) {
          ++count;
          ++i;
        }
        out << count << ' ' << current << '\n';
      }
    }

    void printPairsReversed(std::ostream& out) const
    {
      if (size == 0) {
        out << '\n';
        return;
      }
      size_t i = size;
      while (i > 0) {
        const char current = data[i - 1];
        size_t count = 0;
        while (i > 0 && data[i - 1] == current) {
          ++count;
          --i;
        }
        out << count << ' ' << current << '\n';
      }
    }
  };
}

int main(int argc, char* argv[])
{
  if (argc > 2) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  const bool reverse = (argc == 2) && (std::strcmp(argv[1], "reverse") == 0);
  if (argc == 2 && !reverse) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  gordejchik::CharSequence seq;
  const int result = seq.read(std::cin);
  if (reverse) {
    seq.printPairsReversed(std::cout);
  } else {
    seq.printPairs(std::cout);
  }
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
