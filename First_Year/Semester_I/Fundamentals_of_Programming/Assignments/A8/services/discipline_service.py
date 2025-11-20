from src.repository.memory_repository import MemoryRepository
from src.domain.discipline import Discipline
import random

NUMBER_OF_ENTITIES_AT_THE_PROGRAM_STARTUP = 20
LOWER_BOUND_FOR_GENERATING_A_RANDOM_ID = 1
UPPER_BOUND_FOR_GENERATING_A_RANDOM_ID = 1001


class DisciplineService:
    def __init__(self, repository: MemoryRepository):
        self.__repository = repository
        self.generate_random_disciplines()

    def generate_random_disciplines(self):
        list_of_disciplines = ["Neuroscience", "Astrophysics", "MedicalEthics", "CriminalJustice", "DigitalMarketing",
                               "Philosophy", "CreativeWriting", "ComparativeLiterature", "Sociolinguistics",
                               "ArtificialIntelligence", "EcologicalEconomics", "HumanRightsLaw", "MarineBiology",
                               "Psycholinguistics", "Calculus", "LinearAlgebra", "ComputationalLogic", "Geometry",
                               "Databases", "Graphs", "ChineseLanguage"]

        for i in range(NUMBER_OF_ENTITIES_AT_THE_PROGRAM_STARTUP):
            discipline_id = random.randint(LOWER_BOUND_FOR_GENERATING_A_RANDOM_ID, UPPER_BOUND_FOR_GENERATING_A_RANDOM_ID)
            if self.__repository.check_if_id_not_present_boolean_return(discipline_id):
                self.add_discipline(discipline_id, list_of_disciplines[i])

    def check_if_discipline_is_valid(self, discipline_id: int):
        """
        A function that checks if a given Discipline is valid in the corresponding repository by its ID.
        :param discipline_id: int (integer)
        :return: None
        """
        self.__repository.check_if_id_not_present(discipline_id)

    def add_discipline(self, discipline_id, discipline_name):
        """
        A function that creates a new Discipline object and adds using the given ID and name it to the corresponding repository.
        :param discipline_id: int (integer)
        :param discipline_name: str (string)
        :return: None
        """
        new_discipline = Discipline(discipline_id, discipline_name)
        self.__repository.add(new_discipline)

    def get_discipline_by_id(self, discipline_id):
        """
        A function that returns the Discipline object corresponding to a given ID from the corresponding repository.
        :param discipline_id: int (integer)
        :return: Discipline
        """
        return self.__repository.get_element_by_id(discipline_id)

    def get_all_disciplines(self):
        """
        A function that returns a list with the names of all Discipline objects from the corresponding repository.
        :return: list of str (string) - Discipline names
        """
        return self.__repository.get_all()

    def get_all_disciplines_ids(self):
        """
        A function that returns a list with the ID-s of all Discipline objects from the corresponding from the corresponding repository.
        :return: list of str (string) - Discipline ID-s
        """
        return self.__repository.get_all_ids()

    def update_discipline(self, discipline_id, discipline_name):
        """
        A function that creates a Discipline object using the given ID and name and updates it in the corresponding repository.
        :param discipline_id: int (integer)
        :param discipline_name: str (string)
        :return: None
        """
        updated_discipline = Discipline(discipline_id, discipline_name)
        self.__repository.update(updated_discipline)

    def delete_discipline(self, discipline_id):
        """
        A function that removes a Discipline object from the corresponding repository by its ID.
        :param discipline_id: int (integer)
        :return: None
        """
        self.__repository.remove(discipline_id)

    def delete_all_disciplines(self):
        """
        A function that deletes all the Discipline objects from the corresponding repository.
        :return: None
        """
        self.__repository.delete_all()

    def search_discipline_based_on_id(self, discipline_id):
        return self.__repository.search_by_id(discipline_id)

    def search_discipline_based_on_name(self, discipline_name):
        return self.__repository.search_by_name(discipline_name)
