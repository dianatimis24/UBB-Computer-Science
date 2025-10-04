import numpy

WIDTH = 7
HEIGHT = 6


class Board:
    def __init__(self):
        self.__board = numpy.zeros((HEIGHT, WIDTH), dtype=int)

    @property
    def board(self):
        return self.__board
