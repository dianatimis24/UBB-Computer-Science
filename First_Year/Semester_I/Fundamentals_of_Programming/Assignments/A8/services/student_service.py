from src.repository.memory_repository import MemoryRepository
from src.domain.student import Student
import random

NUMBER_OF_ENTITIES_AT_THE_PROGRAM_STARTUP = 20
LOWER_BOUND_FOR_GENERATING_A_RANDOM_ID = 1
UPPER_BOUND_FOR_GENERATING_A_RANDOM_ID = 1001


class StudentService:
    def __init__(self, repository: MemoryRepository):
        self.__repository = repository
        self.generate_random_students()

    def generate_random_students(self):
        student_names = ["Dorothea", "Diana", "Eleanor", "Ben", "Penelope", "Theodore", "Isabella", "Oliver", "Abigail",
                         "Sebastian", "Grace", "Alexander", "Charlotte", "Ethan", "Amelia", "Cristina", "Sophia",
                         "William", "Ava", "Henry"]
        for i in range(NUMBER_OF_ENTITIES_AT_THE_PROGRAM_STARTUP):
            student_id = random.randint(LOWER_BOUND_FOR_GENERATING_A_RANDOM_ID, UPPER_BOUND_FOR_GENERATING_A_RANDOM_ID)
            if self.__repository.check_if_id_not_present_boolean_return(student_id):
                self.add_student(student_id, student_names[i])

    def check_if_student_is_valid(self, student_id: int):
        """
        A function that checks if a given Student is valid in the corresponding repository by its ID.
        :param student_id: int (integer)
        :return: None
        """
        self.__repository.check_if_id_not_present(student_id)

    def add_student(self, student_id, student_name):
        """
        A function that creates a new Student object using the given ID and name and adds it to the corresponding repository.
        :param student_id: int (integer)
        :param student_name: str (string)
        :return: None
        """
        new_student = Student(student_id, student_name)
        self.__repository.add(new_student)

    def get_student_by_id(self, student_id):
        """
        A function that returns the Student object corresponding to a given ID from the corresponding repository.
        :param student_id: int (integer)
        :return: Student
        """
        return self.__repository.get_element_by_id(student_id)

    def get_all_students(self):
        """
        A function that returns a list with the names of all Student objects from the corresponding repository.
        :return: list of str (string) - Student names
        """
        return self.__repository.get_all()

    def get_all_students_ids(self):
        """
        A function that returns a list with the ID-s of all Student objects from the corresponding from the corresponding repository.
        :return: list of str (string) - Student ID-s
        """
        return self.__repository.get_all_ids()

    def update_student(self, student_id, student_name):
        """
        A function that creates a Student object using the given ID and name and updates it in the corresponding repository.
        :param student_id: int (integer)
        :param student_name: str (string)
        :return: None
        """
        updated_student = Student(student_id, student_name)
        self.__repository.update(updated_student)

    def delete_student(self, student_id):
        """
        A function that removes a Student object from the corresponding repository by its ID.
        :param student_id: int (integer)
        :return: None
        """
        self.__repository.remove(student_id)

    def delete_all_students(self):
        """
        A function that deletes all the Students objects from the corresponding repository.
        :return: None
        """
        self.__repository.delete_all()

    def search_student_based_on_id(self, student_id):
        return self.__repository.search_by_id(student_id)

    def search_student_based_on_name(self, student_name):
        return self.__repository.search_by_name(student_name)
