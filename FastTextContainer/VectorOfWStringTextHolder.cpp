#include "TextHolder.h"

namespace FastTextContainer
{
   using namespace std;

   void VectorOfWStringTextHolder::ReadLines(std::wistream& stream)
   {
      wchar_t buffer[256];
      while (stream)
      {
         stream.getline(buffer, sizeof(buffer) - 1);
         const auto readAmount = stream.gcount();
         if (readAmount <= 0)
            break;
         Lines.emplace_back(buffer);
      }
   }
}
