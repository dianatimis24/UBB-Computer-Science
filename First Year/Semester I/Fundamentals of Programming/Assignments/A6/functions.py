#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print
# statements. Functions here communicate via function parameters, the return statement and raising of exceptions.
#
from texttable import Texttable
from constants import (LOWER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER, UPPER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER, INITIALIZATION_VALUE_ZERO, \
                       NULL_VALUE, CONSTANT_VALUE_TEN_FOR_MULTIPLICATION_IN_ORDER_TO_OBTAIN_AN_INTEGER, INCREMENTATION_VALUE_ONE)
from math import sqrt
import random
from pdoc import pdoc


def create_complex_number(the_real_part_of_the_complex_number: int, the_imaginary_part_of_the_number: int) -> dict:
    """
    A function that creates a complex number using the dictionary representation.
    :param the_real_part_of_the_complex_number: integer (int) - the real part of the complex number
    :param the_imaginary_part_of_the_number: integer (int) - the imaginary part of the complex number
    :return:
    """
    return {"the_real_part_of_the_complex_number": the_real_part_of_the_complex_number,
            "the_imaginary_part_of_the_complex_number": the_imaginary_part_of_the_number}


def get_the_real_part_of_a_complex_number(complex_number: dict) -> int:
    return complex_number["the_real_part_of_the_complex_number"]


def get_the_imaginary_part_of_a_complex_number(complex_number: dict) -> int:
    return complex_number["the_imaginary_part_of_the_complex_number"]


def set_the_real_part_of_a_complex_number(complex_number: dict, value_for_the_real_part_of_a_complex_number: int):
    complex_number["the_real_part_of_the_complex_number"] = value_for_the_real_part_of_a_complex_number


def set_the_imaginary_part_of_a_complex_number(complex_number: dict, value_for_the_imaginary_part_of_a_complex_number: int):
    complex_number["the_imaginary_part_of_the_complex_number"] = value_for_the_imaginary_part_of_a_complex_number


def compute_the_modulus_of_a_complex_number(complex_number: dict) -> int:
    """
    A function that computes the modulus of a complex number.
    :param complex_number: dictionary
    :return: integer (int) - the modulus of the given complex number
    """
    return int(sqrt(
        get_the_real_part_of_a_complex_number(complex_number) * get_the_real_part_of_a_complex_number(complex_number) +
        get_the_imaginary_part_of_a_complex_number(complex_number) * get_the_imaginary_part_of_a_complex_number(
            complex_number)))


def transform_a_complex_number_into_string(complex_number: dict) -> str:
    """
    A function that transforms a complex number into a string.
    :param complex_number:  dictionary
    :return: string representing the given complex number
    """
    if get_the_real_part_of_a_complex_number(complex_number) == NULL_VALUE:
        return f"{get_the_imaginary_part_of_a_complex_number(complex_number)}i"

    if get_the_imaginary_part_of_a_complex_number(complex_number) == NULL_VALUE:
        return f"{get_the_real_part_of_a_complex_number(complex_number)}"

    if get_the_imaginary_part_of_a_complex_number(complex_number) > NULL_VALUE:
        return (f"{get_the_real_part_of_a_complex_number(complex_number)}+"
                f"{get_the_imaginary_part_of_a_complex_number(complex_number)}i")
    else:
        return (f"{get_the_real_part_of_a_complex_number(complex_number)}-"
                f"{abs(get_the_imaginary_part_of_a_complex_number(complex_number))}i")


