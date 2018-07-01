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

  for(int i=0; i<0x100; i++) {
    insertOpcode(&cpu::HLT, i);
  }

  insertOpcode(&cpu::NOP, 0x00);
  insertOpcode(&cpu::LXIBC, 0x01);
  insertOpcode(&cpu::STAXBC, 0x02);
  insertOpcode(&cpu::INXBC, 0x03);
  //0x04-0x05
  insertOpcode(&cpu::MVIB, 0x06);
  //0x07
  insertOpcode(&cpu::NOP, 0x08);
  //0x09
  insertOpcode(&cpu::LDAXBC, 0x0A);
  insertOpcode(&cpu::DCXBC, 0x0B);
  //0x0C-0x0D
  insertOpcode(&cpu::MVIC, 0x0E);
  //0x0F
  insertOpcode(&cpu::NOP, 0x10);
  insertOpcode(&cpu::LXIDE, 0x11);
  insertOpcode(&cpu::STAXDE, 0x12);
  insertOpcode(&cpu::INXDE, 0x13);
  //0x14-0x15
  insertOpcode(&cpu::MVID, 0x16);
  //0x17
  insertOpcode(&cpu::NOP, 0x18);
  //0x19
  insertOpcode(&cpu::LDAXDE, 0x1A);
  insertOpcode(&cpu::DCXDE, 0x1B);
  //0x1C-0x1D
  insertOpcode(&cpu::MVIE, 0x1E);
  //0x1F
  insertOpcode(&cpu::NOP, 0x20);
  insertOpcode(&cpu::LXIHL, 0x21);
  //0x22
  insertOpcode(&cpu::SHLD, 0x23);
  //0x24-0x2F
  insertOpcode(&cpu::NOP, 0x30);
  insertOpcode(&cpu::LXISP, 0x31);
  //0x32-0x3F
  insertOpcode(&cpu::MOVBB, 0x40);
  insertOpcode(&cpu::MOVBC, 0x41);
  insertOpcode(&cpu::MOVBD, 0x42);
  insertOpcode(&cpu::MOVBE, 0x43);
  insertOpcode(&cpu::MOVBH, 0x44);
  insertOpcode(&cpu::MOVBL, 0x45);
  insertOpcode(&cpu::MOVBHL, 0x46);
  insertOpcode(&cpu::MOVBA, 0x47);
  insertOpcode(&cpu::MOVCB, 0x48);
  insertOpcode(&cpu::MOVCC, 0x49);
  insertOpcode(&cpu::MOVCD, 0x4A);
  insertOpcode(&cpu::MOVCE, 0x4B);
  insertOpcode(&cpu::MOVCH, 0x4C);
  insertOpcode(&cpu::MOVCL, 0x4D);
  insertOpcode(&cpu::MOVCHL, 0x4E);
  insertOpcode(&cpu::MOVCA, 0x4F);
  insertOpcode(&cpu::MOVDB, 0x50);
  insertOpcode(&cpu::MOVDC, 0x51);
  insertOpcode(&cpu::MOVDD, 0x52);
  insertOpcode(&cpu::MOVDE, 0x53);
  insertOpcode(&cpu::MOVDH, 0x54);
  insertOpcode(&cpu::MOVDL, 0x55);
  insertOpcode(&cpu::MOVDHL, 0x56);
  insertOpcode(&cpu::MOVDA, 0x57);
  insertOpcode(&cpu::MOVEB, 0x58);
  insertOpcode(&cpu::MOVEC, 0x59);
  insertOpcode(&cpu::MOVED, 0x5A);
  insertOpcode(&cpu::MOVEE, 0x5B);
  insertOpcode(&cpu::MOVEH, 0x5C);
  insertOpcode(&cpu::MOVEL, 0x5D);
  insertOpcode(&cpu::MOVEHL, 0x5E);
  insertOpcode(&cpu::MOVEA, 0x5F);
  insertOpcode(&cpu::MOVHB, 0x60);
  insertOpcode(&cpu::MOVHC, 0x61);
  insertOpcode(&cpu::MOVHD, 0x62);
  insertOpcode(&cpu::MOVHE, 0x63);
  insertOpcode(&cpu::MOVHH, 0x64);
  insertOpcode(&cpu::MOVHL, 0x65);
  insertOpcode(&cpu::MOVHHL, 0x66);
  insertOpcode(&cpu::MOVHA, 0x67);
  insertOpcode(&cpu::MOVLB, 0x68);
  insertOpcode(&cpu::MOVLC, 0x69);
  insertOpcode(&cpu::MOVLD, 0x6A);
  insertOpcode(&cpu::MOVLE, 0x6B);
  insertOpcode(&cpu::MOVLH, 0x6C);
  insertOpcode(&cpu::MOVLL, 0x6D);
  insertOpcode(&cpu::MOVLHL, 0x6E);
  insertOpcode(&cpu::MOVLA, 0x6F);
  insertOpcode(&cpu::MOVToMemoryB, 0x70);
  insertOpcode(&cpu::MOVToMemoryC, 0x71);
  insertOpcode(&cpu::MOVToMemoryD, 0x72);
  insertOpcode(&cpu::MOVToMemoryE, 0x73);
  insertOpcode(&cpu::MOVToMemoryH, 0x74);
  insertOpcode(&cpu::MOVToMemoryL, 0x75);
  insertOpcode(&cpu::HLT, 0x76);
  insertOpcode(&cpu::MOVToMemoryA, 0x77);
  insertOpcode(&cpu::MOVAB, 0x78);
  insertOpcode(&cpu::MOVAC, 0x79);
  insertOpcode(&cpu::MOVAD, 0x7A);
  insertOpcode(&cpu::MOVAE, 0x7B);
  insertOpcode(&cpu::MOVAH, 0x7C);
  insertOpcode(&cpu::MOVAL, 0x7D);
  insertOpcode(&cpu::MOVAHL, 0x7E);
  insertOpcode(&cpu::MOVAA, 0x7F);
  //0x80-0xC8
  insertOpcode(&cpu::RNZ, 0xC0);
  //0xC1-0xC7
  insertOpcode(&cpu::RZ, 0xC8);
  insertOpcode(&cpu::RET, 0xC9);
  //0xCA-0xCF
  insertOpcode(&cpu::RNZ, 0xD0);
  //0xD1-0xD7
  insertOpcode(&cpu::RC, 0xD8);
  //0xD9-0xDF
  insertOpcode(&cpu::RPO, 0xE0);
  //0xE1-0xE7
  insertOpcode(&cpu::RPE, 0xE8);
  //0xE9-0xEA
  insertOpcode(&cpu::XCHG, 0xEB);
  //0xEC-0xEF
  insertOpcode(&cpu::RP, 0xF0);
  //0xF1
  insertOpcode(&cpu::JPa16, 0xF2);
  //0xF3-0xF7
  insertOpcode(&cpu::RM, 0xF8);
  //0xF9-0xFF

  cycles = 0;
}

