#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
import ui
import test_functions


def start_the_program():
    test_functions.test_all_functions()
    ui.print_user_interface()


if __name__ == "__main__":
    start_the_program()
