#include "Tree.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FastTextContainer;

namespace FastTextContainerTests
{
	TEST_CLASS(TreeTests)
	{
	public:
		
		TEST_METHOD(SimpleTreeTest)
		{
			SimpleTree tree;

			tree.Root = tree.CreateNode();
			tree.Root->Left = tree.CreateNode();
			tree.Root->Right = tree.CreateNode();
			tree.Root->Right->Right = tree.CreateNode();

			Assert::IsNotNull(tree.Root.get());
			Assert::IsNotNull(tree.Root->Left.get());
			Assert::IsNotNull(tree.Root->Right.get());
			Assert::IsNotNull(tree.Root->Right->Right.get());

			Assert::IsNull(tree.Root->Left->Left.get());
			Assert::IsNull(tree.Root->Left->Right.get());
			Assert::IsNull(tree.Root->Right->Left.get());
			Assert::IsNull(tree.Root->Right->Right->Left.get());
			Assert::IsNull(tree.Root->Right->Right->Right.get());
		}

		TEST_METHOD(FastTreeTest)
		{
			FastTree tree;

			tree.Root = tree.CreateNode();
			tree.Root->Left = tree.CreateNode();
			tree.Root->Right = tree.CreateNode();
			tree.Root->Right->Right = tree.CreateNode();

			Assert::IsNull(tree.Root->Left->Left);
			Assert::IsNull(tree.Root->Left->Right);
			Assert::IsNull(tree.Root->Right->Left);
			Assert::IsNull(tree.Root->Right->Right->Left);
			Assert::IsNull(tree.Root->Right->Right->Right);
		}

	};
}
