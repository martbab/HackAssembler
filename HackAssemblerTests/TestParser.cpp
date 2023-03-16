#include "gtest/gtest.h"
#include "../LibHackAssembler/Parser.h"
#include "../LibHackAssembler/SymbolTable.h"
#include "../LibHackAssembler/Code.h"
#include "CommandVectorBuilder.h"

struct ParserTestFixture : testing::Test {
	std::shared_ptr<Code> code;
	std::unique_ptr<Parser> parser;

	ParserTestFixture() {
		code = std::make_shared<Code>();
		parser = std::make_unique<Parser>(code);
	}
};

void expect_same_commands(
	std::vector<std::unique_ptr<BaseCommand>> expected,
	std::vector<std::unique_ptr<BaseCommand>> actual) {
	EXPECT_EQ(expected.size(), actual.size());

	auto expected_iter = expected.begin();
	auto actual_iter = actual.begin();

	while (expected_iter != expected.end() && actual_iter != actual.end()) {
		auto expected_command = expected_iter->get();
		auto actual_command = actual_iter->get();
		if (!expected_command->equals(actual_command)) {
			EXPECT_TRUE(false) <<
				"Expected: " << expected_command->toString()
				<< " got: "
				<< actual_command->toString()
				<< std::endl;
		}
		// ASSERT_TRUE(expected_command == actual_command);
		expected_iter++;
		actual_iter++;
	}
}

TEST_F(ParserTestFixture, TestParse) {
	EXPECT_EQ(parser->parse(std::istringstream("")), std::vector<std::unique_ptr<BaseCommand>>());

	expect_same_commands(
		CommandVectorBuilder()
			.add_a_command("i", VARIABLE_OFFSET + 1)
			.add_c_command("M", "1", "", code)
			.build(),
		parser->parse(std::istringstream("@i\nM=1\n"))
	);

	expect_same_commands(
		CommandVectorBuilder()
			.add_c_command("M", "D&M", "", code)
			.build(),
		parser->parse(std::istringstream("\nM=D&M\n"))
	);
	expect_same_commands(
		CommandVectorBuilder()
			.add_a_command("ponggame.0", VARIABLE_OFFSET + 1)
			.build(),
		parser->parse(std::istringstream("\n@ponggame.0\n"))
	);

	expect_same_commands(
		CommandVectorBuilder()
			.add_a_command("2", 2)
			.add_c_command("D", "A", "", code)
			.add_a_command("3", 3)
			.add_c_command("D", "D+A", "", code)
			.add_a_command("0", 0)
			.add_c_command("M", "D", "", code)
			.build(),
		parser->parse(std::istringstream("@2\nD=A\n@3\nD=D+A\n@0\nM=D\n"))
	);
}

const std::string example_from_book(R"EX(
// Adds 1 + ... + 100
	@i
	M=1 // i=1
	@sum
	M=0 // sum=0
(LOOP)
	@i
	D=M // D=i
	@100
	D=D-A // D=i-100
	@END
	D;JGT // if (i-100) > 0 goto END
	@i
	D=M // D=i
	@sum
	M=D+M // sum=sum + i
	@i
	M=M+1 // i=i+1
	@LOOP
	0;JMP // goto LOOP
(END)
	@END
	0;JMP // infinite loop	
)EX");

TEST_F(ParserTestFixture, TestParseExampleFromBook) {
	expect_same_commands(
		CommandVectorBuilder()
			.add_a_command("i", VARIABLE_OFFSET + 1)
			.add_c_command("M", "1", "", code)
			.add_a_command("sum", VARIABLE_OFFSET + 2)
			.add_c_command("M", "0", "", code)
			.add_a_command("i", VARIABLE_OFFSET + 1)
			.add_c_command("D", "M", "", code)
			.add_a_command("100", 100)
			.add_c_command("D", "D-A", "", code)
			.add_a_command("END", 19)
			.add_c_command("", "D", "JGT", code)
			.add_a_command("i", VARIABLE_OFFSET + 1)
			.add_c_command("D", "M", "", code)
			.add_a_command("sum", VARIABLE_OFFSET + 2)
			.add_c_command("M", "D+M", "", code)
			.add_a_command("i", VARIABLE_OFFSET + 1)
			.add_c_command("M", "M+1", "", code)
			.add_a_command("LOOP", 4)
			.add_c_command("", "0", "JMP", code)
			.add_a_command("END", 18)
			.add_c_command("", "0", "JMP", code)
			.build(),
		parser->parse(std::istringstream(example_from_book))
	);
}
