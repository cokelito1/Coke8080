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

#include <iostream>
#include <iomanip>

#include "cpu.hpp"

using namespace std;

cpu::cpu() {
  mainBank.AF.word = 0x00;
  mainBank.BC.word = 0x00;
  mainBank.DE.word = 0x00;
  mainBank.HL.word = 0x00;
  mainBank.SP.word = 0x00;
  mainBank.PC.word = 0x00;

  cycles = 0;
}

cpu::cpu(int32_t cycles) {
  this->cycles = cycles;
}

cpu::~cpu() { }

int32_t cpu::getCycles() {
  return cycles;
}

void cpu::cycle() {
  if(mem == nullptr) {
      cout << "Instancia de memoria en cpu no inicializada" << endl;
      exit(-1);
  }

  uint8_t opcode = mem->readMemory(mainBank.PC.word);

  switch(opcode) {
    case 0x00:
      NOP();
      break;
    case 0x10:
      NOP();
      break;
    case 0x20:
      NOP();
      break;
    case 0x30:
      NOP();
      break;
    case 0x40:
      MOVBB();
      break;
    case 0xF2:
      JPa16();
      break;

    default:
      cout << "default" << endl;
  }
}

void cpu::setMemInstance(memory<uint8_t> *instance) {
  mem = instance;
}

void cpu::NOP() {
  cycles -= 4;
  mainBank.PC.word++;

  cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "NOP" << endl;
}

void cpu::MOVBB() {
  cycles -= 5;
  mainBank.BC.bytes.high = mainBank.BC.bytes.high;
  mainBank.PC.word++;

  cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV B, B" << endl;
}

void cpu::JPa16() {
  cycles -= 10;
  uint16_t addrJump = 0x00;

  mainBank.PC.word++;
  addrJump = mem->readMemory(mainBank.PC.word);
  mainBank.PC.word++;
  addrJump |= (mem->readMemory(mainBank.PC.word) << 8);
  mainBank.PC.word++;

  cout << "0x" << setfill('0') << setw(4) << hex << uppercase << (mainBank.PC.word - 0x03) << ": " << "JP 0x" << setfill('0') << setw(4) << addrJump << endl;

  mainBank.PC.word = addrJump;
}