def transform_a_string_into_a_complex_number(given_string_representing_a_complex_number: str) -> dict:
    """
    A function that transforms the string representation of a complex number into a complex number.
    :param given_string_representing_a_complex_number: string
    :return: dictionary - the complex number
    """
    position_in_the_given_string = INITIALIZATION_VALUE_ZERO
    the_real_part_of_the_complex_number = INITIALIZATION_VALUE_ZERO
    the_imaginary_part_of_the_complex_number = INITIALIZATION_VALUE_ZERO
    current_computation = INITIALIZATION_VALUE_ZERO

    if given_string_representing_a_complex_number[position_in_the_given_string] == "-":
        position_in_the_given_string += INCREMENTATION_VALUE_ONE
        while position_in_the_given_string < len(given_string_representing_a_complex_number) and "0" <= given_string_representing_a_complex_number[position_in_the_given_string] <= "9":
            current_computation = current_computation * CONSTANT_VALUE_TEN_FOR_MULTIPLICATION_IN_ORDER_TO_OBTAIN_AN_INTEGER + int(given_string_representing_a_complex_number[position_in_the_given_string])
            position_in_the_given_string += INCREMENTATION_VALUE_ONE
        current_computation = -current_computation
    else:
        while position_in_the_given_string < len(given_string_representing_a_complex_number) and "0" <= given_string_representing_a_complex_number[position_in_the_given_string] <= "9":
            current_computation = current_computation * CONSTANT_VALUE_TEN_FOR_MULTIPLICATION_IN_ORDER_TO_OBTAIN_AN_INTEGER + int(given_string_representing_a_complex_number[position_in_the_given_string])
            position_in_the_given_string += INCREMENTATION_VALUE_ONE

    if position_in_the_given_string == len(given_string_representing_a_complex_number):
        the_real_part_of_the_complex_number = current_computation
        the_imaginary_part_of_the_complex_number = NULL_VALUE
    elif given_string_representing_a_complex_number[position_in_the_given_string] == "i":
        the_real_part_of_the_complex_number = NULL_VALUE
        the_imaginary_part_of_the_complex_number = current_computation
    else:
        the_real_part_of_the_complex_number = current_computation
        current_computation = INITIALIZATION_VALUE_ZERO
        if given_string_representing_a_complex_number[position_in_the_given_string] == "+":
            position_in_the_given_string += INCREMENTATION_VALUE_ONE
            while "0" <= given_string_representing_a_complex_number[position_in_the_given_string] <= "9":
                current_computation = current_computation * CONSTANT_VALUE_TEN_FOR_MULTIPLICATION_IN_ORDER_TO_OBTAIN_AN_INTEGER + int(given_string_representing_a_complex_number[position_in_the_given_string])
                position_in_the_given_string += INCREMENTATION_VALUE_ONE
        elif given_string_representing_a_complex_number[position_in_the_given_string] == "-":
            position_in_the_given_string += INCREMENTATION_VALUE_ONE
            while "0" <= given_string_representing_a_complex_number[position_in_the_given_string] <= "9":
                current_computation = current_computation * CONSTANT_VALUE_TEN_FOR_MULTIPLICATION_IN_ORDER_TO_OBTAIN_AN_INTEGER + int(given_string_representing_a_complex_number[position_in_the_given_string])
                position_in_the_given_string += INCREMENTATION_VALUE_ONE
            current_computation = -current_computation
        the_imaginary_part_of_the_complex_number = current_computation

    return create_complex_number(the_real_part_of_the_complex_number, the_imaginary_part_of_the_complex_number)


def add_a_complex_number_to_the_end_of_a_list_of_complex_numbers(list_of_complex_numbers : list, given_complex_number : dict) -> tuple:
    """
    A function that adds a given complex number to a list of complex numbers.
    :param list_of_complex_numbers: list of dictionaries
    :param given_complex_number: dictionary
    :return: tuple, list of dictionaries representing the new list of complex numbers
                    list of dictionaries representing the old list of complex numbers
    """
    current_operation = list_of_complex_numbers.copy()
    list_of_complex_numbers.append(given_complex_number)
    return list_of_complex_numbers, current_operation


def insert_a_complex_number_to_a_given_position_in_a_list_of_complex_numbers(list_of_complex_numbers : list, given_complex_number : dict, given_position : int) -> tuple:
    """
    A function that inserts a given complex number in a list of complex numbers to a given position.
    :param list_of_complex_numbers: list of dictionaries
    :param given_complex_number: dictionary
    :param given_position: integer (int) - the position where the given_complex_number is inserted
    :return: tuple, list of dictionaries representing the new list of complex numbers
                    list of dictionaries representing the old list of complex numbers
    """
    current_operation = list_of_complex_numbers.copy()
    list_of_complex_numbers.insert(given_position, given_complex_number)
    return list_of_complex_numbers, current_operation


def remove_a_complex_number_from_a_given_position_from_a_list_of_complex_numbers(list_of_complex_numbers : list, given_position : int) -> tuple:
    """
    A function that removes a complex number from a list from a given position.
    :param list_of_complex_numbers: list of dictionaries
    :param given_position: integer (int) - the position of the removed complex number
    :return: tuple, list of dictionaries representing the new list of complex numbers
                    list of dictionaries representing the old list of complex numbers
    """
    current_operation = list_of_complex_numbers.copy()
    list_of_complex_numbers.pop(given_position)
    return list_of_complex_numbers, current_operation


def remove_a_given_range_of_complex_numbers_from_a_list_of_complex_numbers(list_of_complex_numbers : list, start_position_of_the_range : int, end_position_of_the_range : int) -> tuple:
    """
    A function that removes a range of complex numbers from a list between two a given positions.
    :param list_of_complex_numbers: list of dictionaries
    :param start_position_of_the_range: integer (int) - the position of the first removed complex number
    :param end_position_of_the_range: integer (int) - the position of the last removed complex number
    :return: tuple, list of dictionaries representing the new list of complex numbers
                    list of dictionaries representing the old list of complex numbers
    """
    current_operation = list_of_complex_numbers.copy()
    del list_of_complex_numbers[start_position_of_the_range : end_position_of_the_range + 1]
    return list_of_complex_numbers, current_operation


