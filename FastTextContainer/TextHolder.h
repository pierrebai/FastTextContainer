#pragma once

#ifndef TEXT_HOLDER_H
#define TEXT_HOLDER_H

#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <vector>

namespace FastTextContainer
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Holds whatever is necessary to make the text lines
   // for the lifetime of a text holder.

   struct TextHolder
   {
      virtual ~TextHolder() = default;
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Holds text as a vector of standard text strings.
   //
   // Beware that the string text pointers could theoretically moved while the vector
   // is filled, so don't rely on their address until all the lines have been read.

   struct VectorOfWStringTextHolder : TextHolder
   {
      using Line = std::wstring;

      std::vector<Line> Lines;

      void ReadLines(std::wistream& stream);
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Holds text as a deque of standard text strings.
   //
   // Beware that the string text pointers could theoretically moved while the vector
   // is filled, so don't rely on their address until all the lines have been read.

   struct DequeOfWStringTextHolder : TextHolder
   {
      using Line = std::wstring;

      std::deque<Line> Lines;

      void ReadLines(std::wistream& stream);
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Holds text as a vector of raw characters buffers.
   // Uses indirection to make sure each buffer does not change address.

   struct VectorOfSharedBuffersTextHolder : TextHolder
   {
      typedef std::vector<wchar_t> Buffer;
      typedef std::shared_ptr<Buffer> BufferPtr;
      typedef std::vector<BufferPtr> Buffers;

      Buffers TextBuffers;

      // The text lines.
      using Line = wchar_t *;

      std::vector<Line> Lines;

      void ReadLines(std::wistream& stream);

   private:
      struct ReadPos
      {
         wchar_t* PosInBuffer = nullptr;
         wchar_t* BufferEnd = nullptr;
      };

      std::pair<Line, size_t> ReadLine(std::wistream& stream, ReadPos& readPos);
   };
}

#endif
