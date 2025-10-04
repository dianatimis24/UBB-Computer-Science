from src.repository.repository_exception import RepositoryException
from src.services.discipline_service import DisciplineService
from src.services.student_service import StudentService
from src.repository.memory_repository import MemoryRepository
import random
import unittest


class TestDisciplines(unittest.TestCase):
    def test_add_discipline(self):
        id = 164339
        name = "Discipline1"
        discipline_service = DisciplineService(MemoryRepository())
        number_of_disciplines = len(discipline_service.get_all_disciplines())
        discipline_service.add_discipline(id, name)
        self.assertEqual(len(discipline_service.get_all_disciplines()), number_of_disciplines + 1)

    def test_add_discipline_duplicate(self):
        id = 1556234
        name = "Discipline1"
        discipline_service = DisciplineService(MemoryRepository())
        discipline_service.add_discipline(id, name)
        with self.assertRaises(RepositoryException): discipline_service.add_discipline(id, name)

    def test_update_discipline(self):
        discipline_service = DisciplineService(MemoryRepository())
        disciplines = discipline_service.get_all_disciplines()

        discipline_service.update_discipline(disciplines[0].id, "Discipline1")
        disciplines = discipline_service.get_all_disciplines()

        self.assertEqual(disciplines[0].name, "Discipline1")

    def test_update_discipline_not_found(self):
        discipline_service = DisciplineService(MemoryRepository())
        id = 12738621
        name = "Discipline1"
        with self.assertRaises(RepositoryException): discipline_service.update_discipline(id, name)

    def test_remove_discipline(self):
        discipline_service = DisciplineService(MemoryRepository())
        number_of_disciplines = len(discipline_service.get_all_disciplines())

        id = random.randint(1, 1001)
        while id not in discipline_service.get_all_disciplines_ids():
            id += 1

        discipline_service.delete_discipline(id)

        self.assertEqual(len(discipline_service.get_all_disciplines()), number_of_disciplines - 1)


class TestStudents(unittest.TestCase):
    def test_add_student(self):
        id = 0
        name = "Student1"
        student_service = StudentService(MemoryRepository())
        number_of_students = len(student_service.get_all_students())
        student_service.add_student(id, name)
        self.assertEqual(len(student_service.get_all_students()), number_of_students + 1)

    def test_add_student_duplicate(self):
        id = 24
        name = "Student1"
        student_service = StudentService(MemoryRepository())
        student_service.add_student(id, name)
        with self.assertRaises(RepositoryException): student_service.add_student(id, name)

    def test_update_student(self):
        student_service = StudentService(MemoryRepository())
        students = student_service.get_all_students()

        student_service.update_student(students[0].id, "Student1")
        students = student_service.get_all_students()

        self.assertEqual(students[0].name, "Student1")

    def test_update_student_not_found(self):
        student_service = StudentService(MemoryRepository())
        id = 12738621
        name = "Student1"
        with self.assertRaises(RepositoryException): student_service.update_student(id, name)

    def test_remove_student(self):
        student_service = StudentService(MemoryRepository())
        number_of_students = len(student_service.get_all_students())

        id = random.randint(1, 1001)
        while id not in student_service.get_all_students_ids():
            id += 1

        student_service.delete_student(id)

        self.assertEqual(len(student_service.get_all_students()), number_of_students - 1)


if __name__ == '__main__':
    unittest.main()
