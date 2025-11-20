from dataclasses import dataclass

NULL_VALUE = 0

@dataclass
class ComplexNumber:
    def __init__(self, real_part_of_the_complex_number: int, imaginary_part_of_the_complex_number: int):
        self.__real_part_of_the_complex_number = real_part_of_the_complex_number
        self.__imaginary_part_of_the_complex_number = imaginary_part_of_the_complex_number

    @property
    def real_part_of_the_complex_number(self):
        return self.__real_part_of_the_complex_number

    @property
    def imaginary_part_of_the_complex_number(self):
        return self.__imaginary_part_of_the_complex_number

    def __str__(self):
        if self.__real_part_of_the_complex_number == NULL_VALUE:
            return f"{self.__imaginary_part_of_the_complex_number}i"

        if self.__imaginary_part_of_the_complex_number == NULL_VALUE:
            return f"{self.__real_part_of_the_complex_number}"

        if self.__imaginary_part_of_the_complex_number > NULL_VALUE:
            return (f"{self.__real_part_of_the_complex_number}+"
                    f"{self.__imaginary_part_of_the_complex_number}i")
        else:
            return (f"{self.__real_part_of_the_complex_number}-"
                    f"{abs(self.__imaginary_part_of_the_complex_number)}i")
