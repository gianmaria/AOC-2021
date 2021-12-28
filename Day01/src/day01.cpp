#include <sstream>
#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <array>

int part_01()
{
   try
   {
      std::ifstream ifs("data\\input.txt");

      if (!ifs.is_open())
      {
         std::cout << "cannot open file" << std::endl;
         return 1;
      }

      std::string line;
      std::getline(ifs, line);

      int increase = 0;
      int prev = std::stoi(line);

      for (; std::getline(ifs, line); )
      {
         int current = std::stoi(line);
         if (current > prev)
            ++increase;

         prev = current;
      }

      std::cout << "Res is: " << increase << std::endl;

   }
   catch (const std::exception& e)
   {
      std::cout << "Exception: " << e.what() << std::endl;
   }
   return 0;
}

int part_02()
{
   try
   {
      std::ifstream ifs("data\\input.txt");

      if (!ifs.is_open())
      {
         std::cout << "cannot open file" << std::endl;
         return 1;
      }

      std::array<int, 3> data;

      for (int i = 0;
           i < 3;
           ++i)
      {
         std::string line;
         std::getline(ifs, line);

         data[i] = std::stoi(line);
      }

      int increase = 0;
      int prev = data[0] + data[1] + data[2];
      int current = 0;

      int index = 0;
      for (std::string line; 
           std::getline(ifs, line); 
           )
      {
         data[index] = std::stoi(line);
         ++index;
         index = index % 3;

         current = data[0] + data[1] + data[2];

         if (current > prev)
            ++increase;

         prev = current;
      }

      std::cout << "Res is: " << increase << std::endl;
   }
   catch (const std::exception& e)
   {
      std::cout << "Exception: " << e.what() << std::endl;
   }
   return 0;
}

int main()
{
   part_01();
   part_02();

   return 0;
}
