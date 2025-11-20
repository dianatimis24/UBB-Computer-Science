from src.services.ComplexNumberService import ComplexNumberService

ADD_A_COMPLEX_NUMBER_TO_THE_LIST_OF_NUMBERS = 1
DISPLAY_THE_LIST_OF_COMPLEX_NUMBERS = 2
FILTER_A_RANGE_FROM_A_LIST_OF_COMPLEX_NUMBERS = 3
UNDO_THE_LAST_PERFORMED_OPERATION = 4
EXIT_THE_MENU = 0


class UI:
    def __init__(self, repository):
        self.__complex_number_service = ComplexNumberService(repository)

    def print_menu(self):
        print(str(ADD_A_COMPLEX_NUMBER_TO_THE_LIST_OF_NUMBERS) + ". Add a Complex Number to the list.")
        print(str(DISPLAY_THE_LIST_OF_COMPLEX_NUMBERS) + ". Display the list of Complex Numbers.")
        print(str(FILTER_A_RANGE_FROM_A_LIST_OF_COMPLEX_NUMBERS) + ". Filter a range from the list of ComplexNumbers.")
        print(str(UNDO_THE_LAST_PERFORMED_OPERATION) + ". Undo the last performed operation.")
        print(str(EXIT_THE_MENU) + ". Exit the menu.")

    def print_user_interface(self):
        while True:
            self.print_menu()
            try:
                user_option = int(input("Choose an option from the list above: "))
                if user_option == ADD_A_COMPLEX_NUMBER_TO_THE_LIST_OF_NUMBERS:
                    real_part_of_the_complex_number = int(input("Introduce the real part of the complex number: "))
                    imaginary_part_of_the_complex_number = int(input("Introduce the imaginary part of the complex number: "))
                    self.__complex_number_service.add_complex_number(real_part_of_the_complex_number, imaginary_part_of_the_complex_number)

                elif user_option == DISPLAY_THE_LIST_OF_COMPLEX_NUMBERS:
                    list_of_complex_numbers = self.__complex_number_service.get_list_of_complex_numbers()
                    for complex_number in list_of_complex_numbers:
                        print(str(complex_number))

                elif user_option == FILTER_A_RANGE_FROM_A_LIST_OF_COMPLEX_NUMBERS:
                    start_position_of_the_range = int(input("Introduce the start position of the range: "))
                    end_position_of_the_range = int(input("Introduce the end position of the range: "))
                    self.__complex_number_service.filter_list_of_complex_numbers(start_position_of_the_range, end_position_of_the_range)

                elif user_option == UNDO_THE_LAST_PERFORMED_OPERATION:
                    try:
                        self.__complex_number_service.undo_last_performed_operation()
                    except Exception as exception_message:
                        print(exception_message)

                elif user_option == EXIT_THE_MENU:
                    print("Goodbye!")
                    break
                else:
                    print("Choose a valid option from the list.")
            except ValueError:
                print("Invalid input")
