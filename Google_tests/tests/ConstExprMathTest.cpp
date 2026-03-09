//
// Copyright 2026 scholar-of-artifice
//
// Licensed under the MIT License
//
// Copyright (c) 2026 scholar-of-artifice
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ConstExprMath.h"

TEST(ConstExprMathTest, RaisePowerWithZeroExponentReturnsOne) {
  // GIVEN any base value...
  // AND an exponent of 0...
  // WHEN RaisePower is called..
  // THEN the result is 1
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(1.0, 0), 1.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(2.0, 0), 1.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(3.0, 0), 1.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(9.123, 0), 1.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(10.9812387, 0), 1.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(123.0, 0), 1.0);
}

TEST(ConstExprMathTest, RaisePowerWithOneExponentReturnsBaseValue) {
  // GIVEN any base value...
  // AND an exponent of 1...
  // WHEN RaisePower is called..
  // THEN the result is the base value
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(1.0, 1), 1.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(2.0, 1), 2.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(3.0, 1), 3.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(9.123, 1), 9.123);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(10.9812387, 1), 10.9812387);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(123.0, 1), 123.0);
}

TEST(ConstExprMathTest, RaisePowerWithZeroBaseReturnsZero) {
  // GIVEN any base value...
  // AND an exponent of 0...
  // WHEN RaisePower is called..
  // THEN the result is 0
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(0.0, 1), 0.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(0.0, 2), 0.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(0.0, 3), 0.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(0.0, 14), 0.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(0.0, 95), 0.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(0.0, 123), 0.0);
}

TEST(ConstExprMathTest, RaisePowerCalculatesCorrectly) {
  // GIVEN a base value...
  // AND an exponent value...
  // WHEN RaisePower is called..
  // THEN the result is correct
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(2.0, 3), 8.0);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(3.33333333, 3), 37.037036925925925);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(1.00001, 5), 1.0000500010000104);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(1.000001, 5), 1.0000050000099996);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(1.0000001, 5), 1.0000005000001002);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(13.01, 2), 169.2601);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(23.108, 2), 533.979664);
  EXPECT_DOUBLE_EQ(game_dice_cpp::RaisePower(53.0, 3), 148877.0);
}