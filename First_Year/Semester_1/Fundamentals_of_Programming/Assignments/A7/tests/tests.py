from src.services.ComplexNumberService import ComplexNumberService


class Test:
    def __init__(self, repository):
        self.complex_number_service = ComplexNumberService(repository)

    def test_add_a_complex_number_to_a_list(self):
        initial_length_of_the_list_of_complex_numbers = len(self.complex_number_service.get_list_of_complex_numbers())
        self.complex_number_service.add_complex_number(24, -30)
        assert (len(self.complex_number_service.get_list_of_complex_numbers()) ==
                initial_length_of_the_list_of_complex_numbers + 1)

        self.complex_number_service.add_complex_number(-324, 356)
        assert (len(self.complex_number_service.get_list_of_complex_numbers()) ==
                initial_length_of_the_list_of_complex_numbers + 2)

        self.complex_number_service.add_complex_number(-2400, -900)
        assert (len(self.complex_number_service.get_list_of_complex_numbers()) ==
                initial_length_of_the_list_of_complex_numbers + 3)

        self.complex_number_service.add_complex_number(50, 40)
        assert (len(self.complex_number_service.get_list_of_complex_numbers()) ==
                initial_length_of_the_list_of_complex_numbers + 4)
