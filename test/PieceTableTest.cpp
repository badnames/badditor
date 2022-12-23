#include <gtest/gtest.h>
#include "../src/PieceTable.h"

//
// Created by moritz on 22.12.22.
//
TEST(PieceTableTest, InitializePieceTable_ContainsEmtpyString) {
    auto table = editor::PieceTable();
    ASSERT_EQ(table.get(), "");
}

TEST(PieceTableTest, InitializePieceTableWithValue_ContainsGivenValue) {
    auto table = editor::PieceTable("Hello World");
    ASSERT_EQ(table.get(), "Hello World");
}

TEST(PieceTableTest, InitializePieceTableWithValue_ChangeInitialTable_ChangesAreReflectedInOutput) {
    auto table = editor::PieceTable("Hello World");
    table.cursor(5);
    table.put(" you beautiful");
    ASSERT_EQ(table.get(), "Hello you beautiful World");
}

TEST(PieceTableTest, InitializePieceTableWithValue_ChangeSingleCharacter_ChangesAreReflectedInOutput) {
    auto table = editor::PieceTable("Hello World");
    table.cursor(11);
    table.put('!');
    ASSERT_EQ(table.get(), "Hello World!");
}

TEST(PieceTableTest, InitializePieceTableWithValue_ChangeMultipleCharacters_ChangesAreReflectedInOutput) {
    auto table = editor::PieceTable("Hello World");
    table.cursor(11);
    table.put('!');
    table.put('?');
    ASSERT_EQ(table.get(), "Hello World!?");
}