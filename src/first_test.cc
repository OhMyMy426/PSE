#include <gtest/gtest.h>
#include "ParticleContainer.cpp"
#include "Particle.cpp"
#include <unordered_map>

void Factorial(int n, int& result)
{
  result = 1;
  for (int i = 1; i <= n; i++)
    result *= i;
}



// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(FactorialTest, Mytest)
{
  int result = 0;
  Factorial(5, result);
  EXPECT_EQ(120, result);
}

TEST(ParticaleContainerTest, Easy_Test) {
  std::unordered_map<int, Particle> particles;
  int particle_counter = 20;
  static ParticleContainer particleContainer(particles, particle_counter);
  EXPECT_EQ(20, particleContainer.getParticle_counter());
}