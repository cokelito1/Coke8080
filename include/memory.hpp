/*
This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

#include <iostream>
#include <vector>
#include <cstddef>

using namespace std;

template <class T>
class memory {
public:
  memory() {
    mem = new vector<T>();
  }

  memory(size_t size) {
    mem = new vector<T>(size);
  }

  ~memory() {
    delete mem;
  }

  void writeMemory(T data, size_t addr) {
    mem->insert((mem->begin() + addr), data);
  }

  T readMemory(size_t addr) {
    return mem->at(addr);
  }

private:
  vector<T> *mem;
};

#endif
