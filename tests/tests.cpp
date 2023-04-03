#include "humblelogging/humblelogging.h"
#include "humblelogging/util/patternconfigregistry.h"
#include "gtest/gtest.h"
using namespace humble::logging;

TEST(Util, func_strfmt)
{
	const auto str = strfmt("hello %s!", "world");
	ASSERT_STREQ(str.c_str(), "hello world!");
}

//TEST(Util, MutexTest)
//{
//	Mutex m;
//	std::string buf;
//	auto f1 = [&]() {
//		MutexLockGuard l(m);
//		for (auto i = 0; i < 4096; i++)
//			buf.append("1\n");
//	};
//	auto f2 = [&]() {
//		MutexLockGuard l(m);
//		for (auto i = 0; i < 4096; i++)
//			buf.append("1\n");
//	};
//}

TEST(Util, PatternConfigRegistryTest)
{
	PatternConfigRegistry reg;
	reg.loadFromString(
		"logger.level(*)=fatal\n"
		"logger.level(one*)=error\n"
		"logger.level(one.two*)=info\n"
		"logger.level(two*)=error\n"
		"logger.level(three.four.five)=debug\n"
		"logger.level(three.four.five.*)=fatal\n");
	ASSERT_EQ(reg.getLogLevel("any"), LogLevel::Fatal);
	ASSERT_EQ(reg.getLogLevel("one"), LogLevel::Error);
	ASSERT_EQ(reg.getLogLevel("one.two"), LogLevel::Info);
	ASSERT_EQ(reg.getLogLevel("one.two.three"), LogLevel::Info);
	ASSERT_EQ(reg.getLogLevel("one.any.other"), LogLevel::Error);
	ASSERT_EQ(reg.getLogLevel("two"), LogLevel::Error);
	ASSERT_EQ(reg.getLogLevel("three.four.five"), LogLevel::Debug);
	ASSERT_EQ(reg.getLogLevel("three.four.five.any"), LogLevel::Fatal);
}

TEST(Configuration, CommonConfigurationTest)
{
	auto config = std::make_unique<Configuration>();
	ASSERT_EQ(config->getLogLevel("test", nullptr), LogLevel::All);

	config->setupFromLogLevel(LogLevel::Info);
	ASSERT_EQ(config->getLogLevel("foo.bar", nullptr), LogLevel::Info);
}

TEST(Log, WouldLog)
{
	// Default behavior: Log ALL.
	auto config = std::make_unique<Configuration>();
	ASSERT_EQ(config->getLogLevel("test", nullptr), LogLevel::All);

	auto& fac = Factory::getInstance();
	config = std::make_unique<Configuration>();
	config->setupFromLogLevel(LogLevel::Info);
	fac.setConfiguration(std::move(config));

	auto myLogger = fac.getLogger("MyLogger");
	ASSERT_TRUE(myLogger->wouldLog(LogLevel::Fatal));
	ASSERT_TRUE(myLogger->wouldLog(LogLevel::Error));
	ASSERT_TRUE(myLogger->wouldLog(LogLevel::Info));
	ASSERT_FALSE(myLogger->wouldLog(LogLevel::Debug));
	ASSERT_FALSE(myLogger->wouldLog(LogLevel::Trace));
}

int main(int argc, char** argv)
{
	// Init Logging.
	Factory::getInstance();
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}