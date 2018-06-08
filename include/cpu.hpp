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
  void JPa16(); //0xF2

  void MOV(uint8_t &dst, uint8_t src);

  memory<uint8_t> *mem = nullptr;
};

#endif //_CPU_HPP_
