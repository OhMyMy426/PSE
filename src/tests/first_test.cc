#include <gtest/gtest.h>
#include "ParticleContainer.cpp"
#include "Particle.cpp"
#include <unordered_map>
#include "../src/Cuboid.cpp"
#include "../src/Cuboid.h"
#include "spdlog/spdlog.h"
#include"Calculator.h"
#include"LJCalculator.h"
#include"Particle.h"
#include "../src/LJCalculator.cpp"
#include "../src/Calculator.cpp"
#include "Generator.h"
#include "Generator.cpp"




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

TEST(CalculateFTest, Easy_Test3) {

    LJCalculator c;

    double sigma = 1.0;
    double epsilon = 0.0;

    std::array<double, 3> f= {0,0,0};
    std::array<double, 3> v= {0,0,0};
    std::array<double, 3> x= {0,0,0};
    std::array<double, 3> x1= {1,1,1};
    std::array<double, 3> f1= {1,1,1};

    Particle Particle2(x,x,1,1);
    Particle Particle(x1,x1,1,1);

    Particle2.setF(f1);
    Particle2.setX(x1);
    Particle2.setV(v);
    Particle.setF(f);
    Particle.setX(x);
    Particle.setV(v);

  c.calculateF_LJ(Particle2,Particle, sigma, epsilon);


  EXPECT_EQ(f, Particle.getF());
}

TEST(initializeTest, Easy_Test3) {
    std::array<double, 3> f= {0,0,0};
    std::array<double, 3> v= {0,0,0};
    std::array<int, 3> x= {0,0,0};
    std::array<double, 3> x1= {0,0,0};
    std::array<int, 3> a1= {1,1,1};

    Particle particle1(x1,x1,1,1);


    Cuboid cuboid( x1,a1,2.0,2.0,v,0.0,3);
    Cuboid cuboid2( x1,a1,2.0,2.0,v,0.0,3);
    std::vector<Cuboid> cuboids;

    cuboids.emplace_back(cuboid);
    cuboids.emplace_back(cuboid2);
    cuboids.emplace_back(cuboid2);


    std::unordered_map<int, Particle> particles;
    int particle_counter = 20;
    static ParticleContainer particleContainer(particles, particle_counter);

    Generator generator;
    generator.initialise(cuboids,particleContainer);
    EXPECT_EQ(3, cuboids.size());
    EXPECT_EQ(3, particleContainer.getParticles().size());
}

/*TEST(CalculatexTest, Easy_Test4) {
  std::unordered_map<int, Particle> particles;
  int particle_counter4 = 2;
  static ParticleContainer particleContainer(particles, particle_counter4);
    std::array<double, 3> x= {0,0,0};
  particleContainer.getParticles().at(0).setF(  x);
  particleContainer.getParticles().at(0).setX(x);
  particleContainer.getParticles().at(0).setv(x);
  particleContainer.getParticles().at(0).setOldF(x);
   particleContainer.getParticles().at(0).setM(20);
   cal


  calculateX(particleContainer,0.2);
  
EXPECT_EQ(x, particleContainer.getParticles().at(0).getX());
}

TEST(CalculateVTest, Easy_Test5) {
  std::unordered_map<int, Particle> particles;
  int particle_counter5 = 2;
  static ParticleContainer particleContainer(particles, particle_counter5);
  std::array<double, 3> v= {0,0,0};
  particleContainer.getParticles().at(0).setF(  v);
  particleContainer.getParticles().at(0).setX(v);
  particleContainer.getParticles().at(0).setv(v);
  particleContainer.getParticles().at(0).setOldF(v);
   particleContainer.getParticles().at(0).setM(20);
  calculateV(particleContainer,0.2);
    
EXPECT_EQ(v, particleContainer.getParticles().at(0).getV());
}
*/