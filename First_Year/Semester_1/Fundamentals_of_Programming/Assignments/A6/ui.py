#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements)
# are found here.
#
from constants import NUMBER_OF_COMPLEX_NUMBERS_AVAILABLE_AT_PROGRAM_STARTUP, THE_OPTION_COMMAND, COMMAND_ADD_LENGTH, \
    COMMAND_ADD_THE_NUMBER_ADDED_TO_THE_LIST, COMMAND_INSERT_LENGTH, COMMAND_INSERT_THE_NUMBER_INSERTED_IN_THE_LIST, \
    COMMAND_INSERT_POSITION_WHERE_THE_NUMBER_IS_INSERTED, COMMAND_REMOVE_A_NUMBER_FROM_A_POSITION_LENGTH, \
    COMMAND_REMOVE_POSITION_OF_THE_REMOVED_NUMBER, COMMAND_REMOVE_A_RANGE_OF_NUMBERS_LENGTH, COMMAND_REMOVE_A_RANGE_OF_NUMBERS_START_POSITION, \
    COMMAND_REMOVE_A_RANGE_OF_NUMBERS_END_POSITION, COMMAND_REPLACE_A_NUMBER_LENGTH, COMMAND_REPLACE_OLD_NUMBER, COMMAND_REPLACE_NEW_NUMBER, \
    COMMAND_DISPLAY_LIST_LENGTH, COMMAND_DISPLAY_REAL_NUMBERS_LENGTH, COMMAND_DISPLAY_REAL_NUMBERS_START_POSITION, COMMAND_DISPLAY_REAL_NUMBERS_END_POSITION, \
    COMMAND_DISPLAY_MODULUS_COMPARISON_LENGTH, COMMAND_DISPLAY_MODULUS_COMPARISON_SYMBOL, COMMAND_DISPLAY_MODULUS_COMPARISON_NUMBER, \
    COMMAND_FILTER_REAL_NUMBERS_LENGTH, COMMAND_FILTER_MODULUS_COMPARISON_LENGTH, COMMAND_FILTER_MODULUS_COMPARISON_SYMBOL, \
    COMMAND_FILTER_MODULUS_COMPARISON_NUMBER, COMMAND_UNDO_LENGTH, NULL_VALUE
import functions


def process_command_add_a_complex_number_to_a_list_of_complex_numbers(given_command, list_of_complex_numbers, last_done_operation):
    if len(given_command) != COMMAND_ADD_LENGTH:
        print("This is an invalid command. The format of this command should be add <number>")
        return list_of_complex_numbers, last_done_operation
    try:
        current_complex_number = functions.transform_a_string_into_a_complex_number(given_command[COMMAND_ADD_THE_NUMBER_ADDED_TO_THE_LIST])
    except ValueError:
        print("The complex number has an invalid format.")
        return list_of_complex_numbers, last_done_operation

    list_of_complex_numbers, last_done_operation = functions.add_a_complex_number_to_the_end_of_a_list_of_complex_numbers(list_of_complex_numbers, current_complex_number)
    print(last_done_operation)
    return list_of_complex_numbers, last_done_operation


def process_command_insert_a_complex_number_to_a_given_position_in_a_list_of_complex_numbers(given_command, list_of_complex_numbers, last_done_operation):
    if len(given_command) != COMMAND_INSERT_LENGTH:
        print("This is an invalid command. The format of this command should be insert <number> at <position>")
        return list_of_complex_numbers, last_done_operation
    try:
        current_complex_number = functions.transform_a_string_into_a_complex_number(given_command[COMMAND_INSERT_THE_NUMBER_INSERTED_IN_THE_LIST])
        current_position = int(given_command[COMMAND_INSERT_POSITION_WHERE_THE_NUMBER_IS_INSERTED])
    except ValueError:
        print("The complex number or the position has an invalid format.")
        return list_of_complex_numbers, last_done_operation

    list_of_complex_numbers, last_done_operation = functions.insert_a_complex_number_to_a_given_position_in_a_list_of_complex_numbers(list_of_complex_numbers, current_complex_number, current_position)
    return list_of_complex_numbers, last_done_operation


