import random
from src.domain.grade import Grade
from src.repository.memory_repository import GradeMemoryRepository

NUMBER_OF_ENTITIES_AT_THE_PROGRAM_STARTUP = 20
THE_SMALLEST_GRADE = 1
THE_GREATEST_GRADE = 10


class GradeService:
    def __init__(self, repository: GradeMemoryRepository):
        self.__repository = repository

    def generate_random_grades(self, students: list, disciplines: list):
        for _ in range(NUMBER_OF_ENTITIES_AT_THE_PROGRAM_STARTUP):
            student = random.choice(students)
            discipline = random.choice(disciplines)
            grade = random.uniform(THE_SMALLEST_GRADE, THE_GREATEST_GRADE)
            self.add_grade(discipline, student, grade)

    def check_of_grade_is_valid(self, grade: float):
        self.__repository.check_if_input_grade_is_valid(grade)

    def add_grade(self, discipline_id: int, student_id: int, grade_value: float):
        new_grade = Grade(discipline_id, student_id, grade_value)
        self.__repository.add(new_grade)

    def get_all_grades(self):
        return self.__repository.get_all()

    def delete_grades_based_on_discipline(self, discipline_id: int):
        self.__repository.delete_grades_based_on_discipline(discipline_id)

    def delete_grades_based_on_student(self, student_id: int):
        self.__repository.delete_grades_based_on_student(student_id)
