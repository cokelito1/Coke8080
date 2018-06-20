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
    uint8_t *romData = new uint8_t[size];
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
  bank_t currentRegisters = chip->getMainBank();

  ofstream registerLog;
  registerLog.open(filePath, ios::out | ios::app);

  registerLog << "PC: 0x" <<  currentRegisters.PC.word << endl;
  registerLog << "SP: 0x" <<  currentRegisters.SP.word << endl;

  registerLog << "A: 0x" <<  hex << (currentRegisters.AF.bytes.high >> 8) << ", ";
  registerLog << "F: 0x" <<  hex << (currentRegisters.AF.word & 0x00FF) << ", ";
  registerLog << "AF: 0x" <<  hex << currentRegisters.AF.word << endl;

  registerLog << "B: 0x" <<  hex << (currentRegisters.BC.bytes.high >> 8) << ", ";
  registerLog << "C: 0x" <<  hex << (currentRegisters.BC.word & 0x00FF) << ", ";
  registerLog << "BC: 0x" <<  hex << currentRegisters.BC.word << endl;

  registerLog << "D: 0x" <<  hex << (currentRegisters.DE.bytes.high >> 8) << ", ";
  registerLog << "E: 0x" <<  hex << (currentRegisters.DE.word & 0x00FF) << ", ";
  registerLog << "DE: 0x" <<  hex << currentRegisters.DE.word << endl;

  registerLog << "H: 0x" <<  hex << (currentRegisters.HL.bytes.high >> 8) << ", ";
  registerLog << "L: 0x" <<  hex << (currentRegisters.HL.word & 0x00FF) << ", ";
  registerLog << "HL: 0x" <<  hex << currentRegisters.HL.word << endl << endl;

  registerLog.close();
 }