def process_command_remove_a_complex_number_from_a_given_position_from_a_list_of_complex_numbers(given_command, list_of_complex_numbers, last_done_operation):
    if len(given_command) != COMMAND_REMOVE_A_NUMBER_FROM_A_POSITION_LENGTH:
        print("This is an invalid command. The format of this command should be remove <position>")
        return list_of_complex_numbers, last_done_operation
    try:
        current_position = int(given_command[COMMAND_REMOVE_POSITION_OF_THE_REMOVED_NUMBER])
    except ValueError:
        print("The position has an invalid format.")
        return list_of_complex_numbers, last_done_operation

    list_of_complex_numbers, last_done_operation = functions.remove_a_complex_number_from_a_given_position_from_a_list_of_complex_numbers(list_of_complex_numbers, current_position)
    return list_of_complex_numbers, last_done_operation


def process_command_remove_a_range_of_complex_numbers_from_a_list_of_complex_numbers(given_command, list_of_complex_numbers, last_done_operation):
    if len(given_command) != COMMAND_REMOVE_A_RANGE_OF_NUMBERS_LENGTH:
        print("This is an invalid command. The format of this command should be remove <start position> to <end position>")
        return list_of_complex_numbers, last_done_operation
    try:
        current_start_position = int(given_command[COMMAND_REMOVE_A_RANGE_OF_NUMBERS_START_POSITION])
        current_end_position = int(given_command[COMMAND_REMOVE_A_RANGE_OF_NUMBERS_END_POSITION])
    except ValueError:
        print("One of the positions has an invalid format.")
        return list_of_complex_numbers, last_done_operation

    list_of_complex_numbers, last_done_operation = functions.remove_a_given_range_of_complex_numbers_from_a_list_of_complex_numbers(list_of_complex_numbers, current_start_position, current_end_position)
    return list_of_complex_numbers, last_done_operation


def process_command_replace_all_the_occurrences_of_a_complex_number_with_another_complex_number_in_a_list_of_complex_numbers(given_command, list_of_complex_numbers, last_done_operation):
    if len(given_command) != COMMAND_REPLACE_A_NUMBER_LENGTH:
        print("This is an invalid command. The format of this command should be replace <old number> with <new number>")
        return list_of_complex_numbers, last_done_operation
    try:
        current_old_complex_number = functions.transform_a_string_into_a_complex_number(given_command[COMMAND_REPLACE_OLD_NUMBER])
        current_new_complex_number = functions.transform_a_string_into_a_complex_number(given_command[COMMAND_REPLACE_NEW_NUMBER])
    except ValueError:
        print("One of the complex numbers has an invalid format.")
        return list_of_complex_numbers, last_done_operation

    list_of_complex_numbers, last_done_operation = functions.replace_all_the_occurrences_of_a_complex_number_from_a_list_of_complex_numbers_with_a_given_complex_number(list_of_complex_numbers, current_old_complex_number, current_new_complex_number)
    return list_of_complex_numbers, last_done_operation


def process_command_display_a_list_of_complex_numbers(given_command, list_of_complex_numbers):
    if len(given_command) != COMMAND_DISPLAY_LIST_LENGTH:
        print("This is an invalid command. The format of this command should be list.")
        return

    list_of_complex_numbers = functions.display_a_list_of_complex_numbers(list_of_complex_numbers)
    table_list_of_complex_numbers = functions.build_a_table_from_a_list_of_complex_numbers(list_of_complex_numbers)
    print(table_list_of_complex_numbers.draw())
    print()


def process_command_display_the_real_numbers_from_a_list_of_complex_numbers(given_command, list_of_complex_numbers):
    if len(given_command) != COMMAND_DISPLAY_REAL_NUMBERS_LENGTH:
        print("This is an invalid command. The format of this command should be list real <start position> to <end position>.")
        return

    try:
        current_start_position = int(given_command[COMMAND_DISPLAY_REAL_NUMBERS_START_POSITION])
        current_end_position = int(given_command[COMMAND_DISPLAY_REAL_NUMBERS_END_POSITION])
    except ValueError:
        print("One of the positions has an invalid format.")
        return
    list_of_complex_numbers = functions.display_the_real_numbers_from_a_given_range_from_a_list_of_complex_numbers(list_of_complex_numbers, current_start_position, current_end_position)
    table_list_of_complex_numbers = functions.build_a_table_from_a_list_of_complex_numbers(list_of_complex_numbers)
    print(table_list_of_complex_numbers.draw())
    print()


