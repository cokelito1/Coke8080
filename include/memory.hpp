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

/**
* @file     memory.hpp
* @author   Jorge Bravo (cokelito1)
* @date     20/6/2018
* @version  1.0
*
* @brief Declares a template for memory access to the cpu
*
* This is the declaration for the memory class,
* the function of this class is to get an abstract
* access to different memorys of the emulator
*/

#include <iostream>
#include <vector>
#include <cstddef>

using namespace std;

/**
* @brief this template purpose is implement a clean interface for memory
*
* This class provides a clean form to Read & Write the memory
* is implemented as a template for use with varius data types
*
* @author Jorge Bravo
*/
template <class T>
class memory {
public:
  /**
  * @brief Constructor for the memory class
  */
  memory() {
    mem = new vector<T>();
  }

  /**
  * @brief Constructor for the memory class
  *
  * @param size is a variable to start a vector with a default size
  */
  memory(size_t size) {
    mem = new vector<T>(size);
  }

  /**
  * @brief Destructor for the memory classs
  */
  ~memory() {
    delete mem;
  }

  /**
  * @brief write a value to an address of the memory
  *
  * @param data is the data you want to write to the address
  * @param addr is the address where you want to write the data
  * @return void
  */
  void writeMemory(T data, size_t addr) {
    mem->insert((mem->begin() + addr), data);
  }

  /**
  * @brief read a value from the memory at a specific address
  *
  * @param addr is a size_t and the address of the data you want to read
  * @return T value from the memory at address addr
  */
  T readMemory(size_t addr) {
    return mem->at(addr);
  }

private:
  vector<T> *mem; ///< Vector of T that saves all the values
};

#endif
