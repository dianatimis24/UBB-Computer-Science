from dataclasses import dataclass


@dataclass
class Grade:
    def __init__(self, discipline_id: int, student_id: int, grade_value: float):
        self.__discipline_id = discipline_id
        self.__student_id = student_id
        self.__grade_value = grade_value

    @property
    def discipline_id(self):
        return self.__discipline_id

    @property
    def student_id(self):
        return self.__student_id

    @property
    def grade_value(self):
        return self.__grade_value

    def __str__(self):
        return str(self.discipline_id) + " " + str(self.student_id) + " " + str(self.grade_value)

    def __eq__(self, other):
        return self.__student_id == other.__student_id and self.__discipline_id == other.__discipline_id and self.__grade_value == other.__grade_value