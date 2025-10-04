from src.repository.ComplexNumberMemoryRepository import ComplexNumberMemoryRepository
from src.domain.ComplexNumber import ComplexNumber
import json
import os

NULL_VALUE = 0


class ComplexNumberJSONRepository(ComplexNumberMemoryRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__filename = file_name
        self.__initialise_complex_number_file()
        self.__load_complex_number_file()

    def reset_json_file(self):
        json_output_file = open(self.__filename, "w")
        json_output_file.write("{}")
        json_output_file.close()

    def erase_data(self):
        super().erase_data()
        self.reset_json_file()

    def __initialise_complex_number_file(self):
        file_size = os.path.getsize(self.__filename)
        if file_size == NULL_VALUE:
            self.reset_json_file()

    def __load_complex_number_file(self):
        complex_numbers_json_format = {}
        try:
            json_input_file = open(self.__filename)
            complex_numbers_json_format = json.load(json_input_file)
            json_input_file.close()
        except IOError:
            pass

        for complex_number in complex_numbers_json_format:
            new_complex_number = ComplexNumber(complex_number["_ComplexNumber__real_part_of_the_complex_number"],
                                               complex_number["_ComplexNumber__imaginary_part_of_the_complex_number"])
            super().add_new_complex_number(new_complex_number)

    def __save_complex_number_file(self):
        list_of_complex_numbers = []
        json_output_file = open(self.__filename, "w")
        for complex_numbers in self.get_list_of_complex_numbers():
            list_of_complex_numbers.append(complex_numbers.__dict__)
        json.dump(list_of_complex_numbers, json_output_file, indent=1)
        json_output_file.close()

    def add_new_complex_number(self, complex_number):
        """
        A function that gets a complex number and adds it to the existing list of complex numbers - JSON File Repository.
        :param complex_number: ComplexNumber
        :return: None
        """
        super().add_new_complex_number(complex_number)
        self.__save_complex_number_file()

    def filter_list_of_complex_numbers(self, start_position_ot_the_range: int, end_position_of_the_range: int):
        super().filter_list_of_complex_numbers(start_position_ot_the_range, end_position_of_the_range)
        self.__save_complex_number_file()