cpu::cpu(int32_t cycles) : cpu(){
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
  (this->*op[opcode])();
}

void cpu::insertOpcode(Opcodefunc function, uint16_t opcodeValue) {
  op[opcodeValue] = function;
}

void cpu::setMemInstance(memory<uint8_t> *instance) {
  mem = instance;
}

void cpu::NOP() {
  cycles -= 4;
  mainBank.PC.word++;
}

void cpu::JPa16() {
  cycles -= 10;
  uint16_t addrJump = 0x00;

  mainBank.PC.word++;
  addrJump = mem->readMemory(mainBank.PC.word);
  mainBank.PC.word++;
  addrJump |= (mem->readMemory(mainBank.PC.word) << 8);
  mainBank.PC.word++;

//  cout << "0x" << setfill('0') << setw(4) << hex << uppercase << (mainBank.PC.word - 0x03) << ": " << "JP 0x" << setfill('0') << setw(4) << addrJump << endl;

  mainBank.PC.word = addrJump;
}

//MOV Zone
void cpu::MOV(uint8_t &dst, uint8_t src) {
  dst = src;

  mainBank.PC.word++;
  cycles -= 5;
}

void cpu::MOVBB() {
  MOV(mainBank.BC.bytes.high, mainBank.BC.bytes.high);
}

void cpu::MOVBC() {
  MOV(mainBank.BC.bytes.high, mainBank.BC.bytes.low);
}

