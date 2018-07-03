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
#include <functional>
#include <map>
#include <queue>

#include "memory.hpp"

/**
* @file     cpu.hpp
* @author   Jorge Bravo (cokelito1)
* @date     20/6/2018
* @version  1.0
*
* @brief Implements the 8080 to use on machine
*
* This archive purpose is to declare all the
* cpu data types and the cpu class itself
*/

/**
* @brief union to access low and high bytes of a register
*
* @author Jorge Bravo
*/
typedef union {
  struct {
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
      uint8_t low;  ///< Low byte of the register
      uint8_t high; ///< High byte of the register
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
      uint8_t high; ///< High byte of the register
      uint8_t low;  ///< Low byte of the register
    #endif
  }bytes;

  uint16_t word;  ///< Register 16 bits value
} registers_t;

/**
* @brief enum taht declares the mask to access a flag
*
* @author Jorge Bravo
*/
enum FLAGS {
  FLAG_CARRY  = 0x01, ///<  Mask for Carry flag
  FLAG_2      = 0x02, ///<  Mask for Second flag
  FLAG_PARITY = 0x04, ///<  Mask for Parity flag
  FLAG_4      = 0x08, ///<  Mask for 4 flag
  FLAG_AUX    = 0x10, ///<  Mask for Auxiliary flag
  FLAG_6      = 0x20, ///<  Mask for 6 flag
  FLAG_ZERO   = 0x40, ///<  Mask for Zero flag
  FLAG_SIGN   = 0x80, ///<  Mask for Sign Flag
};

/**
* @brief struct that represents a bank of register for the cpu
*
* @author Jorge Bravo
*/
typedef struct {
  registers_t AF; ///<  Accumulator and Flags register
  registers_t BC; ///<  BC register
  registers_t DE; ///<  DE register
  registers_t HL; ///<  HL register
  registers_t SP; ///<  Stack Pointer register
  registers_t PC; ///<  Program Counter register
} bank_t;

/**
* @brief the purpose of cpu class is to emulate the opcodes of the 8080
*
* This class is the main class of all the project, it's
* importance is to emulate all the 8080 opcodes and,
* set a clean interface to interact.
*
* @author Jorge Bravo
*/
class cpu {
public:
  typedef void (cpu::*Opcodefunc)();

  /**
  * @brief cpu constructor
  *
  * @author Jorge Bravo
  */
  cpu();

  /**
  * @brief cpu constructor
  *
  * @param cycles is a int32_t var to store the cycles
  * @author Jorge Bravo
  */
  cpu(int32_t cycles);

  /**
  * @brief cpu destructor
  *
  * @author Jorge Bravo
  */
  ~cpu();

  /**
  * @brief get cycles variable from the object
  *
  * @return int32_t cycles
  * @author Jorge Bravo
  */
  int32_t getCycles();

  /**
  * @brief cycle one instruction in the cpu
  *
  * @return void
  * @author Jorge Bravo
  */
  void cycle();

  /**
  * @brief give an instance of memory object to the cpu
  *
  * @param instance is a pointer to the memory object
  * @return void
  * @author Jorge Bravo
  */
  void setMemInstance(memory<uint8_t> *instance);

  /**
  * @brief set a queue instance for mmio
  *
  * @param address of the instance
  * @param Queue pointer to mmio
  * @return void
  * @author Jorge Bravo
  */
  void setMMIOInstance(uint16_t address, std::queue<uint8_t> *mmio);

  /**
  * @brief get mainBank, main purpose to use writeRegistersToFile on machine
  *
  * @return bank_t
  * @author Jorge Bravo
  */
  bank_t getMainBank();
private:
  int32_t cycles;
  bank_t mainBank;

  void insertOpcode(Opcodefunc function, uint16_t opcodeValue);

  void NOP();   //0x00, 0x10, 0x20, 0x30
  void HLT();
  void JPa16(); //0xF2
  void LXI(uint16_t &reg);
  void STAX(uint16_t addr);
  void INX(uint16_t &reg);
  void MVI(uint8_t &reg);
  void LDAX(uint16_t addr);
  void DCX(uint16_t &reg);
  void RET();
  void XCHG();
  void RLC();
  void SHLD();

  //MOVToMemory Zone
  void MOVToMemory(uint16_t addr, uint8_t src);
  void MOVToMemoryB();
  void MOVToMemoryC();
  void MOVToMemoryD();
  void MOVToMemoryE();
  void MOVToMemoryH();
  void MOVToMemoryL();
  void MOVToMemoryA();

  //LXI Zone
  void LXIBC();
  void LXIDE();
  void LXIHL();
  void LXISP();

  //Stax Zone
  void STAXBC();
  void STAXDE();

  //INX Zone
  void INXBC();
  void INXDE();

  //MVI Zone
  void MVIB();
  void MVIC();
  void MVID();
  void MVIE();

  //LDAX Zone
  void LDAXBC();
  void LDAXDE();

  //DCX Zone
  void DCXBC();
  void DCXDE();

  //R Zone
  void RCond(uint8_t flag);
  void RNZ();
  void RZ();
  void RNC();
  void RC();
  void RPO();
  void RPE();
  void RP();
  void RM();

  //MOV Zone
  void MOV(uint8_t &dst, uint8_t src);
  void MOVBB();
  void MOVBC();
  void MOVBD();
  void MOVBE();
  void MOVBH();
  void MOVBL();
  void MOVBHL();
  void MOVBA();
  void MOVCB();
  void MOVCC();
  void MOVCD();
  void MOVCE();
  void MOVCH();
  void MOVCL();
  void MOVCHL();
  void MOVCA();
  void MOVDB();
  void MOVDC();
  void MOVDD();
  void MOVDE();
  void MOVDH();
  void MOVDL();
  void MOVDHL();
  void MOVDA();
  void MOVEB();
  void MOVEC();
  void MOVED();
  void MOVEE();
  void MOVEH();
  void MOVEL();
  void MOVEHL();
  void MOVEA();
  void MOVHB();
  void MOVHC();
  void MOVHD();
  void MOVHE();
  void MOVHH();
  void MOVHL();
  void MOVHHL();
  void MOVHA();
  void MOVLB();
  void MOVLC();
  void MOVLD();
  void MOVLE();
  void MOVLH();
  void MOVLL();
  void MOVLHL();
  void MOVLA();
  void MOVAB();
  void MOVAC();
  void MOVAD();
  void MOVAE();
  void MOVAH();
  void MOVAL();
  void MOVAHL();
  void MOVAA();

  //DAD Zone
  void DAD(const uint16_t &reg);
  void DADB();
  void DADD();
  void DADH();
  void DADSP();

  Opcodefunc op[0x100];

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

  std::map<uint16_t, std::queue<uint8_t> *> IO;
};

#endif //_CPU_HPP_
