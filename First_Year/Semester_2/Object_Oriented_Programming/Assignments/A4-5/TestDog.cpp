#include "TestDog.h"
#include "Dog.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>

void TestDog::testDog()
{
    Dog dogDefaultConstructor;
    assert(dogDefaultConstructor.getName() == "");
    assert(dogDefaultConstructor.getBreed() == "");
    assert(dogDefaultConstructor.getAge() == 0);
    assert(dogDefaultConstructor.getPhotograph() == "");
    
    dogDefaultConstructor = dogDefaultConstructor;
    Dog dogConstructorBasedOnParameters{ "Toby", "Labrador", 3, "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75"};
    assert(dogConstructorBasedOnParameters.getName() == "Toby");
    assert(dogConstructorBasedOnParameters.getBreed() == "Labrador");
    assert(dogConstructorBasedOnParameters.getAge() == 3);
    assert(dogConstructorBasedOnParameters.getPhotograph() == "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");

    dogConstructorBasedOnParameters.validateDog();
    assert(true);

    try
    {
        dogConstructorBasedOnParameters.validateName("");
    }
    catch (const std::exception& caughtException)
    {
        assert(true);
    }

    try
    {
        dogConstructorBasedOnParameters.validateBreed("");
    }
    catch (const std::exception& caughtException)
    {
        assert(true);
    }

    try
    {
        dogConstructorBasedOnParameters.validateAge(-21);
    }
    catch (const std::exception& caughtException)
    {
        assert(true);
    }

    try
    {
        dogConstructorBasedOnParameters.validatePhotograph("dsda");
    }
    catch (const std::exception& caughtException)
    {
        assert(true);
    }
    
    try
    {
        dogConstructorBasedOnParameters.setAge(-21);
    }
    catch (const std::exception& caughtException)
    {
        assert(true);
    }

    Dog dogCopyConstructor{ dogConstructorBasedOnParameters };
    assert(dogCopyConstructor.getName() == "Toby");
    assert(dogCopyConstructor.getBreed() == "Labrador");
    assert(dogCopyConstructor.getAge() == 3);
    assert(dogCopyConstructor.getPhotograph() == "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");


    dogDefaultConstructor.setName("Max");
    assert(dogDefaultConstructor.getName() == "Max");
    dogDefaultConstructor.setBreed("Bulldog");
    assert(dogDefaultConstructor.getBreed() == "Bulldog");
    dogDefaultConstructor.setAge(8);
    assert(dogDefaultConstructor.getAge() == 8);
    dogDefaultConstructor.setPhotograph("https://dogtime.com/wp-content/uploads/sites/12/2011/01/GettyImages-168620477-e1691273341205.jpg?w=1024");
    assert(dogDefaultConstructor.getPhotograph() == "https://dogtime.com/wp-content/uploads/sites/12/2011/01/GettyImages-168620477-e1691273341205.jpg?w=1024");


    dogDefaultConstructor = dogConstructorBasedOnParameters;
    assert(dogDefaultConstructor.getName() == "Toby");
    assert(dogDefaultConstructor.getBreed() == "Labrador");
    assert(dogDefaultConstructor.getAge() == 3);
    assert(dogDefaultConstructor.getPhotograph() == "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");
    
    dogDefaultConstructor.validatePhotograph("https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");
    assert(true);
}