void cpu::MOVBD() {
  MOV(mainBank.BC.bytes.high, mainBank.DE.bytes.high);
}

void cpu::MOVBE() {
  MOV(mainBank.BC.bytes.high, mainBank.DE.bytes.low);
}

void cpu::MOVBH() {
  MOV(mainBank.BC.bytes.high, mainBank.HL.bytes.high);
}

void cpu::MOVBL() {
  MOV(mainBank.BC.bytes.high, mainBank.HL.bytes.low);
}

void cpu::MOVBHL() {
  MOV(mainBank.BC.bytes.high, mem->readMemory(mainBank.HL.word));
  cycles -= 2;
}

void cpu::MOVBA() {
  MOV(mainBank.BC.bytes.high, mainBank.AF.bytes.high);
}

void cpu::MOVCB() {
  MOV(mainBank.BC.bytes.low, mainBank.BC.bytes.high);
}

void cpu::MOVCC() {
  MOV(mainBank.BC.bytes.low, mainBank.BC.bytes.low);
}

void cpu::MOVCD() {
  MOV(mainBank.BC.bytes.low, mainBank.DE.bytes.high);
}

void cpu::MOVCE() {
  MOV(mainBank.BC.bytes.low, mainBank.DE.bytes.low);
}

void cpu::MOVCH() {
  MOV(mainBank.BC.bytes.low, mainBank.HL.bytes.high);
}

void cpu::MOVCL() {
  MOV(mainBank.BC.bytes.low, mainBank.HL.bytes.low);
}

void cpu::MOVCHL() {
  MOV(mainBank.BC.bytes.low, mem->readMemory(mainBank.HL.word));
  cycles -= 2;
}

void cpu::MOVCA() {
  MOV(mainBank.BC.bytes.low, mainBank.AF.bytes.high);
}

void cpu::MOVDB() {
  MOV(mainBank.DE.bytes.high, mainBank.BC.bytes.high);
}

void cpu::MOVDC() {
  MOV(mainBank.DE.bytes.high, mainBank.BC.bytes.low);
}

void cpu::MOVDD() {
  MOV(mainBank.DE.bytes.high, mainBank.DE.bytes.high);
}

void cpu::MOVDE() {
  MOV(mainBank.DE.bytes.high, mainBank.DE.bytes.low);
}

void cpu::MOVDH() {
  MOV(mainBank.DE.bytes.high, mainBank.HL.bytes.high);
}

void cpu::MOVDL() {
  MOV(mainBank.DE.bytes.high, mainBank.HL.bytes.low);
}

void cpu::MOVDHL() {
  MOV(mainBank.DE.bytes.high, mem->readMemory(mainBank.HL.word));
  cycles -= 2;
}

void cpu::MOVDA() {
  MOV(mainBank.DE.bytes.high, mainBank.AF.bytes.high);
}

void cpu::MOVEB() {
  MOV(mainBank.DE.bytes.low, mainBank.BC.bytes.high);
}

void cpu::MOVEC() {
  MOV(mainBank.DE.bytes.low, mainBank.BC.bytes.low);
}

void cpu::MOVED() {
  MOV(mainBank.DE.bytes.low, mainBank.DE.bytes.high);
}

void cpu::MOVEE() {
  MOV(mainBank.DE.bytes.low, mainBank.DE.bytes.low);
}

void cpu::MOVEH() {
  MOV(mainBank.DE.bytes.low, mainBank.HL.bytes.high);
}

void cpu::MOVEL() {
  MOV(mainBank.DE.bytes.low, mainBank.HL.bytes.low);
}

void cpu::MOVEHL() {
  MOV(mainBank.DE.bytes.low, mem->readMemory(mainBank.HL.word));
  cycles -= 2;
}

void cpu::MOVEA() {
  MOV(mainBank.DE.bytes.low, mainBank.AF.bytes.high);
}

void cpu::MOVHB() {
  MOV(mainBank.HL.bytes.high, mainBank.BC.bytes.high);
}

void cpu::MOVHC() {
  MOV(mainBank.HL.bytes.high, mainBank.BC.bytes.low);
}