def replace_all_the_occurrences_of_a_complex_number_from_a_list_of_complex_numbers_with_a_given_complex_number(list_of_complex_numbers : list, old_complex_number : dict, given_complex_number : dict) -> tuple:
    """
    A function that replaces a complex number with another given complex number.
    :param list_of_complex_numbers: list of dictionaries
    :param old_complex_number: dictionary - the element replaced
    :param given_complex_number: dictionary - the element that replaces the previous one
    :return: tuple, list of dictionaries representing the new list of complex numbers
                    list of dictionaries representing the old list of complex numbers
    """
    current_operation = list_of_complex_numbers.copy()
    for i in range(len(list_of_complex_numbers)):
        if (get_the_real_part_of_a_complex_number(list_of_complex_numbers[i]) == get_the_real_part_of_a_complex_number(old_complex_number)
                and get_the_imaginary_part_of_a_complex_number(list_of_complex_numbers[i]) == get_the_imaginary_part_of_a_complex_number(old_complex_number)):
            set_the_real_part_of_a_complex_number(list_of_complex_numbers[i], get_the_real_part_of_a_complex_number(given_complex_number))
            set_the_imaginary_part_of_a_complex_number(list_of_complex_numbers[i], get_the_imaginary_part_of_a_complex_number(given_complex_number))

    return list_of_complex_numbers, current_operation


def display_a_list_of_complex_numbers(list_of_complex_numbers : list) -> list:
    """
    A function that creates a list of the complex numbers that will be displayed.
    :param list_of_complex_numbers: list of dictionaries
    :return: list of dictionaries
    """
    list_of_complex_numbers_to_be_displayed = []
    for i in range(len(list_of_complex_numbers)):
        list_of_complex_numbers_to_be_displayed.append(list_of_complex_numbers[i])
    return list_of_complex_numbers_to_be_displayed


def display_the_real_numbers_from_a_given_range_from_a_list_of_complex_numbers(list_of_complex_numbers : list, start_position_of_the_range : int, end_position_of_the_range : int) -> list:
    """
    A function that creates from a given range from a list of complex numbers a list of the real numbers that will be displayed.
    :param list_of_complex_numbers: list of dictionaries
    :param start_position_of_the_range: integer (int) - the position of the first checked complex number
    :param end_position_of_the_range: integer (int) - the position of the last checked complex number
    :return: list of dictionaries
    """
    list_of_complex_numbers_to_be_displayed = []
    for i in range(start_position_of_the_range, end_position_of_the_range + 1):
        if get_the_imaginary_part_of_a_complex_number(list_of_complex_numbers[i]) == NULL_VALUE:
            list_of_complex_numbers_to_be_displayed.append(list_of_complex_numbers[i])
    return list_of_complex_numbers_to_be_displayed


def display_the_numbers_from_a_list_of_complex_numbers_whose_modulus_is_compared_to_a_given_number(list_of_complex_numbers : list, given_number_for_comparison : dict, comparison_symbol : str) -> list:
    """
    A function that creates a list of the complex numbers whose modulus is less, greater or equal to the modulus of a given complex number, that will be displayed.
    :param list_of_complex_numbers: list of dictionaries
    :param given_number_for_comparison: dictionary - complex number
    :param comparison_symbol: < | = | >
    :return: list of dictionaries
    """
    list_of_complex_numbers_to_be_displayed = []
    if comparison_symbol == "<":
        for i in range(len(list_of_complex_numbers)):
            if compute_the_modulus_of_a_complex_number(list_of_complex_numbers[i]) < compute_the_modulus_of_a_complex_number(given_number_for_comparison):
                list_of_complex_numbers_to_be_displayed.append(list_of_complex_numbers[i])
    elif comparison_symbol == ">":
        for i in range(len(list_of_complex_numbers)):
            if compute_the_modulus_of_a_complex_number(list_of_complex_numbers[i]) > compute_the_modulus_of_a_complex_number(given_number_for_comparison):
                list_of_complex_numbers_to_be_displayed.append(list_of_complex_numbers[i])
    elif comparison_symbol == "=":
        for i in range(len(list_of_complex_numbers)):
            if compute_the_modulus_of_a_complex_number(list_of_complex_numbers[i]) == compute_the_modulus_of_a_complex_number(given_number_for_comparison):
                list_of_complex_numbers_to_be_displayed.append(list_of_complex_numbers[i])
    return list_of_complex_numbers_to_be_displayed


