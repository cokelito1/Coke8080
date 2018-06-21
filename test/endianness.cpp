#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "cpu.hpp"

TEST_CASE(  "Probando endiannes", "[machine]" ) {
  registers_t testRegister;

  #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  SECTION( "Probando Little Endian " ) {
    testRegister.bytes.high = 0x12;
    testRegister.bytes.low  = 0x34;

    REQUIRE( testRegister.word == 0x1234 );
  }
  #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  SECTION( "Probando Big Endian ") {
    testRegister.bytes.high = 0x12;
    testRegister.bytes.low  = 0x34;

    REQUIRE( testRegister.word == 0x1234 );
  }
  #endif
}
