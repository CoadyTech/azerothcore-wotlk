/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Util.h"
#include "gtest/gtest.h"

TEST(Utf8TruncateTest, ShorterStringsAreUntouched)
{
    std::string str = "hello";
    utf8truncate(str, 48);
    EXPECT_EQ(str, "hello");

    utf8truncate(str, 5);
    EXPECT_EQ(str, "hello");
}

TEST(Utf8TruncateTest, CutsOnCodePointBoundary)
{
    std::string str = "h\xC3\xA9llo";
    utf8truncate(str, 2);
    EXPECT_EQ(str, "h\xC3\xA9");

    utf8truncate(str, 0);
    EXPECT_TRUE(str.empty());
}

// Characters outside the BMP take two UTF-16 units each; this used to overflow the conversion buffer
TEST(Utf8TruncateTest, HandlesCharactersOutsideTheBmp)
{
    std::string str;
    for (int i = 0; i < 2500; ++i)
        str += "\xF0\x9F\x98\x80";

    utf8truncate(str, 48);
    EXPECT_EQ(str.size(), 48u * 4);
}

TEST(Utf8TruncateTest, InvalidUtf8IsCleared)
{
    std::string str = "ab\xFF" "cd";
    utf8truncate(str, 4);
    EXPECT_TRUE(str.empty());
}
