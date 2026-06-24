from src.repository.memory_repository import MemoryRepository, GradeMemoryRepository
from src.repository.repository_exception import RepositoryException
from src.domain.student import Student
from src.domain.discipline import Discipline
from src.domain.grade import Grade

ID_PARAMETER = 0
NAME_PARAMETER = 1

DISCIPLINE_ID_PARAMETER = 0
STUDENT_ID_PARAMETER = 1
GRADE_VALUE_PARAMETER = 2


class StudentTextFileRepository(MemoryRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__filename = file_name
        try:
            self.__load_data_text_file()
        except FileNotFoundError:
            raise RepositoryException("The file was not found.")
        except Exception:
            raise RepositoryException("Something went wrong. Try again!")

    def __load_data_text_file(self):
        """
        A function that loads a dictionary of Student objects with the content from the corresponding text file.
        :return: None
        """
        lines_from_text_file = []
        try:
            text_file_input = open(self.__filename, "rt")
            lines_from_text_file = text_file_input.readlines()
            text_file_input.close()
        except IOError:
            raise ValueError("Load file incomplete.")

        for line in lines_from_text_file:
            current_line = line.split()
            new_student = Student(int(current_line[ID_PARAMETER].strip()), current_line[NAME_PARAMETER].strip())
            super().add(new_student)

    def __save_to_text_file(self):
        """
        A function that saves in the corresponding text file the content of a dictionary of Student objects.
        :return: None
        """
        text_output_file = open(self.__filename, "wt")
        for student in self.get_all():
            student_string = str(student.id) + " " + str(student.name) + "\n"
            text_output_file.write(student_string)

        text_output_file.close()

    def add(self, student: Student):
        """
        A function that adds a new Student to the corresponding text file repository.
        :param student: Student
        :return: None
        """
        super().add(student)
        self.__save_to_text_file()

    def remove(self, student_id: int):
        """
        A function that removes a Student from the corresponding text file repository by its ID.
        :param student_id: int (integer)
        :return: None
        """
        super().remove(student_id)
        self.__save_to_text_file()

    def update(self, student: Student):
        """
        A function that updates a Student in the corresponding text file repository.
        :param student: Student
        :return: None
        """
        super().update(student)
        self.__save_to_text_file()


class DisciplineTextFileRepository(MemoryRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__filename = file_name
        try:
            self.__load_data_text_file()
        except FileNotFoundError:
            raise RepositoryException("The file was not found.")
        except Exception:
            raise RepositoryException("Something went wrong. Try again!")

    def __load_data_text_file(self):
        """
        A function that loads a dictionary of Discipline objects with the content from the corresponding text file.
        :return: None
        """
        lines_from_text_file = []
        try:
            text_file_input = open(self.__filename, "rt")
            lines_from_text_file = text_file_input.readlines()
            text_file_input.close()
        except IOError:
            raise ValueError("Load file incomplete.")

        for line in lines_from_text_file:
            current_line = line.split()
            new_discipline = Discipline(int(current_line[ID_PARAMETER].strip()), current_line[NAME_PARAMETER].strip())
            super().add(new_discipline)

    def __save_to_text_file(self):
        """
        A function that saves in the corresponding text file the content of a dictionary of Discipline objects.
        :return: None
        """
        text_output_file = open(self.__filename, "wt")
        for discipline in self.get_all():
            discipline_string = str(discipline.id) + " " + str(discipline.name) + "\n"
            text_output_file.write(discipline_string)

        text_output_file.close()

    def add(self, discipline: Discipline):
        """
        A function that adds a new Discipline to the corresponding text file repository.
        :param discipline: Discipline
        :return: None
        """
        super().add(discipline)
        self.__save_to_text_file()

    def remove(self, discipline_id: int):
        """
        A function that removes a Discipline from the corresponding text file repository by its ID.
        :param discipline_id: int (integer)
        :return: None
        """
        super().remove(discipline_id)
        self.__save_to_text_file()

    def update(self, discipline: Discipline):
        """
        A function that updates a Discipline in the corresponding text file repository.
        :param discipline: Student or Discipline
        :return: None
        """
        super().update(discipline)
        self.__save_to_text_file()


class GradeTextFileRepository(GradeMemoryRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__filename = file_name
        try:
            self.__load_data_text_file()
        except FileNotFoundError:
            raise RepositoryException("The file was not found.")
        except Exception:
            raise RepositoryException("Something went wrong. Try again!")

    def __load_data_text_file(self):
        lines_from_text_file = []
        try:
            text_file_input = open(self.__filename, "rt")
            lines_from_text_file = text_file_input.readlines()
            text_file_input.close()
        except IOError:
            raise ValueError("Load file incomplete.")

        for line in lines_from_text_file:
            current_line = line.split()
            new_grade = Grade(int(current_line[DISCIPLINE_ID_PARAMETER].strip()), int(current_line[STUDENT_ID_PARAMETER].strip()), float(current_line[GRADE_VALUE_PARAMETER].strip()))
            super().add(new_grade)

    def __save_to_text_file(self):
        text_output_file = open(self.__filename, "wt")
        for grade in self.get_all():
            grade_string = str(grade.discipline_id) + " " + str(grade.student_id) + " " + str(grade.grade_value) + "\n"
            text_output_file.write(grade_string)

        text_output_file.close()

    def add(self, grade: Grade):
        super().add(grade)
        self.__save_to_text_file()

    def remove(self, grade: Grade):
        super().remove(grade)
        self.__save_to_text_file()