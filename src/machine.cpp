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

#include <fstream>
#include <iomanip>

#include "machine.hpp"

machine::machine() {
  chip = new cpu(2000000);
  mem = new memory<uint8_t>(0x10000);
  logging = false;
  chip->setMemInstance(mem);
}

machine::machine(bool logging, std::string logFile) {
  chip = new cpu(2000000);
  mem = new memory<uint8_t>(0x10000);
  this->logging = logging;
  this->logFile = logFile;
  chip->setMemInstance(mem);
}

machine::~machine() {
  delete chip;
  delete mem;
}

bool machine::loadRom(std::string filePath) {
  ifstream rom(filePath, ios::in|ios::binary|ios::ate);
  if(rom.is_open()) {
    ifstream::pos_type size = rom.tellg();
    #pragma warning(disable:4244)
    uint8_t *romData = new uint8_t[size];
    #pragma warning(default:4244)
    rom.seekg(0, ios::beg);
    rom.read((char *) romData, size);
    rom.close();

    if(size > 0xFFFF) {
      return false;
    } else {
      for(int i = 0; i < size; i++) {
        mem->writeMemory(romData[i], i);
      }
    }

    delete[] romData;
  } else {
    return false;
  }
  return true;
}

void machine::startEmu() {
  while(chip->getCycles() > 0){
    chip->cycle();
    if(logging) {
      writeRegistersToFile(logFile);
    }
  }
}

void machine::setLogFile(std::string logFile) {
  this->logFile = logFile;
}

void machine::writeRegistersToFile(std::string filePath) {
  #pragma warning(disable:4333)
  bank_t currentRegisters = chip->getMainBank();

  ofstream registerLog;
  registerLog.open(filePath, ios::out | ios::app);

  registerLog << "PC: 0x" <<  currentRegisters.PC.word << endl;
  registerLog << "SP: 0x" <<  currentRegisters.SP.word << endl;

  registerLog << "A: 0x" <<  hex << unsigned(currentRegisters.AF.bytes.high) << ", ";
  registerLog << "F: 0x" <<  hex << unsigned(currentRegisters.AF.bytes.low) << ", ";
  registerLog << "AF: 0x" <<  hex << currentRegisters.AF.word << endl;

  registerLog << "B: 0x" <<  hex << unsigned(currentRegisters.BC.bytes.high) << ", ";
  registerLog << "C: 0x" <<  hex << unsigned(currentRegisters.BC.bytes.low) << ", ";
  registerLog << "BC: 0x" <<  hex << currentRegisters.BC.word << endl;

  registerLog << "D: 0x" <<  hex << unsigned(currentRegisters.DE.bytes.high) << ", ";
  registerLog << "E: 0x" <<  hex << unsigned(currentRegisters.DE.bytes.low) << ", ";
  registerLog << "DE: 0x" <<  hex << currentRegisters.DE.word << endl;

  registerLog << "H: 0x" <<  hex << unsigned(currentRegisters.HL.bytes.high) << ", ";
  registerLog << "L: 0x" <<  hex << unsigned(currentRegisters.HL.bytes.low) << ", ";
  registerLog << "HL: 0x" <<  hex << currentRegisters.HL.word << endl << endl;

  registerLog.close();
  #pragma warning(default:4333)
 }
