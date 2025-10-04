from src.repository.memory_repository import MemoryRepository, GradeMemoryRepository
from src.repository.repository_exception import RepositoryException
from src.domain.student import Student
from src.domain.discipline import Discipline
from src.domain.grade import Grade
import pickle


class BinaryFileRepository(MemoryRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__filename = file_name
        try:
            self.__load_data_binary_file()
        except FileNotFoundError:
            raise RepositoryException("The file was not found.")
        except Exception:
            raise RepositoryException("Something went wrong. Try again!")

    def __load_data_binary_file(self):
        """
        A function that loads a dictionary of Student or Discipline objects with the content from the corresponding binary file.
        :return: None
        """
        try:
            binary_input_file = open(self.__filename, "rb")
            instances_from_binary_file = pickle.load(binary_input_file)
        except EOFError:
            return
        for current_instance in instances_from_binary_file:
            super().add(current_instance)
        binary_input_file.close()

    def __save_to_binary_file(self):
        """
        A function that saves in the corresponding binary file the content of a dictionary of Student or Discipline objects.
        :return: None
        """
        binary_output_file = open(self.__filename, "wb")
        pickle.dump(self.get_all(), binary_output_file)
        binary_output_file.close()

    def add(self, new_element):
        """
        A function that adds a new element (a Student or a Discipline) to the corresponding binary file repository.
        :param new_element: Student or Discipline
        :return: None
        """
        super().add(new_element)
        self.__save_to_binary_file()

    def remove(self, element_id: int):
        """
        A function that removes an element (a Student or a Discipline) from the corresponding binary file repository by its ID.
        :param element_id: int (integer)
        :return: None
        """
        super().remove(element_id)
        self.__save_to_binary_file()

    def update(self, element):
        """
        A function that updates an element (a Student or a Discipline) in the corresponding binary file repository.
        :param element: Student or Discipline
        :return: None
        """
        super().update(element)
        self.__save_to_binary_file()


class GradeBinaryFileRepository(GradeMemoryRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__filename = file_name
        try:
            self.__load_data_binary_file()
        except FileNotFoundError:
            raise RepositoryException("The file was not found.")
        except Exception:
            raise RepositoryException("Something went wrong. Try again!")

    def __load_data_binary_file(self):
        try:
            binary_input_file = open(self.__filename, "rb")
            instances_from_binary_file = pickle.load(binary_input_file)
        except EOFError:
            return
        for current_instance in instances_from_binary_file:
            super().add(current_instance)
        binary_input_file.close()

    def __save_to_binary_file(self):
        binary_output_file = open(self.__filename, "wb")
        pickle.dump(self.get_all(), binary_output_file)
        binary_output_file.close()

    def add(self, new_grade: Grade):
        super().add(new_grade)
        self.__save_to_binary_file()

    def remove(self, grade: Grade):
        super().remove(grade)
        self.__save_to_binary_file()