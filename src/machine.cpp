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

#include "machine.hpp"

machine::machine() {
  chip = new cpu(100);
  mem = new memory<uint8_t>(4096000);

  chip->setMemInstance(mem);
}

machine::~machine() {
  delete chip;
  delete mem;
}

void machine::startEmu() {
  mem->writeMemory(0xF2, 0x00);
  mem->writeMemory(0x4A, 0x01);
  mem->writeMemory(0x5C, 0x02);

  mem->writeMemory(0x00, 0x5C4A);

  mem->writeMemory(0xF2, 0x5C4B);
  mem->writeMemory(0x00, 0x5C4C);
  mem->writeMemory(0x00, 0x5C4D);

  while(chip->getCycles() > 0){
    chip->cycle();
  }
}
