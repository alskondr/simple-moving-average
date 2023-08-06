#include "SimpleMovingAverage.h"

#include <fstream>
#include <iostream>
#include <unistd.h>

void printUsage()
{
  std::cout << "Add one parameter:" << std::endl <<
               "-t Test SMA" << std::endl <<
               "-p Perfomance" << std::endl;
}

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    printUsage();
    return 0;
  }

  if(std::string(argv[1]) == "-t")
  {
    const auto& input = generateSinData<double>(2000);
    auto output = simpleMovingAverage(input, 50);

    std::ofstream out;
    out.open("data.traj");
    for(unsigned long i = 0; i < output.size(); i++)
    {
      out << i << " " << output[i] << std::endl;
    }

    std::cout << "Generate test data to data.traj" << std::endl;
  }
  else if(std::string(argv[1]) == "-p")
  {
    const auto& inputFloat = generateSinData<float>(1e6);
    const auto& inputDouble = generateSinData<double>(1e6);
    std::ofstream out;
    out.open("data.perf");
    out << "WindowSize" << ";" << "float" << ";" << "double" << std::endl;

    for(auto windowSize : {4, 8, 16, 32, 64, 128})
    {
      auto start = clock();
      simpleMovingAverage(inputFloat, windowSize);
      auto half = clock();
      simpleMovingAverage(inputDouble, windowSize);
      auto end = clock();

      double first = static_cast<double>(half - start) / CLOCKS_PER_SEC * 1000;
      double second = static_cast<double>(end - half) / CLOCKS_PER_SEC * 1000;
      out << windowSize << ";" << first << ";" << second << std::endl;
    }

    std::cout << "Generate perfomance data to data.perf" << std::endl;
  }
  else
  {
    printUsage();
  }

  return 0;
}
