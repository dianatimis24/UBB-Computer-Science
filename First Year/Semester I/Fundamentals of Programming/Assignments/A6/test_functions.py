import functions


def test_add_a_complex_number_to_a_list_of_numbers():
    list_of_complex_numbers = []
    functions.add_a_complex_number_to_the_end_of_a_list_of_complex_numbers(list_of_complex_numbers, functions.create_complex_number(24, 30))
    assert list_of_complex_numbers == [{'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30}]
    functions.add_a_complex_number_to_the_end_of_a_list_of_complex_numbers(list_of_complex_numbers, functions.create_complex_number(100, 0))
    assert list_of_complex_numbers == [{'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
                                       {'the_real_part_of_the_complex_number': 100, 'the_imaginary_part_of_the_complex_number': 0}]
    functions.add_a_complex_number_to_the_end_of_a_list_of_complex_numbers(list_of_complex_numbers, functions.create_complex_number(0, -5))
    assert list_of_complex_numbers == [{'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
                                       {'the_real_part_of_the_complex_number': 100, 'the_imaginary_part_of_the_complex_number': 0},
                                       {'the_real_part_of_the_complex_number': 0, 'the_imaginary_part_of_the_complex_number': -5}]


def test_insert_a_complex_number_to_a_given_position_in_a_list_of_complex_numbers():
    list_of_complex_numbers = [{'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
                               {'the_real_part_of_the_complex_number': 100, 'the_imaginary_part_of_the_complex_number': 0},
                               {'the_real_part_of_the_complex_number': 0, 'the_imaginary_part_of_the_complex_number': -5}]

    functions.insert_a_complex_number_to_a_given_position_in_a_list_of_complex_numbers(list_of_complex_numbers, functions.create_complex_number(-30, -24), 1)
    assert list_of_complex_numbers == [{'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
                                       {'the_real_part_of_the_complex_number': -30, 'the_imaginary_part_of_the_complex_number': -24},
                                       {'the_real_part_of_the_complex_number': 100, 'the_imaginary_part_of_the_complex_number': 0},
                                       {'the_real_part_of_the_complex_number': 0, 'the_imaginary_part_of_the_complex_number': -5}]
    functions.insert_a_complex_number_to_a_given_position_in_a_list_of_complex_numbers(list_of_complex_numbers, functions.create_complex_number(-3, 5), 3)
    assert list_of_complex_numbers == [{'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
                                       {'the_real_part_of_the_complex_number': -30, 'the_imaginary_part_of_the_complex_number': -24},
                                       {'the_real_part_of_the_complex_number': 100, 'the_imaginary_part_of_the_complex_number': 0},
                                       {'the_real_part_of_the_complex_number': -3, 'the_imaginary_part_of_the_complex_number': 5},
                                       {'the_real_part_of_the_complex_number': 0, 'the_imaginary_part_of_the_complex_number': -5}]


def test_remove_a_number_from_a_given_position_from_a_list_of_complex_numbers():
    list_of_complex_numbers = [
        {'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
        {'the_real_part_of_the_complex_number': -30, 'the_imaginary_part_of_the_complex_number': -24},
        {'the_real_part_of_the_complex_number': 100, 'the_imaginary_part_of_the_complex_number': 0},
        {'the_real_part_of_the_complex_number': -3, 'the_imaginary_part_of_the_complex_number': 5},
        {'the_real_part_of_the_complex_number': 0, 'the_imaginary_part_of_the_complex_number': -5}]

    functions.remove_a_complex_number_from_a_given_position_from_a_list_of_complex_numbers(list_of_complex_numbers, 1)
    assert list_of_complex_numbers == [
        {'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
        {'the_real_part_of_the_complex_number': 100, 'the_imaginary_part_of_the_complex_number': 0},
        {'the_real_part_of_the_complex_number': -3, 'the_imaginary_part_of_the_complex_number': 5},
        {'the_real_part_of_the_complex_number': 0, 'the_imaginary_part_of_the_complex_number': -5}]

    functions.remove_a_complex_number_from_a_given_position_from_a_list_of_complex_numbers(list_of_complex_numbers, 2)
    assert list_of_complex_numbers == [
        {'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
        {'the_real_part_of_the_complex_number': 100, 'the_imaginary_part_of_the_complex_number': 0},
        {'the_real_part_of_the_complex_number': 0, 'the_imaginary_part_of_the_complex_number': -5}]


def test_remove_a_range_of_numbers_from_a_list_of_complex_numbers():
    list_of_complex_numbers = [
        {'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
        {'the_real_part_of_the_complex_number': -30, 'the_imaginary_part_of_the_complex_number': -24},
        {'the_real_part_of_the_complex_number': 100, 'the_imaginary_part_of_the_complex_number': 0},
        {'the_real_part_of_the_complex_number': -3, 'the_imaginary_part_of_the_complex_number': 5},
        {'the_real_part_of_the_complex_number': 0, 'the_imaginary_part_of_the_complex_number': -5}]

    functions.remove_a_given_range_of_complex_numbers_from_a_list_of_complex_numbers(list_of_complex_numbers, 1, 3)
    assert list_of_complex_numbers == [
        {'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
        {'the_real_part_of_the_complex_number': 0, 'the_imaginary_part_of_the_complex_number': -5}]


def test_replace_all_the_occurrences_of_a_complex_numbers_from_a_list_with_another_given_complex_number():
    list_of_complex_numbers = [
        {'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
        {'the_real_part_of_the_complex_number': -30, 'the_imaginary_part_of_the_complex_number': -24},
        {'the_real_part_of_the_complex_number': 100, 'the_imaginary_part_of_the_complex_number': 0},
        {'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
        {'the_real_part_of_the_complex_number': -3, 'the_imaginary_part_of_the_complex_number': 5},
        {'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30},
        {'the_real_part_of_the_complex_number': 0, 'the_imaginary_part_of_the_complex_number': -5},
        {'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 33},
        {'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 30}]

    functions.replace_all_the_occurrences_of_a_complex_number_from_a_list_of_complex_numbers_with_a_given_complex_number(list_of_complex_numbers, functions.create_complex_number(24, 30), functions.create_complex_number(-24, 3))
    assert list_of_complex_numbers == [
        {'the_real_part_of_the_complex_number': -24, 'the_imaginary_part_of_the_complex_number': 3},
        {'the_real_part_of_the_complex_number': -30, 'the_imaginary_part_of_the_complex_number': -24},
        {'the_real_part_of_the_complex_number': 100, 'the_imaginary_part_of_the_complex_number': 0},
        {'the_real_part_of_the_complex_number': -24, 'the_imaginary_part_of_the_complex_number': 3},
        {'the_real_part_of_the_complex_number': -3, 'the_imaginary_part_of_the_complex_number': 5},
        {'the_real_part_of_the_complex_number': -24, 'the_imaginary_part_of_the_complex_number': 3},
        {'the_real_part_of_the_complex_number': 0, 'the_imaginary_part_of_the_complex_number': -5},
        {'the_real_part_of_the_complex_number': 24, 'the_imaginary_part_of_the_complex_number': 33},
        {'the_real_part_of_the_complex_number': -24, 'the_imaginary_part_of_the_complex_number': 3}]


def test_all_functions():
    test_add_a_complex_number_to_a_list_of_numbers()
    test_insert_a_complex_number_to_a_given_position_in_a_list_of_complex_numbers()
    test_remove_a_number_from_a_given_position_from_a_list_of_complex_numbers()
    test_remove_a_range_of_numbers_from_a_list_of_complex_numbers()
    test_replace_all_the_occurrences_of_a_complex_numbers_from_a_list_with_another_given_complex_number()