def process_command_display_the_numbers_from_a_list_of_complex_numbers_whose_modulus_is_compared_to_a_given_number(given_command, list_of_complex_numbers):
    if len(given_command) != COMMAND_DISPLAY_MODULUS_COMPARISON_LENGTH:
        print("This is an invalid command. The format of this command should be list modulo [ < | = | > ] <number>.")
        return

    try:
        current_comparison_symbol = given_command[COMMAND_DISPLAY_MODULUS_COMPARISON_SYMBOL]
        current_complex_number = functions.transform_a_string_into_a_complex_number(given_command[COMMAND_DISPLAY_MODULUS_COMPARISON_NUMBER])
    except ValueError:
        print("The comparison symbol or the complex number have an invalid format.")
        return
    list_of_complex_numbers = functions.display_the_numbers_from_a_list_of_complex_numbers_whose_modulus_is_compared_to_a_given_number(list_of_complex_numbers, current_complex_number, current_comparison_symbol)
    table_list_of_complex_numbers = functions.build_a_table_from_a_list_of_complex_numbers(list_of_complex_numbers)
    print(table_list_of_complex_numbers.draw())
    print()


def process_command_filter_the_real_numbers_from_a_list_of_complex_numbers(given_command, list_of_complex_numbers):
    if len(given_command) != COMMAND_FILTER_REAL_NUMBERS_LENGTH:
        print("This is an invalid command. The format of this command should be filter real.")
        return

    list_of_complex_numbers = functions.filter_a_list_of_complex_numbers_keeping_only_the_real_numbers(list_of_complex_numbers)
    table_list_of_complex_numbers = functions.build_a_table_from_a_list_of_complex_numbers(list_of_complex_numbers)
    print(table_list_of_complex_numbers.draw())
    print()


def process_command_filter_the_numbers_from_a_list_of_complex_numbers_whose_modulus_is_compared_to_a_given_number(given_command, list_of_complex_numbers):
    if len(given_command) != COMMAND_FILTER_MODULUS_COMPARISON_LENGTH:
        print("This is an invalid command. The format of this command should be filter modulo [ < | = | > ] <number>.")
        return

    try:
        current_comparison_symbol = given_command[COMMAND_FILTER_MODULUS_COMPARISON_SYMBOL]
        current_complex_number = functions.transform_a_string_into_a_complex_number(given_command[COMMAND_FILTER_MODULUS_COMPARISON_NUMBER])
    except ValueError:
        print("The comparison symbol or the complex number have an invalid format.")
        return
    list_of_complex_numbers = functions.filter_a_list_of_complex_numbers_keeping_only_the_numbers_whose_modulus_is_compared_to_a_given_number(list_of_complex_numbers, current_complex_number, current_comparison_symbol)
    table_list_of_complex_numbers = functions.build_a_table_from_a_list_of_complex_numbers(list_of_complex_numbers)
    print(table_list_of_complex_numbers.draw())
    print()


def process_command_undo_the_last_operation_done_on_a_list_of_complex_numbers(given_command, list_of_complex_numbers, history_of_done_operations):
    if len(given_command) != COMMAND_UNDO_LENGTH:
        print("This is an invalid command. The format of this command should be undo.")
        return list_of_complex_numbers, history_of_done_operations
    if len(history_of_done_operations) == NULL_VALUE:
        print("The list of operations is empty. Please perform an operation before trying to undo them.")
        return list_of_complex_numbers, history_of_done_operations

    list_of_complex_numbers, history_of_done_operations = functions.undo_the_last_operation_done_on_a_list_of_complex_numbers(list_of_complex_numbers, history_of_done_operations)
    return list_of_complex_numbers, history_of_done_operations


