#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "EventManager.h"

using namespace std;
using ::testing::MockFunction;

namespace {
Event MakeEvent(
    string id,
    string title,
    Event::TimePoint start,
    optional<Event::TimePoint> end = nullopt) {
    Event e{std::move(id), std::move(title), start, end};
    return e;
}
}

TEST(EventManagerTest, Create_ValidEvent_AssignsIdIfMissingAndNotifiesListeners) {
    EventManager mgr;

    MockFunction<void()> listener;
    mgr.subscribe(listener.AsStdFunction());

    // create() should notify listeners exactly once.
    EXPECT_CALL(listener, Call()).Times(1);

    auto now = chrono::system_clock::now();
    Event input = MakeEvent("", "Final Exam", now);

    const Event& stored = mgr.create(input);

    EXPECT_FALSE(stored.getId().empty());
    EXPECT_EQ(stored.getTitle(), "Final Exam");
    EXPECT_EQ(stored.getStart(), now);

    // all() returns events in chronological order (backed by the time multimap)
    auto all = mgr.all();
    ASSERT_EQ(all.size(), 1u);
    EXPECT_EQ(all[0].getId(), stored.getId());
}

TEST(EventManagerTest, Create_InvalidEvent_ThrowsAndDoesNotNotify) {
    EventManager mgr;

    MockFunction<void()> listener;
    mgr.subscribe(listener.AsStdFunction());

    // Title is whitespace only -> Validate::event() fails -> create() throws.
    EXPECT_CALL(listener, Call()).Times(0);

    auto now = chrono::system_clock::now();
    Event bad = MakeEvent("", "   ", now);

    EXPECT_THROW({ (void)mgr.create(bad); }, runtime_error);
    EXPECT_TRUE(mgr.all().empty());
}

TEST(EventManagerTest, Update_StartTimeChanges_ReindexesChronologicalOrderAndNotifies) {
    EventManager mgr;

    MockFunction<void()> listener;
    mgr.subscribe(listener.AsStdFunction());

    auto t0 = chrono::system_clock::now();
    auto t1 = t0 + chrono::hours(1);
    auto t2 = t0 + chrono::hours(2);

    // Two creates + one update => 3 notifications.
    EXPECT_CALL(listener, Call()).Times(3);

    const Event& a = mgr.create(MakeEvent("A", "Alpha", t1));
    const Event& b = mgr.create(MakeEvent("B", "Beta", t2));

    // Initially: A then B
    {
        auto all = mgr.all();
        ASSERT_EQ(all.size(), 2u);
        EXPECT_EQ(all[0].getId(), a.getId());
        EXPECT_EQ(all[1].getId(), b.getId());
    }

    // Move B earlier than A
    Event bUpdated = MakeEvent("B", "Beta", t0);
    ASSERT_TRUE(mgr.update(bUpdated));

    // Now: B then A
    {
        auto all = mgr.all();
        ASSERT_EQ(all.size(), 2u);
        EXPECT_EQ(all[0].getId(), "B");
        EXPECT_EQ(all[1].getId(), "A");
    }
}

TEST(EventManagerTest, SearchByTitle_IsCaseInsensitive_AndEmptyNeedleReturnsAll) {
    EventManager mgr;
    auto base = chrono::system_clock::now();
    mgr.create(MakeEvent("1", "Project Meeting", base));
    mgr.create(MakeEvent("2", "Grocery run", base + chrono::minutes(10)));
    mgr.create(MakeEvent("3", "MEET the team", base + chrono::minutes(20)));

    {
        TextQuery q;
        q.text = "meet";
        auto hit = mgr.searchByTitle(q);
        ASSERT_EQ(hit.size(), 2u);
        EXPECT_EQ(hit[0].getId(), "1");
        EXPECT_EQ(hit[1].getId(), "3");
    }

    {
        TextQuery q;
        q.text = ""; // contains(..., "") returns true
        auto hit = mgr.searchByTitle(q);
        EXPECT_EQ(hit.size(), 3u);
    }
}
