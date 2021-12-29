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
#include <optional>
#include <functional>
#include <numeric>
#include <algorithm>

struct Bingo_Cell
{
   uint32_t num = 0;
   bool marked = false;
};

class Bingo_Card;

using opt_bingo_card_ref = std::optional<std::reference_wrapper<Bingo_Card>>;

class Bingo_Card
{
   static constexpr uint32_t ROWS = 5;
   static constexpr uint32_t COLS = 5;

public:

   Bingo_Card(uint32_t card_num)
      : card_id(card_num)
   {

   }

   void insert_row(const std::string& row_str,
                   const uint32_t dest_row)
   {
      uint32_t col = 0;
      std::istringstream tokens(row_str);
      for (std::string token;
           std::getline(tokens, token, ' ')
           ;)
      {
         if (token == "")
            continue;

         auto num = std::stoul(token);
         numbers[dest_row][col++].num = num;
      }
   }

   bool check_win(uint32_t target_row, uint32_t target_col)
   {
      uint32_t marked_nums_col = 0;

      for (uint32_t col = 0;
           col < COLS;
           ++col)
      {
         if (numbers[target_row][col].marked)
            ++marked_nums_col;
      }

      uint32_t marked_nums_row = 0;

      for (uint32_t row = 0;
           row < ROWS;
           ++row)
      {
         if (numbers[row][target_col].marked)
            ++marked_nums_row;
      }

      if (marked_nums_col == 5 &&
          marked_nums_row == 5)
      {
         int stop = 0;
      }

      if (marked_nums_col == 5 ||
          marked_nums_row == 5)
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   opt_bingo_card_ref mark(uint32_t draw_number)
   {
      for (uint32_t r = 0;
           r < ROWS;
           ++r)
      {
         for (uint32_t c = 0;
              c < COLS;
              ++c)
         {
            auto& cell = numbers[r][c];

            if (cell.num == draw_number)
            {
               cell.marked = true;

               if (check_win(r, c))
               {
                  winning_card = true;
               }
            }
         }
      }

      if (winning_card)
      {
         return *this;
      }
      else
      {
         return {};
      }
   }

   std::array<std::array<Bingo_Cell, ROWS>, COLS>&
      get_numbers()
   {
      return numbers;
   }

   bool is_winning_card() const
   {
      return winning_card;
   }

   uint32_t get_card_id() const
   {
      return card_id;
   }

private:

   bool winning_card = false;
   uint32_t card_id = 0;
   std::array<std::array<Bingo_Cell, ROWS>, COLS> numbers;
};

class Board
{
public:

   opt_bingo_card_ref mark(uint32_t draw_number)
   {
      opt_bingo_card_ref winning_card;

      for (auto& bingo_card : bingo_cards)
      {
         // if the card already won don't bother checking
         if (bingo_card.is_winning_card())
         {
            continue;
         }

         if (auto _ = bingo_card.mark(draw_number);
             _.has_value())
         {
            if (!winning_card.has_value())
               winning_card = _.value(); // we found a winning bingo card
         }
      }

      return winning_card;
   }

   std::vector<Bingo_Card>& get_bingo_cards()
   {
      return bingo_cards;
   }

   uint32_t num_bingo_cards() const
   {
      return bingo_cards.size();
   }

   uint32_t num_winning_cards() const
   {
      return std::count_if(bingo_cards.begin(),
                           bingo_cards.end(),
                           [](const Bingo_Card& card)
      {
         return card.is_winning_card();
      });


   }

private:
   std::vector<Bingo_Card> bingo_cards;

};

uint32_t part_01()
{
   std::ifstream file_stream("data\\input.txt");

   if (!file_stream.is_open())
   {
      throw std::runtime_error("Cannot open file");
   }

   // extract drawn numbers
   std::string drawn_numbers_str;
   std::getline(file_stream, drawn_numbers_str);

   std::vector<uint32_t> drawn_numbers;

   // collect drawn numbers in vector
   std::istringstream tokens(drawn_numbers_str);
   for (std::string token;
        std::getline(tokens, token, ',')
        ;)
   {
      auto num = std::stoul(token);
      drawn_numbers.push_back(num);
   }

   uint32_t card_num = 1;
   Board board;
   {
      Bingo_Card bingo_card(card_num++);
      uint32_t read_lines = 0;

      // create all the bingo cards
      for (std::string line;
           std::getline(file_stream, line)
           ;)
      {
         if (line == "")
            continue;

         ++read_lines;

         bingo_card.insert_row(line, read_lines - 1);

         if (read_lines == 5)
         {
            read_lines = 0;
            board.get_bingo_cards().push_back(std::move(bingo_card));
         }
      }
   }

   uint32_t score = 0;

   for (auto& draw_number : drawn_numbers)
   {
      if (auto _ = board.mark(draw_number);
          _.has_value())
      {
         auto bingo_card_ref = _.value();

         uint32_t unmaked_sum = 0;
         for (const auto& row : bingo_card_ref.get().get_numbers())
         {
            for (const auto& cell : row)
            {
               if (!cell.marked)
                  unmaked_sum += cell.num;
            }
         }

         score = unmaked_sum * draw_number;
         break;
      }
   }


   return score;
}



uint32_t part_02()
{
   std::ifstream file_stream("data\\input.txt");

   if (!file_stream.is_open())
   {
      throw std::runtime_error("Cannot open file");
   }

   // extract drawn numbers
   std::string drawn_numbers_str;
   std::getline(file_stream, drawn_numbers_str);

   std::vector<uint32_t> drawn_numbers;

   // collect drawn numbers in vector
   std::istringstream tokens(drawn_numbers_str);
   for (std::string token;
        std::getline(tokens, token, ',')
        ;)
   {
      auto num = std::stoul(token);
      drawn_numbers.push_back(num);
   }

   uint32_t card_num = 1;
   Board board;
   {
      Bingo_Card bingo_card(card_num);

      uint32_t read_lines = 0;

      // create all the bingo cards
      for (std::string line;
           std::getline(file_stream, line)
           ;)
      {
         if (line == "")
            continue;

         ++read_lines;

         bingo_card.insert_row(line, read_lines - 1);

         if (read_lines == 5)
         {
            read_lines = 0;
            board.get_bingo_cards().push_back(std::move(bingo_card));

            ++card_num;
            bingo_card = Bingo_Card(card_num);
         }
      }
   }

   uint32_t score = 0;

   for (auto& draw_number : drawn_numbers)
   {
      if (auto _ = board.mark(draw_number);
          _.has_value())
      {
         // we found a winning card!
         auto& bingo_card_ref = _.value();
         auto& bingo_card = bingo_card_ref.get();

         if (board.num_winning_cards() == board.num_bingo_cards())
         {
            uint32_t unmaked_sum = 0;
            for (const auto& row : bingo_card.get_numbers())
            {
               for (const auto& cell : row)
               {
                  if (!cell.marked)
                     unmaked_sum += cell.num;
               }
            }
            score = unmaked_sum * draw_number;
         }
      }
   }

   return score;
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
