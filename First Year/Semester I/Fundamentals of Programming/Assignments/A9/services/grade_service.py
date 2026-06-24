import random
from src.domain.grade import Grade
from src.repository.memory_repository import GradeMemoryRepository
from src.services.undo_service import UndoService, FunctionCall, Operation, CascadedOperation
from statistics import mean

NUMBER_OF_ENTITIES_AT_THE_PROGRAM_STARTUP = 20
THE_SMALLEST_GRADE = 1
THE_GREATEST_GRADE = 10

STUDENT_ID = 0
DISCIPLINE_ID = 1

SMALLEST_GRADE_TO_PASS_A_DISCIPLINE = 5


class GradeService:
    def __init__(self, repository: GradeMemoryRepository, undo_service: UndoService):
        self.__repository = repository
        self.__undo_service = undo_service
        self.__statistics = {}

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
        function_redo = FunctionCall(self.__repository.add, new_grade)
        function_undo = FunctionCall(self.__repository.remove, new_grade)
        self.__undo_service.record_undo(Operation(function_undo, function_redo))

    def get_all_grades(self):
        return self.__repository.get_all()

    def filter_grades_based_on_student(self, student_id: int):
        grades = []
        for grade in self.get_all_grades():
            if grade.student_id == student_id:
                grades.append(grade)
        return grades

    def filter_grades_based_on_discipline(self, discipline_id: int):
        grades = []
        for grade in self.get_all_grades():
            if grade.discipline_id == discipline_id:
                grades.append(grade)
        return grades

    def remove_grade(self, grade: Grade):
        self.__repository.remove(grade)

    def delete_grades_based_on_discipline(self, discipline_id: int):
        self.__repository.delete_grades_based_on_discipline(discipline_id)

    def delete_grades_based_on_student(self, student_id: int):
        self.__repository.delete_grades_based_on_student(student_id)

    def process_data(self):
        for grade in self.get_all_grades():
            key = (grade.student_id, grade.discipline_id)
            if key not in self.__statistics:
                self.__statistics.update({key: []})
            self.__statistics[key].append(grade.grade_value)

    def statistics_of_failing_students(self):
        self.process_data()
        failing_students = []

        for key in self.__statistics:
            average = mean(self.__statistics[key])
            if average < SMALLEST_GRADE_TO_PASS_A_DISCIPLINE:
                failing_students.append([key, average])

        return failing_students

    def statistics_of_best_students(self):
        self.process_data()
        students_grades = {}
        best_students = {}

        for key in self.__statistics:
            average = mean(self.__statistics[key])
            if key[STUDENT_ID] not in students_grades:
                students_grades.update({key[STUDENT_ID]: []})
            students_grades[key[STUDENT_ID]].append(average)

        for key in students_grades:
            average = mean(students_grades[key])
            best_students[key] = average

        return dict(sorted(best_students.items(), key=lambda key_value_pair: key_value_pair[1], reverse=True))

    def statistics_of_disciplines_descending_by_average_grade(self):
        self.process_data()
        discipline_grades = {}
        disciplines_descending_by_average_grade = {}

        for key in self.__statistics:
            average = mean(self.__statistics[key])
            if key[DISCIPLINE_ID] not in discipline_grades:
                discipline_grades.update({key[DISCIPLINE_ID]: []})
            discipline_grades[key[DISCIPLINE_ID]].append(average)

        for key in discipline_grades:
            average = mean(discipline_grades[key])
            disciplines_descending_by_average_grade[key] = average

        return dict(sorted(disciplines_descending_by_average_grade.items(), key=lambda key_value_pair: key_value_pair[1], reverse=True))
