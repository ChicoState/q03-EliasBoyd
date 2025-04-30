/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"
#include <string>
using std::string;

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}

TEST(GuesserTest, lockoutTest1)
{
  Guesser object("Secret");
  ASSERT_EQ( true, object.match("Secret"));
  ASSERT_EQ( false, object.match("Secre"));
  ASSERT_EQ( true, object.match("Secret"));
  ASSERT_EQ( false, object.match("Secrt"));
  ASSERT_EQ( true, object.match("Secret"));
  ASSERT_EQ( false, object.match("Secrret"));
  ASSERT_EQ( false, object.match("Secret"));

}

TEST(GuesserTest, lockoutTest2)
{
	Guesser object("Secret");
	ASSERT_EQ( true, object.match("Secret"));
	ASSERT_EQ( false, object.match("BOB"));
	ASSERT_EQ( false, object.match("Secret"));

}


TEST(GuesserTest, nameTest)
{
	string name = "asdf12345";
	Guesser object(name);
	ASSERT_EQ( true, object.match(name));

}

TEST(GuesserTest, nameTest2)
{
	string name = "asdf 1/?!@#$%^&2345";
	Guesser object(name);
	ASSERT_EQ( true, object.match(name));

}

TEST(GuesserTest, nameTest3)
{
	string name = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
	Guesser object(name);
	ASSERT_EQ( true, object.match(name));

}

TEST(GuesserTest, distanceTest1)
{ 
	Guesser object("a s d f g");
	ASSERT_EQ( false, object.match("a s d f  g"));
	ASSERT_EQ( true, object.match("a s d f g"));
}

TEST(GuesserTest, distanceTest2)
{ 
	Guesser object("a s d f g");
	ASSERT_EQ( false, object.match("a s d fb g"));
	ASSERT_EQ( true, object.match("a s d f g"));
}
TEST(GuesserTest, distanceTest3)
{ 
	Guesser object("a s d f g");
	ASSERT_EQ( false, object.match("a s d ff g"));
	ASSERT_EQ( true, object.match("a s d f g"));
}
TEST(GuesserTest, distanceTest4)
{ 
	Guesser object("a s d f g");
	ASSERT_EQ( false, object.match("a s dg f g"));
	ASSERT_EQ( true, object.match("a s d f g"));
}

TEST(GuesserTest, distanceTest5)
{ 
	Guesser object("a s d f g");
	ASSERT_EQ( false, object.match("a s rd f g"));
	ASSERT_EQ( true, object.match("a s d f g"));
}

TEST(GuesserTest, distanceTest6)
{ 
	Guesser object("a s d f g");
	ASSERT_EQ( false, object.match(" a s d f g"));
	ASSERT_EQ( true, object.match("a s d f g"));
}


TEST(GuesserTest, distanceTest7)
{ 
	Guesser object("abcdefghijklmnop");
	ASSERT_EQ( false, object.match(" abcdefghijklmnop"));
	ASSERT_EQ( true, object.match("abcdefghijklmnop"));
}
