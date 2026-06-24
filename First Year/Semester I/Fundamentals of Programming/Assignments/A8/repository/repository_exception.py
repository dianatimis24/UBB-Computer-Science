class RepositoryException(Exception):
    def __init__(self, exception_message):
        self._exception_message = exception_message

    def __str__(self):
        return self._exception_message


class DuplicateIDError(RepositoryException):
    pass


class IDNotFoundError(RepositoryException):
    pass
