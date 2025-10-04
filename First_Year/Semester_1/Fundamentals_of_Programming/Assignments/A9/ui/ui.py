from src.services.student_service import StudentService
from src.services.discipline_service import DisciplineService
from src.services.grade_service import GradeService
from src.repository.repository_exception import RepositoryException
from src.services.undo_service import UndoService

MANAGE_STUDENTS = 1
MANAGE_DISCIPLINES = 2
GRADE_STUDENT = 3
SEARCH_STUDENT = 4
SEARCH_DISCIPLINE = 5
DISPLAY_STATISTICS = 6
UNDO_LAST_PERFORMED_OPERATION = 7
REDO_LAST_PERFORMED_OPERATION = 8
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

DISPLAY_FAILING_STUDENTS = 1
DISPLAY_BEST_STUDENTS = 2
DISPLAY_DISCIPLINES_WITH_AT_LEAST_ONE_GRADE = 3

ID_INDEX = 0
AVERAGE_INDEX = 1


class UI:
    def __init__(self, repository_for_students, repository_for_disciplines, repository_for_grades):
        self.__undo_service = UndoService()
        self.__grade_service = GradeService(repository_for_grades, self.__undo_service)
        self.__student_service = StudentService(repository_for_students, self.__undo_service, self.__grade_service)
        self.__discipline_service = DisciplineService(repository_for_disciplines, self.__undo_service, self.__grade_service)
        self.__grade_service.generate_random_grades(self.__student_service.get_all_students_ids(),
                                                    self.__discipline_service.get_all_disciplines_ids())

    def print_main_menu(self):
        print(str(MANAGE_STUDENTS) + ". Manage students")
        print(str(MANAGE_DISCIPLINES) + ". Manage disciplines")
        print(str(GRADE_STUDENT) + ". Grade a student")
        print(str(SEARCH_STUDENT) + ". Search for students")
        print(str(SEARCH_DISCIPLINE) + ". Search for disciplines")
        print(str(DISPLAY_STATISTICS) + ". Display statistics")
        print(str(UNDO_LAST_PERFORMED_OPERATION) + ". Undo the last performed operation")
        print(str(REDO_LAST_PERFORMED_OPERATION) + ". Redo the last performed operation")
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

    def print_display_statistics_menu(self):
        print("1. Display all the students that are failing at one or more disciplines")
        print("2. Display the best students based on aggregate average")
        print("3. Display all the disciplines based on the grades received by the students")

    def print_ui(self):
        while True:
            try:
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

                    elif menu_option == DISPLAY_STATISTICS:
                        self.print_display_statistics_menu()

                        submenu_option = int(input("Choose your option: "))
                        if submenu_option == DISPLAY_FAILING_STUDENTS:
                            failing_students = self.__grade_service.statistics_of_failing_students()
                            for failing_student in failing_students:
                                print(self.__student_service.get_student_by_id(failing_student[ID_INDEX][ID_INDEX]).name,
                                      self.__discipline_service.get_discipline_by_id(failing_student[ID_INDEX][AVERAGE_INDEX]).name,
                                      failing_student[AVERAGE_INDEX])
                        elif submenu_option == DISPLAY_BEST_STUDENTS:
                            best_students = self.__grade_service.statistics_of_best_students()
                            for student in best_students:
                                print(self.__student_service.get_student_by_id(student), best_students[student])
                        elif submenu_option == DISPLAY_DISCIPLINES_WITH_AT_LEAST_ONE_GRADE:
                            disciplines_descending_by_average_grade = self.__grade_service.statistics_of_disciplines_descending_by_average_grade()
                            for discipline in disciplines_descending_by_average_grade:
                                print(self.__discipline_service.get_discipline_by_id(discipline), disciplines_descending_by_average_grade[discipline])
                        else:
                            print("Input not valid!")

                    elif menu_option == UNDO_LAST_PERFORMED_OPERATION:
                        self.__undo_service.undo()

                    elif menu_option == REDO_LAST_PERFORMED_OPERATION:
                        self.__undo_service.redo()

                    elif menu_option == EXIT_THE_MENU:
                        print("Goodbye!")
                        break

                    else:
                        print("Input not valid!")

                except Exception as exception:
                    print(exception)

            except Exception as exception:
                print(exception)
