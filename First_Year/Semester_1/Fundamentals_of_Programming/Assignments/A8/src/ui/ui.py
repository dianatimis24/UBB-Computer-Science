from src.services.student_service import StudentService
from src.services.discipline_service import DisciplineService
from src.services.grade_service import GradeService
from src.repository.repository_exception import RepositoryException

MANAGE_STUDENTS = 1
MANAGE_DISCIPLINES = 2
GRADE_STUDENT = 3
SEARCH_STUDENT = 4
SEARCH_DISCIPLINE = 5
EXIT_THE_MENU = 0

ADD_STUDENT = 1
UPDATE_INFORMATION_ABOUT_STUDENT = 2
REMOVE_STUDENT = 3
LIST_STUDENTS = 4

ADD_DISCIPLINE = 1
UPDATE_INFORMATION_ABOUT_DISCIPLINE = 2
REMOVE_DISCIPLINE = 3
LIST_DISCIPLINES = 4

SEARCH_BY_ID = 1
SEARCH_BY_NAME = 2


class UI:
    def __init__(self, repository_for_students, repository_for_disciplines, repository_for_grades):
        self.__student_service = StudentService(repository_for_students)
        self.__discipline_service = DisciplineService(repository_for_disciplines)
        self.__grade_service = GradeService(repository_for_grades)
        self.__grade_service.generate_random_grades(self.__student_service.get_all_students_ids(),
                                                    self.__discipline_service.get_all_disciplines_ids())

    def print_main_menu(self):
        print(str(MANAGE_STUDENTS) + ". Manage students")
        print(str(MANAGE_DISCIPLINES) + ". Manage disciplines")
        print(str(GRADE_STUDENT) + ". Grade a student")
        print(str(SEARCH_STUDENT) + ". Search for students")
        print(str(SEARCH_DISCIPLINE) + ". Search for disciplines")
        print(str(EXIT_THE_MENU) + ". Exit the menu")

    def print_manage_student_menu(self):
        print(str(ADD_STUDENT) + ". Add a student")
        print(str(UPDATE_INFORMATION_ABOUT_STUDENT) + ". Update information about the student")
        print(str(REMOVE_STUDENT) + ". Remove student")
        print(str(LIST_STUDENTS) + ". List all students")

    def print_manage_discipline_menu(self):
        print(str(ADD_DISCIPLINE) + ". Add a discipline")
        print(str(UPDATE_INFORMATION_ABOUT_DISCIPLINE) + ". Update information about the discipline")
        print(str(REMOVE_DISCIPLINE) + ". Remove discipline")
        print(str(LIST_DISCIPLINES) + ". List all disciplines")

    def print_search_student_menu(self):
        print("1. Search student based on id")
        print("2. Search student based on name")

    def print_search_discipline_menu(self):
        print("1. Search discipline based on id")
        print("2. Search discipline based on name")

    def print_ui(self):
        while True:
            self.print_main_menu()
            menu_option = int(input("Choose an option from the list: "))

            try:
                if menu_option == MANAGE_STUDENTS:
                    self.print_manage_student_menu()

                    submenu_option = int(input("Choose an option: "))
                    if submenu_option == ADD_STUDENT:
                        student_id = int(input("Introduce the ID of the student: "))
                        student_name = input("Introduce the name of the student: ")
                        self.__student_service.add_student(student_id, student_name)

                    elif submenu_option == UPDATE_INFORMATION_ABOUT_STUDENT:
                        student_id = int(input("Introduce the ID of the student: "))
                        student_name = input("Introduce the name of the student: ")
                        self.__student_service.update_student(student_id, student_name)

                    elif submenu_option == REMOVE_STUDENT:
                        student_id = int(input("Introduce the ID of the student: "))
                        self.__grade_service.delete_grades_based_on_student(student_id)
                        self.__student_service.delete_student(student_id)

                    elif submenu_option == LIST_STUDENTS:
                        students = self.__student_service.get_all_students()
                        for student in students:
                            print(student)
                    else:
                        print("Input not valid!")

                elif menu_option == MANAGE_DISCIPLINES:
                    self.print_manage_discipline_menu()

                    submenu_option = int(input("Choose an option: "))
                    if submenu_option == ADD_DISCIPLINE:
                        discipline_id = int(input("Introduce the ID of the discipline: "))
                        discipline_name = input("Introduce the name of the discipline: ")
                        self.__discipline_service.add_discipline(discipline_id, discipline_name)

                    elif submenu_option == UPDATE_INFORMATION_ABOUT_DISCIPLINE:
                        discipline_id = int(input("Introduce the ID of the discipline: "))
                        discipline_name = input("Introduce the name of the discipline: ")
                        self.__discipline_service.update_discipline(discipline_id, discipline_name)

                    elif submenu_option == REMOVE_DISCIPLINE:
                        discipline_id = int(input("Introduce the ID of the discipline: "))
                        self.__grade_service.delete_grades_based_on_discipline(discipline_id)
                        self.__discipline_service.delete_discipline(discipline_id)

                    elif submenu_option == LIST_DISCIPLINES:
                        disciplines = self.__discipline_service.get_all_disciplines()
                        for discipline in disciplines:
                            print(discipline)
                    else:
                        print("Input not valid!")

                elif menu_option == GRADE_STUDENT:
                    discipline_id = int(input("Introduce the ID of the discipline: "))
                    self.__discipline_service.check_if_discipline_is_valid(discipline_id)

                    student_id = int(input("Introduce the ID of the student: "))
                    self.__student_service.check_if_student_is_valid(student_id)

                    grade_value = float(input("Introduce the grade of the student: "))
                    self.__grade_service.add_grade(discipline_id, student_id, grade_value)

                    grades = self.__grade_service.get_all_grades()
                    for grade in grades:
                        print(grade)

                elif menu_option == SEARCH_STUDENT:
                    self.print_search_student_menu()

                    submenu_option = int(input("Choose an option: "))
                    if submenu_option == SEARCH_BY_ID:
                        student_id = int(input("Introduce the ID of the student: "))
                        students = self.__student_service.search_student_based_on_id(student_id)
                        for student in students:
                            print(student)
                    elif submenu_option == SEARCH_BY_NAME:
                        student_name = input("Introduce the name of the student: ")
                        students = self.__student_service.search_student_based_on_name(student_name)
                        for student in students:
                            print(student)
                    else:
                        print("Input not valid!")

                elif menu_option == SEARCH_DISCIPLINE:
                    self.print_search_discipline_menu()

                    submenu_option = int(input("Choose your option: "))
                    if submenu_option == SEARCH_BY_ID:
                        discipline_id = int(input("Introduce the ID of the discipline: "))
                        disciplines = self.__discipline_service.search_discipline_based_on_id(discipline_id)
                        for discipline in disciplines:
                            print(discipline)
                    elif submenu_option == SEARCH_BY_NAME:
                        discipline_name = input("Introduce the name of the discipline: ")
                        disciplines = self.__discipline_service.search_discipline_based_on_name(discipline_name)
                        for discipline in disciplines:
                            print(discipline)
                    else:
                        print("Input not valid!")

                elif menu_option == EXIT_THE_MENU:
                    print("Goodbye!")
                    break

                else:
                    print("Input not valid!")

            except RepositoryException as exception:
                print(exception)
