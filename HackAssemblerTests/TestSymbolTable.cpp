#include "gtest/gtest.h"
#include "../LibHackAssembler/SymbolTable.h"

struct SymbolTableFixture : testing::Test {
	std::unique_ptr<SymbolTable::Builder> symbolTableBuilder;

	SymbolTableFixture() : symbolTableBuilder {SymbolTable::builder()} {}
};

TEST_F(SymbolTableFixture, InsertLookupTest) {
	symbolTableBuilder->addVariable("Symbol1");
	symbolTableBuilder->addVariable("Symbol2");
    auto symbolTable = symbolTableBuilder->build();
  EXPECT_EQ(VARIABLE_OFFSET, symbolTable->getAddress("Symbol1"));
  EXPECT_EQ(VARIABLE_OFFSET + 1, symbolTable->getAddress("Symbol2"));
  EXPECT_THROW(symbolTable->getAddress("LOL"), std::invalid_argument);
  EXPECT_EQ(0, symbolTable->getAddress("SP"));
  EXPECT_EQ(0, symbolTable->getAddress("R0"));
  EXPECT_EQ(0x4000, symbolTable->getAddress("SCREEN"));
  EXPECT_EQ(0x6000, symbolTable->getAddress("KBD"));
  EXPECT_EQ(4, symbolTable->getAddress("THAT"));
}