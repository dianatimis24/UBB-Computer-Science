from src.repository.ComplexNumberMemoryRepository import ComplexNumberMemoryRepository
from src.repository.ComplexNumberTextFileRepository import ComplexNumberTextFileRepository
from src.repository.ComplexNumberBinaryFileRepository import ComplexNumberBinaryRepository
from src.repository.ComplexNumberJSONRepository import ComplexNumberJSONRepository
from src.ui.ui import UI
from src.tests.tests import Test
from jproperties import Properties


def get_repository_from_properties():
    configurations = Properties()
    with open('settings.properties', 'rb') as configuration_file:
        configurations.load(configuration_file)

    type_of_repository_string = configurations.get("REPOSITORY").data
    repository = ""

    if type_of_repository_string == "Memory":
        repository = ComplexNumberMemoryRepository()
    elif type_of_repository_string == "Text":
        repository = ComplexNumberTextFileRepository("complex_numbers.txt")
    elif type_of_repository_string == "Binary":
        repository = ComplexNumberBinaryRepository("complex_numbers.pickle")
    elif type_of_repository_string == "JSON":
        repository = ComplexNumberJSONRepository("complex_numbers.json")

    return repository


test_repository = Test(get_repository_from_properties())
test_repository.test_add_a_complex_number_to_a_list()

user_interface = UI(get_repository_from_properties())
user_interface.print_user_interface()