def filter_a_list_of_complex_numbers_keeping_only_the_real_numbers(list_of_complex_numbers : list) -> list:
    """
    A function that creates a list of the real numbers from a list of complex numbers.
    :param list_of_complex_numbers: list of dictionaries
    :return: list of dictionaries
    """
    filtered_list_of_complex_numbers = []
    for i in range(len(list_of_complex_numbers)):
        if get_the_imaginary_part_of_a_complex_number(list_of_complex_numbers[i]) == NULL_VALUE:
            filtered_list_of_complex_numbers.append(list_of_complex_numbers[i])

    return filtered_list_of_complex_numbers


def filter_a_list_of_complex_numbers_keeping_only_the_numbers_whose_modulus_is_compared_to_a_given_number(list_of_complex_numbers : list, given_number_for_comparison : dict, comparison_symbol : str) -> list:
    """
     A function that creates a list of the complex numbers whose modulus is less, greater or equal to the modulus of a given complex number.
    :param list_of_complex_numbers: list of dictionaries
    :param given_number_for_comparison: dictionary - complex number
    :param comparison_symbol: < | = | >
    :return: list of dictionaries
    """
    filtered_list_of_complex_numbers = []
    if comparison_symbol == "<":
        for i in range(len(list_of_complex_numbers)):
            if compute_the_modulus_of_a_complex_number(list_of_complex_numbers[i]) < compute_the_modulus_of_a_complex_number(given_number_for_comparison):
                filtered_list_of_complex_numbers.append(list_of_complex_numbers[i])
    elif comparison_symbol == ">":
        for i in range(len(list_of_complex_numbers)):
            if compute_the_modulus_of_a_complex_number(list_of_complex_numbers[i]) > compute_the_modulus_of_a_complex_number(given_number_for_comparison):
                filtered_list_of_complex_numbers.append(list_of_complex_numbers[i])
    elif comparison_symbol == "=":
        for i in range(len(list_of_complex_numbers)):
            if compute_the_modulus_of_a_complex_number(list_of_complex_numbers[i]) == compute_the_modulus_of_a_complex_number(given_number_for_comparison):
                filtered_list_of_complex_numbers.append(list_of_complex_numbers[i])

    return filtered_list_of_complex_numbers


def undo_the_last_operation_done_on_a_list_of_complex_numbers(list_of_complex_numbers : list, history_of_done_operations : list) -> tuple:
    """
    A function that undoes the last operation done on a list of complex numbers.
    :param list_of_complex_numbers: list of dictionaries - the list of complex numbers
    :param history_of_done_operations: list of list of dictionaries - the list of the list of complex numbers before the last operation
    :return: tuple, list of dictionaries - the list of complex numbers after the undo operation (before the last operation)
                    list of list of dictionaries, without the operation that was undone
    """
    list_of_complex_numbers = history_of_done_operations.pop()

    return list_of_complex_numbers, history_of_done_operations


def generate_a_list_of_complex_numbers(number_of_complex_numbers_to_be_generated : int) -> list:
    """
    A function that generates a list of random complex numbers.
    :param number_of_complex_numbers_to_be_generated: the number of the generated complex numbers of the list
    :return: list of dictionaries - a list of complex numbers
    """
    list_of_complex_numbers = []
    for i in range(number_of_complex_numbers_to_be_generated):
        list_of_complex_numbers.append(
            create_complex_number(random.randint(LOWER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER, UPPER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER),
                                  random.randint(LOWER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER, UPPER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER)))
    return list_of_complex_numbers


def build_a_table_from_a_list_of_complex_numbers(list_of_complex_numbers : list):
    """
    A function that creates a table from a given list of complex Numbers.
    :param list_of_complex_numbers: list of dictionaries - the list of complex numbers
    :return: the table containing the complex numbers
    """
    table_with_complex_numbers = Texttable()
    table_with_complex_numbers.add_row(["The Complex Number", "The Real Part of the Complex Number", "The Imaginary Part of the Complex Number"])
    for i in range(len(list_of_complex_numbers)):
        table_with_complex_numbers.add_row([transform_a_complex_number_into_string(list_of_complex_numbers[i]),
                                            get_the_real_part_of_a_complex_number(list_of_complex_numbers[i]),
                                            get_the_imaginary_part_of_a_complex_number(list_of_complex_numbers[i])])
    return table_with_complex_numbers


if __name__ == "__main__":
    documentation = open("Documentation_assignment6.html", "wt")
    documentation.write(pdoc("functions.py", " "))
    documentation.close()