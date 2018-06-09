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
  mainBank.AF.word = 0x00;
  mainBank.BC.word = 0x00;
  mainBank.DE.word = 0x00;
  mainBank.HL.word = 0x00;
  mainBank.SP.word = 0x00;
  mainBank.PC.word = 0x00;
  this->cycles = cycles;
}

cpu::~cpu() {   }

int32_t cpu::getCycles() {
  return cycles;
}

bool cpu::getCarry() {
  return mainBank.AF.bytes.low & FLAG_CARRY;
}

bool cpu::get2() {
  return (mainBank.AF.bytes.low & FLAG_2) >> 1;
}

bool cpu::getParity() {
  return (mainBank.AF.bytes.low & FLAG_PARITY) >> 2;
}

bool cpu::get4() {
  return (mainBank.AF.bytes.low & FLAG_4) >> 3;
}

bool cpu::getAux() {
  return (mainBank.AF.bytes.low & FLAG_AUX) >> 4;
}

bool cpu::get6()  {
  return (mainBank.AF.bytes.low & FLAG_6) >>  5;
}

bool cpu::getZero() {
  return (mainBank.AF.bytes.low & FLAG_ZERO) >> 6;
}

bool cpu::getSign() {
  return (mainBank.AF.bytes.low & FLAG_SIGN) >> 7;
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
      MOV(mainBank.BC.bytes.high, mainBank.BC.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV B, B" << endl;
      break;
    case 0x41:
      MOV(mainBank.BC.bytes.high, mainBank.BC.bytes.low);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV B, C" << endl;
      break;
    case 0x42:
      MOV(mainBank.BC.bytes.high, mainBank.DE.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV B, D" << endl;
      break;
    case 0x43:
      MOV(mainBank.BC.bytes.high, mainBank.DE.bytes.low);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV B, E" << endl;
      break;
    case 0x44:
      MOV(mainBank.BC.bytes.high, mainBank.HL.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV B, H" << endl;
      break;
    case 0x45:
      MOV(mainBank.BC.bytes.high, mainBank.HL.bytes.low);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV B, L" << endl;
      break;
    case 0x46:
      MOV(mainBank.BC.bytes.high, mem->readMemory(mainBank.HL.word));
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV B, (HL)" << endl;
      cycles -= 2;
      break;
    case 0x47:
      MOV(mainBank.BC.bytes.high, mainBank.AF.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV B, A" << endl;
      break;
    case 0x48:
      MOV(mainBank.BC.bytes.low, mainBank.BC.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV C, B" << endl;
      break;
    case 0x49:
      MOV(mainBank.BC.bytes.low, mainBank.BC.bytes.low);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV C, C" << endl;
      break;
    case 0x4A:
      MOV(mainBank.BC.bytes.low, mainBank.DE.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV C, D" << endl;
      break;
    case 0x4B:
      MOV(mainBank.BC.bytes.low, mainBank.DE.bytes.low);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV C, E" << endl;
    case 0x4C:
      MOV(mainBank.BC.bytes.low, mainBank.HL.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV C, H" << endl;
      break;
    case 0x4D:
      MOV(mainBank.BC.bytes.low, mainBank.HL.bytes.low);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV C, L" << endl;
      break;
    case 0x4E:
      MOV(mainBank.BC.bytes.low, mem->readMemory(mainBank.HL.word));
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV C, (HL)" << endl;
      cycles -= 2;
      break;
    case 0x4F:
      MOV(mainBank.BC.bytes.low, mainBank.AF.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV C, A" << endl;
      break;
    case 0x50:
      MOV(mainBank.DE.bytes.high, mainBank.BC.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV D, B" << endl;
      break;
    case 0x51:
      MOV(mainBank.DE.bytes.high, mainBank.BC.bytes.low);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV D, C" << endl;
      break;
    case 0x52:
      MOV(mainBank.DE.bytes.high, mainBank.DE.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV D, D" << endl;
      break;
    case 0x53:
      MOV(mainBank.DE.bytes.high, mainBank.DE.bytes.low);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV D, E" << endl;
      break;
    case 0x54:
      MOV(mainBank.DE.bytes.high, mainBank.HL.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV D, H" << endl;
      break;
    case 0x55:
      MOV(mainBank.DE.bytes.high, mainBank.HL.bytes.low);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV D, L" << endl;
      break;
    case 0x56:
      MOV(mainBank.DE.bytes.high, mem->readMemory(mainBank.HL.word));
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV D, (HL)" << endl;
      cycles -= 2;
      break;
    case 0x57:
      MOV(mainBank.DE.bytes.high, mainBank.AF.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV D, A" << endl;
      break;
    case 0x58:
      MOV(mainBank.DE.bytes.low, mainBank.BC.bytes.high);
      cout << "0x" << setfill('0') << setw(4) << hex << uppercase << mainBank.PC.word << ": " << "MOV E, B" << endl;
      break; 
    case 0x59:
      MOV(mainBank.DE.bytes.low, mainBank.BC.bytes.low);
      break;
    case 0x5A:
      MOV(mainBank.DE.bytes.low, mainBank.DE.bytes.high);
      break;
    case 0x5B:
      MOV(mainBank.DE.bytes.low, mainBank.DE.bytes.low);
      break;
    case 0x5C:
      MOV(mainBank.DE.bytes.low, mainBank.HL.bytes.high);
      break;
    case 0x5D:
      MOV(mainBank.DE.bytes.low, mainBank.HL.bytes.low);
      break;
    case 0x5E:
      MOV(mainBank.DE.bytes.low, mem->readMemory(mainBank.HL.word));
      cycles -= 2;
      break;
    case 0x5F:
      MOV(mainBank.DE.bytes.low, mainBank.AF.bytes.high);
      break;
    case 0x60:
      MOV(mainBank.HL.bytes.high, mainBank.BC.bytes.high);
      break;
    case 0x61:
      MOV(mainBank.HL.bytes.high, mainBank.BC.bytes.low);
      break;
    case 0x62:
      MOV(mainBank.HL.bytes.high, mainBank.DE.bytes.high);
      break;
    case 0x63: 
      MOV(mainBank.HL.bytes.high, mainBank.DE.bytes.low);
      break;
    case 0x64:
      MOV(mainBank.HL.bytes.high, mainBank.HL.bytes.high);
      break;
    case 0x65:
      MOV(mainBank.HL.bytes.high, mainBank.HL.bytes.low);
      break;
    case 0x66:
      MOV(mainBank.HL.bytes.high, mem->readMemory(mainBank.HL.word));
      cycles -= 2;
      break;
    case 0x67:
      MOV(mainBank.HL.bytes.high, mainBank.AF.bytes.high);
      break;
    case 0x68:
      MOV(mainBank.HL.bytes.low, mainBank.BC.bytes.high);
      break;
    case 0x69:
      MOV(mainBank.HL.bytes.low, mainBank.BC.bytes.low);
      break;
    case 0x6A:
      MOV(mainBank.HL.bytes.low, mainBank.DE.bytes.high);
      break;
    case 0x6B:
      MOV(mainBank.HL.bytes.low, mainBank.DE.bytes.low);
      break;
    case 0x6C:
      MOV(mainBank.HL.bytes.low, mainBank.HL.bytes.high);
      break;
    case 0x6D:
      MOV(mainBank.HL.bytes.low, mainBank.HL.bytes.low);
      break;
    case 0x6E:
      MOV(mainBank.HL.bytes.low, mem->readMemory(mainBank.HL.word));
      break;
    case 0x6F:
      MOV(mainBank.HL.bytes.low, mainBank.AF.bytes.high);
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

void cpu::MOV(uint8_t &dst, uint8_t src) {
  dst = src;

  mainBank.PC.word++;
  cycles -= 5;
}

bank_t cpu::getMainBank() {
  return mainBank;
}
