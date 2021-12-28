#include <sstream>
#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <array>
#include <cassert>

int part_01()
{
   int res = -1;

   std::ifstream file_stream("data\\input.txt");

   if (!file_stream.is_open())
   {
      std::cout << "cannot open file" << std::endl;
      return res;
   }

   int horizontal_pos = 0;
   int depth = 0;

   for (std::string line; 
        std::getline(file_stream, line); 
        )
   {
      std::istringstream stream(line);
      
      std::string direction;
      int amount;

      stream >> direction >> amount;

      if (direction == "forward")
      {
         horizontal_pos += amount;
      }
      else if (direction == "up")
      {
         depth -= amount;
      }
      else if (direction == "down")
      {
         depth += amount;
      }
      else
      {
         throw std::runtime_error("Unknown direction: " + direction);
      }
   }

   res = horizontal_pos * depth;

   return res;
}

int part_02()
{
   int res = -1;

   std::ifstream file_stream("data\\input.txt");

   if (!file_stream.is_open())
   {
      std::cout << "cannot open file" << std::endl;
      return res;
   }

   int horizontal_pos = 0;
   int depth = 0;
   int aim = 0;

   for (std::string line; 
        std::getline(file_stream, line); 
        )
   {
      std::istringstream stream(line);

      std::string direction;
      int amount;

      stream >> direction >> amount;

      if (direction == "forward")
      {
         horizontal_pos += amount;
         depth += aim * amount;
      }
      else if (direction == "up")
      {
         aim -= amount;
      }
      else if (direction == "down")
      {
         aim += amount;
      }
      else
      {
         throw std::runtime_error("Unknown direction: " + direction);
      }
   }

   res = horizontal_pos * depth;

   return res;
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