def process_command(given_command, list_of_complex_numbers, history_of_done_operations):
    predefined_commands = ["add", "insert", "remove", "replace", "list", "filter", "undo"]

    if given_command[THE_OPTION_COMMAND] not in predefined_commands:
        print("This is an invalid command. Please try again!")
        return list_of_complex_numbers, history_of_done_operations

    last_done_operation = ""
    if given_command[THE_OPTION_COMMAND] == "add":
        list_of_complex_numbers, last_done_operation = process_command_add_a_complex_number_to_a_list_of_complex_numbers(given_command, list_of_complex_numbers, last_done_operation)
        if last_done_operation != "":
            history_of_done_operations.append(last_done_operation)

    elif given_command[THE_OPTION_COMMAND] == "insert":
        list_of_complex_numbers, last_done_operation = process_command_insert_a_complex_number_to_a_given_position_in_a_list_of_complex_numbers(given_command, list_of_complex_numbers, last_done_operation)
        if last_done_operation != "":
            history_of_done_operations.append(last_done_operation)

    elif given_command[THE_OPTION_COMMAND] == "remove":
        if len(given_command) == COMMAND_REMOVE_A_NUMBER_FROM_A_POSITION_LENGTH:
            list_of_complex_numbers, last_done_operation = process_command_remove_a_complex_number_from_a_given_position_from_a_list_of_complex_numbers(given_command, list_of_complex_numbers, last_done_operation)
            if last_done_operation != "":
                history_of_done_operations.append(last_done_operation)
        else:
            list_of_complex_numbers, last_done_operation = process_command_remove_a_range_of_complex_numbers_from_a_list_of_complex_numbers(given_command, list_of_complex_numbers, last_done_operation)
            if last_done_operation != "":
                history_of_done_operations.append(last_done_operation)

    elif given_command[THE_OPTION_COMMAND] == "replace":
        list_of_complex_numbers, last_done_operation = process_command_replace_all_the_occurrences_of_a_complex_number_with_another_complex_number_in_a_list_of_complex_numbers(given_command, list_of_complex_numbers, last_done_operation)
        if last_done_operation != "":
            history_of_done_operations.append(last_done_operation)

    elif given_command[THE_OPTION_COMMAND] == "list":
        if len(given_command) == COMMAND_DISPLAY_LIST_LENGTH:
            process_command_display_a_list_of_complex_numbers(given_command, list_of_complex_numbers)
        elif len(given_command) == COMMAND_DISPLAY_REAL_NUMBERS_LENGTH:
            process_command_display_the_real_numbers_from_a_list_of_complex_numbers(given_command, list_of_complex_numbers)
        elif len(given_command) == COMMAND_DISPLAY_MODULUS_COMPARISON_LENGTH:
            process_command_display_the_numbers_from_a_list_of_complex_numbers_whose_modulus_is_compared_to_a_given_number(given_command, list_of_complex_numbers)

    elif given_command[THE_OPTION_COMMAND] == "filter":
        if len(given_command) == COMMAND_FILTER_REAL_NUMBERS_LENGTH:
            process_command_filter_the_real_numbers_from_a_list_of_complex_numbers(given_command, list_of_complex_numbers)
        else:
            process_command_filter_the_numbers_from_a_list_of_complex_numbers_whose_modulus_is_compared_to_a_given_number(given_command, list_of_complex_numbers)

    elif given_command[THE_OPTION_COMMAND] == "undo":
        list_of_complex_numbers, history_of_done_operations = process_command_undo_the_last_operation_done_on_a_list_of_complex_numbers(given_command, list_of_complex_numbers, history_of_done_operations)

    return list_of_complex_numbers, history_of_done_operations


def print_possible_command_formats():
    print("add <number>")
    print("insert <number> at <position>")
    print("remove <position>")
    print("remove <start position> to <end position>")
    print("replace <old number> with <new number>")
    print("list")
    print("list real <start position> to <end position>")
    print("list modulo [ < | = | > ] <number>")
    print("filter real")
    print("filter modulo [ < | = | > ] <number>")
    print("undo")
    print("exit the program")
    print()


def print_user_interface():
    list_of_complex_numbers = functions.generate_a_list_of_complex_numbers(NUMBER_OF_COMPLEX_NUMBERS_AVAILABLE_AT_PROGRAM_STARTUP)
    history_of_done_operations = []
    while True:
        print("Enter a command using one of the following formats: ")
        print_possible_command_formats()
        given_command = input().split()
        if given_command[THE_OPTION_COMMAND] == "exit":
            break
        else:
            list_of_complex_numbers, history_of_done_operations = process_command(given_command, list_of_complex_numbers, history_of_done_operations)
