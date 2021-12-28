#include <sstream>
#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <cassert>
#include <cstdint>
#include <utility>

uint32_t part_01()
{
   uint32_t res = 0;

   std::ifstream file_stream("data\\input.txt");

   if (!file_stream.is_open())
   {
      throw std::runtime_error("Cannot open file");
   }

   struct Data
   {
      uint32_t zeros = 0;
      uint32_t ones = 0;
   };

   std::string line;
   std::getline(file_stream, line);

   std::vector<Data> raw_data(line.size());

   for (size_t i = 0;
        i < line.size();
        ++i)
   {
      if (line[i] == '0')
         ++raw_data[i].zeros;
      else if (line[i] == '1')
         ++raw_data[i].ones;
      else
         throw std::runtime_error("Unknown number: " + line[i]);
   }

   for (;
        std::getline(file_stream, line);
        )
   {
      for (size_t i = 0;
           i < line.size();
           ++i)
      {
         if (line[i] == '0')
            ++raw_data[i].zeros;
         else if (line[i] == '1')
            ++raw_data[i].ones;
         else
            throw std::runtime_error("Unknown number: " + line[i]);
      }
   }

   std::string gamma_rate_str;
   std::string epsilon_rate_str;

   for (auto data : raw_data)
   {
      if (data.ones > data.zeros)
      {
         gamma_rate_str += "1";
         epsilon_rate_str += "0";
      }
      else
      {
         gamma_rate_str += "0";
         epsilon_rate_str += "1";
      }
   }

   uint32_t gamma_rate = std::stoul(gamma_rate_str, nullptr, 2);
   uint32_t epsilon_rate = std::stoul(epsilon_rate_str, nullptr, 2);

   return gamma_rate * epsilon_rate;
}


struct Zeros_And_Ones
{
   uint32_t zeros = 0;
   uint32_t ones = 0;
};

template<typename Predicate>
uint32_t part_02_helper(const std::vector<std::string>& numbers,
                        uint32_t col,
                        Predicate predicate)
{
   if (numbers.size() == 1)
   {
      return std::stoul(numbers[0], nullptr, 2);
   }

   Zeros_And_Ones zeros_and_ones;

   std::vector<std::string> zeros;
   std::vector<std::string> ones;

   for (const auto& line : numbers)
   {
      if (line[col] == '0')
      {
         zeros.push_back(line);
         ++zeros_and_ones.zeros;
      }
      else if (line[col] == '1')
      {
         ones.push_back(line);
         ++zeros_and_ones.ones;
      }
      else
         throw std::runtime_error("Unknown number: " + line);
   }

   if (predicate(zeros_and_ones))
   {
      return part_02_helper(ones, col + 1, predicate);
   }
   else
   {
      return part_02_helper(zeros, col + 1, predicate);
   }

}

int part_02()
{
   std::ifstream file_stream("data\\input.txt");

   if (!file_stream.is_open())
   {
      throw std::runtime_error("Cannot open file");
   }

   std::vector<std::string> lines;
   lines.reserve(1000);

   for (std::string line;
        std::getline(file_stream, line);
        )
   {
      lines.push_back(std::move(line));
   }

   auto oxygen_generator_rating = part_02_helper(lines, 0,
                                                 [](const Zeros_And_Ones& zeros_and_ones)
   {
      return (zeros_and_ones.ones > zeros_and_ones.zeros ||
              zeros_and_ones.ones == zeros_and_ones.zeros);
   });

   auto CO2_scrubber_rating = part_02_helper(lines, 0,
                                                 [](const Zeros_And_Ones& zeros_and_ones)
   {
      return (zeros_and_ones.ones < zeros_and_ones.zeros);
   });

   return oxygen_generator_rating * CO2_scrubber_rating;
}

int main()
{
   try
   {
      std::cout << "Part 1: " << part_01() << std::endl;
      std::cout << "Part 2: " << part_02() << std::endl;
   }
   catch (const std::exception& e)
   {
      std::cout << "Exception: " << e.what() << std::endl;
   }

   return 0;
}