void cpu::MOVHD() {
  MOV(mainBank.HL.bytes.high, mainBank.DE.bytes.high);
}

void cpu::MOVHE() {
  MOV(mainBank.HL.bytes.high, mainBank.DE.bytes.low);
}

void cpu::MOVHH() {
  MOV(mainBank.HL.bytes.high, mainBank.HL.bytes.high);
}

void cpu::MOVHL() {
  MOV(mainBank.HL.bytes.high, mainBank.HL.bytes.low);
}

void cpu::MOVHHL() {
  MOV(mainBank.HL.bytes.high, mem->readMemory(mainBank.HL.word));
  cycles -= 2;
}

void cpu::MOVHA() {
  MOV(mainBank.HL.bytes.high, mainBank.AF.bytes.high);
}

void cpu::MOVLB() {
  MOV(mainBank.HL.bytes.low, mainBank.BC.bytes.high);
}

void cpu::MOVLC() {
  MOV(mainBank.HL.bytes.low, mainBank.BC.bytes.low);
}

void cpu::MOVLD() {
  MOV(mainBank.HL.bytes.low, mainBank.DE.bytes.high);
}

void cpu::MOVLE() {
  MOV(mainBank.HL.bytes.low, mainBank.DE.bytes.low);
}

void cpu::MOVLH() {
  MOV(mainBank.HL.bytes.low, mainBank.HL.bytes.high);
}

void cpu::MOVLL() {
    MOV(mainBank.HL.bytes.low, mainBank.HL.bytes.low);
}

void cpu::MOVLHL() {
  MOV(mainBank.HL.bytes.low, mem->readMemory(mainBank.HL.word));
  cycles -= 2;
}

void cpu::MOVLA() {
  MOV(mainBank.HL.bytes.low, mainBank.AF.bytes.high);
}

void cpu::MOVAB() {
  MOV(mainBank.AF.bytes.high, mainBank.BC.bytes.high);
}

void cpu::MOVAC() {
  MOV(mainBank.AF.bytes.high, mainBank.BC.bytes.high);
}

void cpu::MOVAD() {
  MOV(mainBank.AF.bytes.high, mainBank.DE.bytes.high);
}

void cpu::MOVAE() {
  MOV(mainBank.AF.bytes.high, mainBank.DE.bytes.low);
}

void cpu::MOVAH() {
  MOV(mainBank.AF.bytes.high, mainBank.HL.bytes.high);
}

void cpu::MOVAL() {
  MOV(mainBank.AF.bytes.high, mainBank.HL.bytes.low);
}

void cpu::MOVAHL() {
  MOV(mainBank.AF.bytes.high, mem->readMemory(mainBank.HL.word));
  cycles -= 2;
}

void cpu::MOVAA() {
  MOV(mainBank.AF.bytes.high, mainBank.AF.bytes.high);
}

//MOVToMemory Zone
void cpu::MOVToMemory(uint16_t addr, uint8_t src) {
  mem->writeMemory(src, addr);

  mainBank.PC.word++;
  cycles -= 7;
}

void cpu::MOVToMemoryB() {
  MOVToMemory(mainBank.HL.word, mainBank.BC.bytes.high);
}

void cpu::MOVToMemoryC() {
  MOVToMemory(mainBank.HL.word, mainBank.BC.bytes.low);
}

void cpu::MOVToMemoryD() {
  MOVToMemory(mainBank.HL.word, mainBank.DE.bytes.high);
}

void cpu::MOVToMemoryE() {
  MOVToMemory(mainBank.HL.word, mainBank.DE.bytes.low);
}

void cpu::MOVToMemoryH() {
  MOVToMemory(mainBank.HL.word, mainBank.HL.bytes.high);
}

void cpu::MOVToMemoryL() {
  MOVToMemory(mainBank.HL.word, mainBank.HL.bytes.low);
}

void cpu::MOVToMemoryA() {
  MOVToMemory(mainBank.HL.word, mainBank.AF.bytes.high);
}

void cpu::HLT() {
  exit(0);
}

//LXI Zone
void cpu::LXI(uint16_t &reg) {
  cycles -= 10;
  mainBank.PC.word++;

  uint16_t val = mem->readMemory(mainBank.PC.word);
  mainBank.PC.word++;

  val |= (mem->readMemory(mainBank.PC.word) << 8);
  mainBank.PC.word++;

  reg = val;
}

