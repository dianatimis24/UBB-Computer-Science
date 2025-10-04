VALUE_OF_THE_INDEX_FOR_AN_EMPTY_LIST = -1


class FunctionCall:
    def __init__(self, function_name, *function_parameters):
        self.__function_name = function_name
        self.__function_parameters = function_parameters

    def call(self):
        self.__function_name(*self.__function_parameters)

    def __call__(self, *args, **kwargs):
        self.call()


class Operation:
    def __init__(self, undo_function: FunctionCall, redo_function: FunctionCall):
        self.__undo_function = undo_function
        self.__redo_function = redo_function

    def undo(self):
        self.__undo_function()

    def redo(self):
        self.__redo_function()


class CascadedOperation:
    def __init__(self, *operations):
        self.__operations = operations

    def undo(self):
        for current_operation in self.__operations:
            current_operation.undo()

    def redo(self):
        for current_operation in self.__operations:
            current_operation.redo()


class UndoRedoError(Exception):
    pass


class UndoService:
    def __init__(self):
        self.__history_of_performed_operations = []
        self.__index_of_the_last_performed_operation = VALUE_OF_THE_INDEX_FOR_AN_EMPTY_LIST

    def record_undo(self, operation):
        self.__history_of_performed_operations.append(operation)
        self.__index_of_the_last_performed_operation = len(self.__history_of_performed_operations) - 1

    def undo(self):
        if self.__index_of_the_last_performed_operation == VALUE_OF_THE_INDEX_FOR_AN_EMPTY_LIST:
            raise UndoRedoError("There are no more available undo operations.")

        self.__history_of_performed_operations[self.__index_of_the_last_performed_operation].undo()
        self.__index_of_the_last_performed_operation -= 1

    def redo(self):
        if self.__index_of_the_last_performed_operation == len(self.__history_of_performed_operations) - 1:
            raise UndoRedoError("There are no more available redo operations.")

        self.__index_of_the_last_performed_operation += 1
        self.__history_of_performed_operations[self.__index_of_the_last_performed_operation].redo()
