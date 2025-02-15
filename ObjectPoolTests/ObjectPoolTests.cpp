#include "pch.h"
#include "CppUnitTest.h"
#include "../CDDS_Optimise/ObjectPool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ObjectPoolTests
{
	TEST_CLASS(ObjectPoolTests)
	{
	public:
		
		TEST_METHOD(ObjectPoolConstrcuctor)
		{
			ObjectPool<int> pool;
			Assert::IsNotNull(&pool);
			Assert::IsNotNull(&pool.m_objectsInPool);
			Assert::IsNotNull(&pool.m_objectsOutOfPool);
		}

		TEST_METHOD(activateObject)
		{
			ObjectPool<int> Pool;
			Assert::IsNotNull(&Pool);

			int critter = 5;
			int critter2 = 7;
			Pool.poolAdd(critter, 0);
			Pool.poolAdd(critter, 1);

			Assert::IsNotNull(&Pool.m_objectsInPool);
			Assert::AreEqual(5, *Pool.m_objectsOutOfPool.first());
			Assert::AreEqual(7, *Pool.m_objectsOutOfPool.last());
			Assert::AreEqual(2, Pool.m_objectsOutOfPool.getLength());

			Pool.deactivateObject(critter);
			Pool.deactivateObject(critter2);

			Assert::IsNotNull(&Pool.m_objectsOutOfPool);
			Assert::AreEqual(5, *Pool.m_objectsInPool.first());
			Assert::AreEqual(7, *Pool.m_objectsInPool.last());
			Assert::AreEqual(2, Pool.m_objectsInPool.getLength());

			Pool.activateObjectIndex(0);

			Assert::AreEqual(7, *Pool.m_objectsOutOfPool.first());
			Assert::AreEqual(7, *Pool.m_objectsOutOfPool.last());
			Assert::AreEqual(1, Pool.m_objectsOutOfPool.getLength());

			Assert::AreEqual(7, *Pool.m_objectsInPool.first());
			Assert::AreEqual(9, *Pool.m_objectsInPool.last());
			Assert::AreEqual(2, Pool.m_objectsInPool.getLength());

			Pool.activateObjectIndex(1);

			Assert::AreEqual(5, *Pool.m_objectsOutOfPool.first());
			Assert::AreEqual(7, *Pool.m_objectsOutOfPool.last());
			Assert::AreEqual(2, Pool.m_objectsOutOfPool.getLength());
		}

		TEST_METHOD(deactivateObject)
		{
			ObjectPool<int> Pool;
			Assert::IsNotNull(&Pool);

			int critter = 5;
			Pool.poolAdd(critter, 0);

			int critter2 = 7;
			Pool.poolAdd(critter2, 1);

			Assert::AreEqual(5, *Pool.m_objectsOutOfPool.first());
			Assert::AreEqual(7, *Pool.m_objectsOutOfPool.last());
			Assert::AreEqual(2, Pool.m_objectsOutOfPool.getLength());

			Pool.deactivateObject(critter);

			Assert::AreEqual(7, *Pool.m_objectsOutOfPool.first());
			Assert::AreEqual(7, *Pool.m_objectsOutOfPool.last());
			Assert::AreEqual(1, Pool.m_objectsOutOfPool.getLength());

			Assert::AreEqual(5, *Pool.m_objectsInPool.first());
			Assert::AreEqual(5, *Pool.m_objectsInPool.last());
			Assert::AreEqual(1, Pool.m_objectsInPool.getLength());

			Pool.deactivateObject(critter2);

			Assert::AreEqual(5, *Pool.m_objectsInPool.first());
			Assert::AreEqual(7, *Pool.m_objectsInPool.last());
			Assert::AreEqual(2, Pool.m_objectsInPool.getLength());

		}

		TEST_METHOD(poolAdd)
		{
			ObjectPool<int> Pool;
			Assert::IsNotNull(&Pool);

			int critter = 3;
			Pool.poolAdd(critter, 2); 

			Assert::AreEqual(3, *Pool.m_objectsOutOfPool.first());
			Assert::AreEqual(3, *Pool.m_objectsOutOfPool.last());
			Assert::AreEqual(1, Pool.m_objectsOutOfPool.getLength());

			int critter2 = 5;
			Pool.poolAdd(critter2, 2);

			Assert::AreEqual(3, *Pool.m_objectsOutOfPool.first());
			Assert::AreEqual(5, *Pool.m_objectsOutOfPool.last());
			Assert::AreEqual(2, Pool.m_objectsOutOfPool.getLength());
		}
	};
}
