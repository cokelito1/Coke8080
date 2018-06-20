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

#ifndef _MACHINE_HPP_
#define _MACHINE_HPP_

/**
* @file     machine.hpp
* @author   Jorge Bravo (cokelito1)
* @date     20/6/2018
* @version  1.0
*
* @brief Connect all the components to the 8080
*
* This is the declaration for the 8080 emulator,
* the machine class it's an abstraction of a PCB
* that connect all the internal components of a PC
* like the ram and the cpu.
*/

#include <cstdint>
#include <iostream>
#include <string>

#include "memory.hpp"
#include "cpu.hpp"

/**
* @brief Serve as a frontend for the emulator implements I/O
*
* This class has the purpose of connect all the classes and
* implement the graphics and I/O
*
* @author Jorge Bravo
*/
class machine {
public:
  /**
  * @brief Constructor of machine object
  */
  machine();

  /**
  * @brief Constructor of machine object
  *
  * @param  logging is a boolean that enables/disables logging to a file
  * @param  logFile is a string to the path of the log file
  */
  machine(bool logging, std::string logFile);

  /**
  * @brief Destructor of the machine object
  */
  ~machine();

  /**
  * @brief Loads a binary file to the emulator memory
  *
  * @param filePath is a string to the path of the rom
  * @return false on fail and true on success
  */
  bool loadRom(std::string filePath);

  /**
  * @brief Main loop of the emulator
  *
  * @return void
  */
  void startEmu();

  /**
  * @brief Debug function to write all the registers to a file
  *
  * @param filePath string to the path of the logging file, normally logFile var
  * @return void
  */
  void writeRegistersToFile(std::string filePath);

  /**
  * @brief Set a new value to the logFile variable
  *
  * @param logFile string of the new value for logFile
  * @return void
  */
  void setLogFile(std::string logFile);
private:
  cpu *chip;            ///<cpu object, main part of the emulator
  memory<uint8_t> *mem; ///<memory object, main memory for the cpu

  bool logging;         ///<boolean value that enables logging to a file

  std::string logFile;  ///<string to the parg of the log file
};

#endif
