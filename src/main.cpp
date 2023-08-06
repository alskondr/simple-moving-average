#include "SimpleMovingAverage.h"

#include <fstream>

int main()
{
  auto input = generateSinData<double>(2000);
  auto output = simpleMovingAverage(input, 50);

  std::ofstream out;
  out.open("data.traj");
  for(unsigned long i = 0; i < output.size(); i++)
  {
    out << i << " " << output[i] << std::endl;
  }

  return 0;
}
