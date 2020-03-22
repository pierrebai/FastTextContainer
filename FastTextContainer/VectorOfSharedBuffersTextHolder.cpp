#include "TextHolder.h"

namespace FastTextContainer
{
   using namespace std;

   void VectorOfSharedBuffersTextHolder::ReadLines(std::wistream& stream)
   {
      ReadPos readPos;
      while (true)
      {
         auto result = ReadLine(stream, readPos);
         wchar_t* line = result.first;
         size_t count = result.second;
         if (count <= 0)
            break;

         Lines.emplace_back(line);
      }
   }

   std::pair<VectorOfSharedBuffersTextHolder::Line, size_t> VectorOfSharedBuffersTextHolder::ReadLine(std::wistream& stream, ReadPos& readPos)
   {
      bool skipNewLines = true;

      wchar_t* line = readPos.PosInBuffer;
      while (true)
      {
         if (readPos.PosInBuffer >= readPos.BufferEnd)
         {
            // Record how much we will need to transfer between the buffer
            // and how big the new buffer must be.
            const size_t amountReadSoFar = readPos.PosInBuffer - line;
            const size_t bufferSize = max(size_t(64 * 1024), amountReadSoFar * 2);

            // Allocate new buffer.
            TextBuffers.emplace_back(make_shared<Buffer>());
            auto buffer = TextBuffers.back();
            // Note: allocate one more character to be able to always put a terminating null.
            buffer->resize(bufferSize + 1);

            // Copy over the data that was reasd so far in th eprevious buffer.
            if (amountReadSoFar > 0)
               std::copy(line, line + amountReadSoFar, buffer->data());

            // Adjust the variable to point into the new buffer.
            line = buffer->data();
            readPos.BufferEnd = line + bufferSize;
            readPos.PosInBuffer = line + amountReadSoFar;

            // Fill the empty part of the new buffer.
            // Stop if there was nothign left to read.
            stream.read(readPos.PosInBuffer, readPos.BufferEnd - readPos.PosInBuffer);
            const auto readAmount = stream.gcount();
            if (readAmount <= 0)
               break;
            readPos.BufferEnd = readPos.PosInBuffer + readAmount;
         }

         if (skipNewLines)
         {
            if (*readPos.PosInBuffer != '\n' && *readPos.PosInBuffer != '\r')
            {
               line = readPos.PosInBuffer;
               skipNewLines = false;
            }
         }
         else
         {
            if (*readPos.PosInBuffer == '\n' || *readPos.PosInBuffer == '\r')
            {
               *readPos.PosInBuffer = 0;
               readPos.PosInBuffer++;
               break;
            }
         }

         ++readPos.PosInBuffer;
      }

      return make_pair(line, readPos.PosInBuffer - line);
   }
}
