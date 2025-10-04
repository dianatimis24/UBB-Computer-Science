import random
from src.domain.ComplexNumber import ComplexNumber
from src.repository.ComplexNumberTextFileRepository import ComplexNumberTextFileRepository

LOWER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER = -1000
UPPER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER = 1000
NUMBER_OF_COMPLEX_NUMBERS_AVAILABLE_AT_PROGRAM_STARTUP = 10
EMPTY_LIST_OF_PERFORMED_OPERATIONS = 0


class ComplexNumberService:
    def __init__(self, repository):
        self.__repository = repository
        self.__history_of_performed_operations = []
        if (len(self.__repository)) < NUMBER_OF_COMPLEX_NUMBERS_AVAILABLE_AT_PROGRAM_STARTUP:
            self.generate_a_list_of_random_complex_numbers()

    def generate_a_list_of_random_complex_numbers(self):
        for i in range(NUMBER_OF_COMPLEX_NUMBERS_AVAILABLE_AT_PROGRAM_STARTUP):
            self.__repository.add_new_complex_number(ComplexNumber(random.randint(LOWER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER, UPPER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER),
                                                     random.randint(LOWER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER, UPPER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER)))

    def clear_list_of_complex_numbers(self):
        self.__repository.erase_data()

    def get_list_of_complex_numbers(self):
        return self.__repository.get_list_of_complex_numbers()

    def add_complex_number(self, real_part_of_the_complex_number: int, imaginary_part_of_the_complex_number: int):
        """
        A function that gets two integers, representing the real part and the imaginary part of a complex number,
        creates a complex numbers and adds it to the existing list of complex numbers.
        :param real_part_of_the_complex_number: int (integer) - the real part of the new complex number
        :param imaginary_part_of_the_complex_number: int (integer) - the imaginary part of the new complex number
        :return: None
        """
        new_complex_number = ComplexNumber(real_part_of_the_complex_number, imaginary_part_of_the_complex_number)
        self.__history_of_performed_operations.append(self.__repository.get_list_of_complex_numbers()[:])
        self.__repository.add_new_complex_number(new_complex_number)

    def filter_list_of_complex_numbers(self, start_position_ot_the_range: int, end_position_of_the_range: int):
        self.__history_of_performed_operations.append(self.__repository.get_list_of_complex_numbers()[:])
        self.__repository.filter_list_of_complex_numbers(start_position_ot_the_range, end_position_of_the_range)

    def undo_last_performed_operation(self):
        if len(self.__history_of_performed_operations) != EMPTY_LIST_OF_PERFORMED_OPERATIONS:
            last_operation_performed = self.__history_of_performed_operations.pop()
            self.clear_list_of_complex_numbers()
            for complex_number in last_operation_performed:
                self.__repository.add_new_complex_number(complex_number)
        else:
            raise Exception("There are no more operations to be undone.")
