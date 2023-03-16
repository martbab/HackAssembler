#include "gtest/gtest.h"
#include "../LibHackAssembler/Code.h"

struct CodeTestFixture : testing::Test {
	Code* code;
	CodeTestFixture() {
		code = new Code();
	}

	~CodeTestFixture() {
		delete code;
	}
};

TEST_F(CodeTestFixture, TestDest) {
	EXPECT_EQ(0b1110000000000000, code->emitDest(""));
	EXPECT_EQ(0b1110000000100000, code->emitDest("A"));
	EXPECT_EQ(0b1110000000110000, code->emitDest("AD"));
	EXPECT_EQ(0b1110000000111000, code->emitDest("ADM"));
	EXPECT_EQ(0b1110000000011000, code->emitDest("MD"));
	EXPECT_EQ(0b1110000000010000, code->emitDest("D"));
	EXPECT_EQ(0b1110000000001000, code->emitDest("M"));
	EXPECT_THROW(code->emitDest("ADDMDMD"), std::invalid_argument);
	EXPECT_THROW(code->emitDest("AX"), std::invalid_argument);
};

TEST_F(CodeTestFixture, testJmp) {
	EXPECT_THROW(code->emitJump("NONSENSE"), std::invalid_argument);
	EXPECT_EQ(0b1110000000000000, code->emitJump(""));
	EXPECT_EQ(0b1110000000000111, code->emitJump("JMP"));
	EXPECT_EQ(0b1110000000000001, code->emitJump("JGT"));
	EXPECT_EQ(0b1110000000000011, code->emitJump("JGE"));
	EXPECT_EQ(0b1110000000000110, code->emitJump("JLE"));
	EXPECT_EQ(0b1110000000000100, code->emitJump("JLT"));
	EXPECT_EQ(0b1110000000000101, code->emitJump("JNE"));
	EXPECT_EQ(0b1110000000000010, code->emitJump("JEQ"));
};

TEST_F(CodeTestFixture, testComp) {
	EXPECT_THROW(code->emitComp("nonsense"), std::invalid_argument);
	EXPECT_EQ(0b1110000000000000, code->emitComp(""));
	EXPECT_EQ(0b1111000000000000, code->emitComp("D&M"));
	EXPECT_EQ(0b1110000000000000, code->emitComp("D&A"));
	EXPECT_EQ(0b1110111111000000, code->emitComp("1"));
	EXPECT_EQ(0b1110101010000000, code->emitComp("0"));
	EXPECT_EQ(0b1111110000000000, code->emitComp("M"));
	EXPECT_EQ(0b1110110000000000, code->emitComp("A"));
	EXPECT_EQ(0b1110011111000000, code->emitComp("D+1"));
	EXPECT_EQ(0b1110000010000000, code->emitComp("D+A"));
	EXPECT_EQ(0b1111000111000000, code->emitComp("M-D"));
};