from dataclasses import dataclass


@dataclass
class Student:
    def __init__(self, student_id: int, student_name: str):
        self.__student_id = student_id
        self.__student_name = student_name

    @property
    def id(self):
        return self.__student_id

    @property
    def name(self):
        return self.__student_name

    @name.setter
    def name(self, new_student_name):
        self.__student_name = new_student_name

    def __str__(self):
        return str(self.id) + " " + self.name