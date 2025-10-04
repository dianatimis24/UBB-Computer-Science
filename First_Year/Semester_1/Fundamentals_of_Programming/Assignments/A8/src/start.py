from src.ui.ui import UI
from jproperties import Properties
from src.repository.memory_repository import MemoryRepository, GradeMemoryRepository
from src.repository.text_file_repository import StudentTextFileRepository, DisciplineTextFileRepository, GradeTextFileRepository
from src.repository.binary_file_repository import BinaryFileRepository, GradeBinaryFileRepository


def get_repository_from_properties_file():
    configurations_properties = Properties()

    with open('settings.properties', 'rb') as configuration_file:
        configurations_properties.load(configuration_file)

    type_of_repository_string = configurations_properties.get("repository").data
    repository_for_students = configurations_properties.get("students").data
    repository_for_disciplines = configurations_properties.get("disciplines").data
    repository_for_grades = configurations_properties.get("grades").data

    if type_of_repository_string == "Memory":
        student_repository = MemoryRepository()
        discipline_repository = MemoryRepository()
        grade_repository = GradeMemoryRepository()
    elif type_of_repository_string == "TextFile":
        student_repository = StudentTextFileRepository(repository_for_students)
        discipline_repository = DisciplineTextFileRepository(repository_for_disciplines)
        grade_repository = GradeTextFileRepository(repository_for_grades)
    elif type_of_repository_string == "BinaryFile":
        student_repository = BinaryFileRepository(repository_for_students)
        discipline_repository = BinaryFileRepository(repository_for_disciplines)
        grade_repository = GradeBinaryFileRepository(repository_for_grades)

    else:
        raise ValueError(f"Invalid repository type specified in settings.properties: {type_of_repository_string}")

    return student_repository, discipline_repository, grade_repository


if __name__ == "__main__":
    student_repository, discipline_repository, grade_repository = get_repository_from_properties_file()
    ui = UI(student_repository, discipline_repository, grade_repository)
    ui.print_ui()
