from dataclasses import dataclass


@dataclass
class Discipline:
    def __init__(self, discipline_id: int, discipline_name: str):
        self.__discipline_id = discipline_id
        self.__discipline_name = discipline_name

    @property
    def id(self):
        return self.__discipline_id

    @property
    def name(self):
        return self.__discipline_name

    @name.setter
    def name(self, new_discipline_name):
        self.__discipline_name = new_discipline_name

    def __str__(self):
        return str(self.id) + " " + self.name