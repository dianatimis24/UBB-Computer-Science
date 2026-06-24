#include "TestDynamicVector.h"
#include "DynamicVector.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>

void TestDynamicVector::testDynamicVector()
{
    // Test DynamicVector<>
    DynamicVector<int> vectorOfIntegers{ 2 };
    vectorOfIntegers.addElement(10);
    vectorOfIntegers.addElement(20);
    assert(vectorOfIntegers.getSize() == 2);
    assert(vectorOfIntegers[1] == 20);
    vectorOfIntegers[1] = 25;
    assert(vectorOfIntegers[1] == 25);
    vectorOfIntegers.addElement(30);
    assert(vectorOfIntegers.getSize() == 3);

    try
    {
        vectorOfIntegers.removeElement(-1);
    }
    catch (const std::exception& caughtException)
    {
        assert(true);
    }
    try
    {
        vectorOfIntegers.getElement(100);
    }
    catch (const std::exception& caughtException)
    {
        assert(true);
    }

    DynamicVector<int> copyOfVectorOfIntegers1{ vectorOfIntegers };
    assert(copyOfVectorOfIntegers1.getSize() == 3);

    DynamicVector<int> copyOfVectorOfIntegers2;
    copyOfVectorOfIntegers2 = vectorOfIntegers;
    assert(copyOfVectorOfIntegers2[0] == 10);
    assert(copyOfVectorOfIntegers2[0] == 10);
    int returnedPositionFromCopiedVector2 = copyOfVectorOfIntegers2.returnPosition(25);
    assert(returnedPositionFromCopiedVector2 == 1);
    copyOfVectorOfIntegers2.removeElement(1);
    assert(copyOfVectorOfIntegers2.getSize() == 2);


    // Test iterator
    DynamicVector<int>::Iterator iteratorForVectorOfIntegers = vectorOfIntegers.begin();
    DynamicVector<int>::Iterator copyOfIteratorForVectorOfIntegers = vectorOfIntegers.begin();

    assert(iteratorForVectorOfIntegers == copyOfIteratorForVectorOfIntegers);
    
    assert(*iteratorForVectorOfIntegers == 10);
    
    assert(iteratorForVectorOfIntegers != vectorOfIntegers.end());
    
    iteratorForVectorOfIntegers++;
    assert(*iteratorForVectorOfIntegers == 25);
    
    ++iteratorForVectorOfIntegers;
    assert(*iteratorForVectorOfIntegers == 30);

    // Test operator+
    DynamicVector<int> vector{};
    vector = vector + 2;
    assert(vector[0] == 2);
    vector = 3 + vector;
    assert(vector[1] == 3);
}