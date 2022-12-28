#include "gtest/gtest.h"
#include "humblelogging/humblelogging.h"
#include "humblelogging/util/patternconfigregistry.h"
using namespace humble::logging;

TEST(Util, func_strfmt)
{
	const auto str = strfmt("hello %s!", "world");
	ASSERT_STREQ(str.c_str(), "hello world!");
}

TEST(Util, PatternConfigRegistryTest)
{
	PatternConfigRegistry reg;
	reg.loadFromString(
		"logger.level(*)=fatal\n"
		"logger.level(one*)=error\n"
		"logger.level(one.two*)=info\n"
		"logger.level(two*)=error\n"
		"logger.level(three.four.five)=debug\n"
		"logger.level(three.four.five.*)=fatal\n"
	);
	ASSERT_EQ(reg.getLogLevel("any"), LogLevel::Fatal);
	ASSERT_EQ(reg.getLogLevel("one"), LogLevel::Error);
	ASSERT_EQ(reg.getLogLevel("one.two"), LogLevel::Info);
	ASSERT_EQ(reg.getLogLevel("one.two.three"), LogLevel::Info);
	ASSERT_EQ(reg.getLogLevel("one.any.other"), LogLevel::Error);
	ASSERT_EQ(reg.getLogLevel("two"), LogLevel::Error);
	ASSERT_EQ(reg.getLogLevel("three.four.five"), LogLevel::Debug);
	ASSERT_EQ(reg.getLogLevel("three.four.five.any"), LogLevel::Fatal);
}

TEST(Log, FormatSimple)
{
	SimpleFormatter fmt;
	LogEvent event("Logger", LogLevel::Info, "Hello World", 42, "myfile.cpp", "myfunc()");
	const auto str = fmt.format(event);
}

TEST(Log, FormatPattern)
{}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}