#include <gtest/gtest.h>

#include "Validate.h"

using namespace std;

TEST(ValidateTest, NonEmpty_TrimsWhitespace) {
    EXPECT_FALSE(Validate::nonEmpty(""));
    EXPECT_FALSE(Validate::nonEmpty("   \t\n"));
    EXPECT_TRUE(Validate::nonEmpty(" a "));
}

TEST(ValidateTest, Chronological_AllowsNoEndAndEndAfterStart) {
    auto t0 = chrono::system_clock::now();
    auto t1 = t0 + chrono::minutes(1);

    {
        Event noEnd{"id", "Title", t0, nullopt};
        EXPECT_TRUE(Validate::chronological(noEnd));
        EXPECT_EQ(Validate::event(noEnd), nullopt);
    }

    {
        Event ok{"id", "Title", t0, t1};
        EXPECT_TRUE(Validate::chronological(ok));
        EXPECT_EQ(Validate::event(ok), nullopt);
    }
}

TEST(ValidateTest, Event_FailsWhenEndBeforeStart_AndWhenTitleEmpty) {
    auto t0 = chrono::system_clock::now();
    auto tNeg = t0 - chrono::minutes(1);

    {
        Event badTitle{"id", "   ", t0, nullopt};
        auto err = Validate::event(badTitle);
        ASSERT_TRUE(err.has_value());
        EXPECT_NE(err->message.find("Title"), string::npos);
    }

    {
        Event badTime{"id", "Ok", t0, tNeg};
        auto err = Validate::event(badTime);
        ASSERT_TRUE(err.has_value());
        EXPECT_NE(err->message.find("End Time"), string::npos);
    }
}
