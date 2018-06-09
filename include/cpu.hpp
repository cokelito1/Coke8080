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

#ifndef _CPU_HPP_
#define _CPU_HPP_

#include <cstdint>

#include "memory.hpp"

typedef union {
  struct {
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
      uint8_t low;
      uint8_t high;
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
      uint8_t high;
      uint8_t low;
    #endif
  }bytes;

  uint16_t word;
} registers_t;

enum FLAGS {
  FLAG_CARRY  = 0x01,
  FLAG_2      = 0x02,
  FLAG_PARITY = 0x04,
  FLAG_4      = 0x08,
  FLAG_AUX    = 0x10,
  FLAG_6      = 0x20,
  FLAG_ZERO   = 0x40,
  FLAG_SIGN   = 0x80,
};

typedef struct {
  registers_t AF;
  registers_t BC;
  registers_t DE;
  registers_t HL;
  registers_t SP;
  registers_t PC;
} bank_t;

class cpu {
public:
  cpu();
  cpu(int32_t cycles);
  ~cpu();

  int32_t getCycles();

  void cycle();
  void setMemInstance(memory<uint8_t> *instance);

  bank_t getMainBank();
private:
  int32_t cycles;
  bank_t mainBank;

  void NOP();   //0x00, 0x10, 0x20, 0x30
  void HLT();
  void JPa16(); //0xF2
  void MOVToMemory(uint16_t addr, uint8_t src);

  void MOV(uint8_t &dst, uint8_t src);

  bool getCarry();
  bool get2();
  bool getParity();
  bool get4();
  bool getAux();
  bool get6();
  bool getZero();
  bool getSign();

  memory<uint8_t> *mem = nullptr;
  memory<uint8_t> stack;
};

#endif //_CPU_HPP_
