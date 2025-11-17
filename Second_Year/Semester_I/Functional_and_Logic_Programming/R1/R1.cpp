#include <iostream>
#include "lista.h"

bool duplicate(PNod n, TElem e);
bool isSetRecursive(PNod n);
bool isSet(Lista list);
int numberOfDistinctElementsRecursive(PNod n);
int numberOfDistinctElements(Lista list);

int main()
{
    Lista l1;
    l1 = creare();
    std::cout << "Check if is set: " << isSet(l1) << '\n';
    std::cout << "Number of distinct elements from the list: " << numberOfDistinctElements(l1) << '\n';
    distruge(l1);
}

bool duplicate(PNod n, TElem e)
{
    if (n == nullptr)
        return false;
    if (n->e == e)
        return true;
    return duplicate(n->urm, e);
}

bool isSetRecursive(PNod n)
{
    if (n == nullptr)
        return true;
    if (duplicate(n->urm, n->e))
        return false;
    return isSetRecursive(n->urm);
}

bool isSet(Lista list)
{
    return isSetRecursive(list._prim);
}

int numberOfDistinctElementsRecursive(PNod n)
{
    if (n == nullptr)
        return 0;
    if (duplicate(n->urm, n->e))
        return numberOfDistinctElementsRecursive(n->urm);
    return 1 + numberOfDistinctElementsRecursive(n->urm);
}

int numberOfDistinctElements(Lista list)
{
    return numberOfDistinctElementsRecursive(list._prim);
}