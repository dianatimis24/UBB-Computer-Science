from src.repository.ComplexNumberMemoryRepository import ComplexNumberMemoryRepository, RepositoryError
from src.domain.ComplexNumber import ComplexNumber
from pdoc import pdoc

INDEX_OF_THE_REAL_PART_OF_THE_COMPLEX_NUMBER = 0
INDEX_OF_THE_IMAGINARY_PART_OF_THE_COMPLEX_NUMBER = 1


class ComplexNumberTextFileRepository(ComplexNumberMemoryRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__filename = file_name
        try:
            self.__load_complex_numbers_text_file()
        except FileNotFoundError:
            raise RepositoryError("The file was not found.")
        except Exception:
           raise RepositoryError("Something went wrong. Try again!")

    def __load_complex_numbers_text_file(self):
        """
        A function that loads a list of Complex Numbers with the content from a text file.
        :return: None
        """
        lines_from_text_file = []
        try:
            text_file_input = open(self.__filename, "rt")
            lines_from_text_file = text_file_input.readlines()
            text_file_input.close()
        except:
            raise ValueError("Load file incomplete.")

        for line in lines_from_text_file:
            current_line = line.split(", ")
            new_complex_number = ComplexNumber(int(current_line[INDEX_OF_THE_REAL_PART_OF_THE_COMPLEX_NUMBER].strip()),
                                               int(current_line[INDEX_OF_THE_IMAGINARY_PART_OF_THE_COMPLEX_NUMBER].strip()))
            super().add_new_complex_number(new_complex_number)

    def __save_to_text_file(self):
        """
        A function that saves in a text file the content of the list of Complex Numbers.
        :return: None
        """
        text_output_file = open(self.__filename, "wt")
        for complex_number in self.get_list_of_complex_numbers():
            text_output_file.write(str(complex_number.real_part_of_the_complex_number) + ", "
                                   + str(complex_number.imaginary_part_of_the_complex_number) + "\n")
        text_output_file.close()

    def erase_data(self):
        """
        A function that clears the initial list of Complex Numbers.
        :return: None
        """
        super().erase_data()
        open(self.__filename, "w").close()

    def add_new_complex_number(self, complex_number):
        """
        A function that gets a complex number and adds it to the existing list of complex numbers - Text File Repository.
        :param complex_number: ComplexNumber
        :return: None
        """
        super().add_new_complex_number(complex_number)
        self.__save_to_text_file()

    def filter_list_of_complex_numbers(self, start_position_ot_the_range: int, end_position_of_the_range: int):
        """
        A function that filters a range, using its start position and its end position, from the initial list of Complex Numbers.
        :param start_position_ot_the_range: int (integer) - start position of the filtered range
        :param end_position_of_the_range: int (integer) - end position of the filtered range
        :return: List of ComplexNumber - the filtered list of Complex Numbers
        """
        super().filter_list_of_complex_numbers(start_position_ot_the_range, end_position_of_the_range)
        self.__save_to_text_file()


if __name__=="__main__":
    documentation = open("TextFileRepositoryDocumentation.html", "wt")
    documentation.write(pdoc("ComplexNumberTextFileRepository.py", " "))
    documentation.close()