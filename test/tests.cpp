#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <thread>

#include "semaphore.hpp"

TEST_CASE("test_name", "test_category") {
  int shared{0};
  blnkr::Semaphore s{0};

  std::thread t1{[&s, &shared]() {
    s.wait();
    shared >>= 1;
  }};

  std::thread t2{[&s, &shared]() {
    shared += 42;
    s.signal();
  }};

  t1.join();
  t2.join();

  REQUIRE(shared == 21);
}
