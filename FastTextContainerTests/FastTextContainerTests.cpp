#include "TextHolder.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FastTextContainer;

namespace FastTextContainerTests
{
	TEST_CLASS(FastTextContainerTests)
	{
	public:
		
		TEST_METHOD(VectorOfWStringTextHolderReadLinesTest)
		{
			VectorOfWStringTextHolder holder;

			holder.ReadLines(PrepareTextToRead());

			Assert::AreEqual<size_t>(7, holder.Lines.size());
			Assert::AreNotEqual(wstring::npos, holder.Lines[0].find(L"first"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[1].find(L"second"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[2].find(L"third"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[3].find(L"fourth"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[4].find(L"fifth"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[5].find(L"sixth"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[6].find(L"seventh"));
		}

		TEST_METHOD(DequeOfWStringTextHolderReadLinesTest)
		{
			DequeOfWStringTextHolder holder;

			holder.ReadLines(PrepareTextToRead());

			Assert::AreEqual<size_t>(7, holder.Lines.size());
			Assert::AreNotEqual(wstring::npos, holder.Lines[0].find(L"first"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[1].find(L"second"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[2].find(L"third"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[3].find(L"fourth"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[4].find(L"fifth"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[5].find(L"sixth"));
			Assert::AreNotEqual(wstring::npos, holder.Lines[6].find(L"seventh"));
		}

		TEST_METHOD(VectorOfSharedBuffersTextHolderReadLinesTest)
		{
			VectorOfSharedBuffersTextHolder holder;

			holder.ReadLines(PrepareTextToRead());

			Assert::AreEqual<size_t>(7, holder.Lines.size());
			Assert::AreNotEqual(nullptr, wcsstr(holder.Lines[0], L"first"));
			Assert::AreNotEqual(nullptr, wcsstr(holder.Lines[1], L"second"));
			Assert::AreNotEqual(nullptr, wcsstr(holder.Lines[2], L"third"));
			Assert::AreNotEqual(nullptr, wcsstr(holder.Lines[3], L"fourth"));
			Assert::AreNotEqual(nullptr, wcsstr(holder.Lines[4], L"fifth"));
			Assert::AreNotEqual(nullptr, wcsstr(holder.Lines[5], L"sixth"));
			Assert::AreNotEqual(nullptr, wcsstr(holder.Lines[6], L"seventh"));
		}

	private:
		wistringstream PrepareTextToRead()
		{
			static const wchar_t text[] =
				L"first line\n"
				L"second line\n"
				L"third line\n"
				L"fourth line\n"
				L"fifth line\n"
				L"sixth line\n"
				L"seventh line\n";

			return wistringstream(text);
		}
	};
}
