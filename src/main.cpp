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

#include "machine.hpp"

int main(int argc, char *argv[])
{
  std::cout << "Coke8080 ver 0.01" << std::endl;

  if(argc < 2) {
    std::cout << "Usage: " << argv[0] << " <rom.bin> <registers.log>" << std::endl;
    return -1;
  }

  if(argc == 2) {
    std::cout << "Partiendo maquina 1" << std::endl;
    machine *maquina = new machine();
    maquina->loadRom(argv[1]);
    maquina->startEmu();
    delete maquina;
  } else if(argc == 3) {
    std::cout << "Partiendo maquina 1" << std::endl;
    machine *maquina = new machine(true, argv[2]);
    maquina->loadRom(argv[1]);
    maquina->startEmu();
    delete maquina;
  }

  return 0;
}
