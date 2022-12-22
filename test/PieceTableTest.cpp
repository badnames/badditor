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
    auto table = editor::PieceTable((std::string &) "Hello World");
    ASSERT_EQ(table.get(), "Hello World");
}