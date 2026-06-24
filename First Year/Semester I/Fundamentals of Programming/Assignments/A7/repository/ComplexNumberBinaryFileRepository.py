from src.repository.ComplexNumberMemoryRepository import ComplexNumberMemoryRepository, RepositoryError
import pickle
from pdoc import pdoc


class ComplexNumberBinaryRepository(ComplexNumberMemoryRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__filename = file_name
        try:
            self.__load_complex_numbers_binary_file()
        except FileNotFoundError:
            raise RepositoryError("The file was not found.")
        except Exception:
            raise RepositoryError("Something went wrong. Try again!")

    def __load_complex_numbers_binary_file(self):
        """
        A function that loads a list of Complex Numbers with the content from a binary file.
        :return: None
        """
        try:
            binary_file_input = open(self.__filename, "rb")
            complex_numbers_from_binary_file = pickle.load(binary_file_input)
        except EOFError:
            return

        for complex_number in complex_numbers_from_binary_file:
            super().add_new_complex_number(complex_number)
        binary_file_input.close()

    def __save_to_binary_file(self):
        """
        A function that saves in a binary file the content of the list of Complex Numbers.
        :return: None
        """
        binary_output_file = open(self.__filename, "wb")
        pickle.dump(self.get_list_of_complex_numbers(), binary_output_file)
        binary_output_file.close()

    def erase_data(self):
        """
        A function that clears the initial list of Complex Numbers.
        :return: None
        """
        super().erase_data()
        open(self.__filename, "w").close()

    def add_new_complex_number(self, complex_number):
        """
        A function that gets a complex number and adds it to the existing list of complex numbers - Binary File Repository.
        :param complex_number: ComplexNumber
        :return: None
        """
        super().add_new_complex_number(complex_number)
        self.__save_to_binary_file()

    def filter_list_of_complex_numbers(self, start_position_ot_the_range: int, end_position_of_the_range: int):
        """
        A function that filters a range, using its start position and its end position, from the initial list of Complex Numbers.
        :param start_position_ot_the_range: int (integer) - start position of the filtered range
        :param end_position_of_the_range: int (integer) - end position of the filtered range
        :return: List of ComplexNumber - the filtered list of Complex Numbers
        """
        super().filter_list_of_complex_numbers(start_position_ot_the_range, end_position_of_the_range)
        self.__save_to_binary_file()


if __name__=="__main__":
    documentation = open("BinaryFileRepositoryDocumentation.html", "wt")
    documentation.write(pdoc("ComplexNumberBinaryFileRepository.py", " "))
    documentation.close()