void cpu::LXIBC() {
  LXI(mainBank.BC.word);
}

void cpu::LXIDE() {
  LXI(mainBank.DE.word);
}

void cpu::LXIHL() {
  LXI(mainBank.HL.word);
}

void cpu::LXISP() {
  LXI(mainBank.SP.word);
}

//STAX Zone
void cpu::STAX(uint16_t addr) {
  cycles -= 7;
  mainBank.PC.word++;

  mem->writeMemory(mainBank.AF.bytes.high, addr);
}

void cpu::STAXBC() {
  STAX(mainBank.BC.word);
}

void cpu::STAXDE() {
  STAX(mainBank.DE.word);
}

//INX Zone
void cpu::INX(uint16_t &reg) {
  cycles -= 5;
  mainBank.PC.word++;

  reg++;
}

void cpu::INXBC() {
  INX(mainBank.BC.word);
}

void cpu::INXDE() {
  INX(mainBank.DE.word);
}

//MVI Zone
void cpu::MVI(uint8_t &reg) {
    cycles -= 7;
    mainBank.PC.word++;

    reg = mem->readMemory(mainBank.PC.word);
    mainBank.PC.word++;
}

void cpu::MVIB() {
  MVI(mainBank.BC.bytes.high);
}

void cpu::MVIC() {
  MVI(mainBank.BC.bytes.low);
}

void cpu::MVID() {
  MVI(mainBank.DE.bytes.high);
}

void cpu::MVIE() {
  MVI(mainBank.DE.bytes.low);
}

//LDAX Zone
void cpu::LDAX(uint16_t addr) {
  cycles -= 7;
  mainBank.PC.word++;

  mainBank.AF.bytes.high = mem->readMemory(addr);
}

void cpu::LDAXBC() {
  LDAX(mainBank.BC.word);
}

void cpu::LDAXDE() {
  LDAX(mainBank.DE.word);
}

//DCX Zone
void cpu::DCX(uint16_t &reg) {
  cycles -= 5;
  mainBank.PC.word++;

  reg--;
}

void cpu::DCXBC() {
  DCX(mainBank.BC.word);
}

void cpu::DCXDE() {
  DCX(mainBank.DE.word);
}

void cpu::SHLD() {
  cycles -= 16;
  mainBank.PC.word++;

  registers_t val;
  val.word = mem->readMemory(mainBank.PC.word);
  mainBank.PC.word++;

  val.word |= (mem->readMemory(mainBank.PC.word) << 8);
  mainBank.PC.word++;

  mem->writeMemory(mainBank.HL.bytes.low, val.bytes.low);
  mem->writeMemory(mainBank.HL.bytes.high, val.bytes.high);
}

void cpu::XCHG() {
  uint16_t tmp = mainBank.DE.word;
  mainBank.DE.word = mainBank.HL.word;
  mainBank.HL.word = tmp;

  cycles -= 5;
  mainBank.PC.word++;
}

//R Zone
void cpu::RET() {
  mainBank.PC.bytes.low = stack.readMemory(mainBank.SP.word);
  mainBank.PC.bytes.high = stack.readMemory(mainBank.SP.word + 1);
  mainBank.SP.word += 2;

  cycles -= 10;
}

void cpu::RCond(uint8_t flag) {
  if(flag) {
    RET();
    cycles -= 1;
  } else {
    cycles -= 5;
  }
}

void cpu::RNZ() {
  RCond(!getZero());
}

void cpu::RZ() {
  RCond(getZero());
}

void cpu::RNC() {
  RCond(!getCarry());
}

void cpu::RC() {
  RCond(getCarry());
}

void cpu::RPO() {
  RCond(getParity());
}

void cpu::RPE() {
  RCond(!getParity());
}

void cpu::RP() {
  RCond(getParity());
}

void cpu::RM() {
  RCond(getAux());
}

bank_t cpu::getMainBank() {
  return mainBank;
}

void cpu::setMMIOInstance(uint16_t address, queue<uint8_t> *mmio) {
  IO[address] = mmio;
}
