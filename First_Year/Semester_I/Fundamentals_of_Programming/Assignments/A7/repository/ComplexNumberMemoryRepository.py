from src.domain.ComplexNumber import ComplexNumber
from pdoc import pdoc


class RepositoryError(Exception):
    def __init__(self, error_message):
        self.__error_message = error_message

    def __str__(self):
        return "Repository Error: " + self.__error_message


class ComplexNumberMemoryRepository:
    def __init__(self):
        self._all_complex_numbers_data = []

    def erase_data(self):
        """
        A function that clears the initial list of Complex Numbers.
        :return: None
        """
        self._all_complex_numbers_data.clear()

    def add_new_complex_number(self, complex_number: ComplexNumber):
        """
        A function that gets a complex number and adds it to the existing list of complex numbers - Memory Repository.
        :param complex_number: ComplexNumber
        :return: None
        """
        self._all_complex_numbers_data.append(complex_number)

    def get_list_of_complex_numbers(self):
        """
        A function that returns the initial list of Complex Numbers.
        :return: List of ComplexNumber
        """
        return self._all_complex_numbers_data

    def filter_list_of_complex_numbers(self, start_position_ot_the_range: int, end_position_of_the_range: int):
        """
        A function that filters a range, using its start position and its end position, from the initial list of Complex Numbers.
        :param start_position_ot_the_range: int (integer) - start position of the filtered range
        :param end_position_of_the_range: int (integer) - end position of the filtered range
        :return: List of ComplexNumber - the filtered list of Complex Numbers
        """
        filtered_list_of_complex_numbers = self._all_complex_numbers_data[start_position_ot_the_range:(end_position_of_the_range + 1)]
        self._all_complex_numbers_data = filtered_list_of_complex_numbers
        return self._all_complex_numbers_data

    def __len__(self):
        return len(list(self._all_complex_numbers_data))


if __name__=="__main__":
    documentation = open("MemoryRepositoryDocumentation.html", "wt")
    documentation.write(pdoc("ComplexNumberMemoryRepository.py", " "))
    documentation.close()
