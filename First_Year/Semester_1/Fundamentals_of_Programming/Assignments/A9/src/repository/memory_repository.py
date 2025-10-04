from src.repository.repository_exception import RepositoryException, DuplicateIDError, IDNotFoundError
from src.domain.grade import Grade


class MemoryRepository:
    def __init__(self):
        self.__data = {}

    def check_if_id_present(self, element_id: int):
        """
        A function that checks using the ID if an element (Student or Discipline) is in the corresponding memory
        repository and raises an DuplicateIDError if the ID can be found more than one time in the repository.
        :param element_id: int (integer)
        :return: None
        """
        if element_id in self.__data:
            raise DuplicateIDError("Duplicate object ID")

    def check_if_id_not_present(self, element_id: int):
        """
        A function that checks using the ID if an element (Student or Discipline) is not in the corresponding memory
        repository and raises an IDNotFoundError if the ID can not be found in the repository.
        :param element_id: int (integer)
        :return: None
        """
        if element_id not in self.__data:
            raise IDNotFoundError("ID not found")

    def check_if_id_not_present_boolean_return(self, element_id: int):
        """
        A function that checks using the ID if an element (Student or Discipline) is not in the corresponding memory
        repository and returns False if the ID can be found in the repository and True otherwise.
        :param element_id: int (integer)
        :return: Boolean
        """
        if element_id in self.__data:
            return False
        return True

    def get_element_by_id(self, element_id: int):
        """
        A function that returns the element (Student or Discipline) corresponding to a given ID.
        :param element_id: int (integer)
        :return: Student or Discipline
        """
        return self.__data[element_id]

    def add(self, new_element):
        """
        A function that adds a new element (a Student or a Discipline) to the corresponding memory repository.
        :param new_element: Student or Discipline
        :return: None
        """
        self.check_if_id_present(new_element.id)
        self.__data[new_element.id] = new_element

    def remove(self, element_id: int):
        """
        A function that removes an element (a Student or a Discipline) from the corresponding memory repository by its ID.
        :param element_id: int (integer)
        :return: None
        """
        self.check_if_id_not_present(element_id)
        return self.__data.pop(element_id)

    def update(self, element):
        """
        A function that updates an element (a Student or a Discipline) in the corresponding memory repository.
        :param element: Student or Discipline
        :return: None
        """
        self.check_if_id_not_present(element.id)
        self.__data[element.id] = element

    def search_by_id(self, element_id: int):
        list_of_instances = []
        element_id = str(element_id)

        for current_instance in self.__data.values():
            current_instance_id = str(current_instance.id)
            if element_id in current_instance_id:
                list_of_instances.append(current_instance)

        return list_of_instances

    def search_by_name(self, element_name: str):
        list_of_instances = []
        name = element_name.lower()

        for current_instance in self.__data.values():
            current_instance_name = current_instance.name.lower()
            if name in current_instance_name:
                list_of_instances.append(current_instance)

        return list_of_instances

    def get_all(self):
        """
        A function that returns a list with the names of the objects (Student or Discipline) from the memory repository.
        :return: list of str (string) - names
        """
        return list(self.__data.values())

    def get_all_ids(self):
        """
        A function that returns a list with the ID-s of the objects (Student or Discipline) from the memory repository.
        :return: list of int (integer) - ID-s
        """
        return list(self.__data.keys())

    def delete_all(self):
        """
        A function that clears the memory repository.
        :return: None
        """
        self.__data.clear()


class GradeMemoryRepository:
    def __init__(self):
        self.__data_grade = []

    def check_if_input_grade_is_valid(self, grade_value: float):
        if not (0 <= grade_value <= 10):
            raise RepositoryException("The value of the grade is not valid!")

    def add(self, grade: Grade):
        self.check_if_input_grade_is_valid(grade.grade_value)
        self.__data_grade.append(grade)

    def remove(self, grade: Grade):
        self.check_if_input_grade_is_valid(grade.grade_value)
        for current_grade in self.__data_grade:
            if current_grade == grade:
                self.__data_grade.remove(current_grade)
                break

    def get_all(self):
        return self.__data_grade

    def delete_grades_based_on_discipline(self, discipline_id: int):
        self.__data_grade = [object for object in self.__data_grade if object.discipline_id != discipline_id]

    def delete_grades_based_on_student(self, student_id: int):
        self.__data_grade = [object for object in self.__data_grade if object.student_id != student_id]
