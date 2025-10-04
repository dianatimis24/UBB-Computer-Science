from src.domain.board import Board, WIDTH, HEIGHT
import numpy
import random
import math

INITIALIZATION_VALUE_ZERO = 0
VALUE_OF_AN_EMPTY_POSITION = 0
CHANGING_TURN_VALUE = 1
NOT_AVAILABLE = -1
CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN = 4
NULL_VALUE = 0


class Game:
    def __init__(self):
        self.__board = Board()
        self.__game_over = False
        self.__turn = INITIALIZATION_VALUE_ZERO

    @property
    def board(self):
        return self.__board

    @property
    def game_over(self):
        return self.__game_over

    @property
    def turn(self):
        return self.__turn

    @game_over.setter
    def game_over(self, value):
        self.__game_over = value

    def get_board(self):
        return numpy.flip(self.board.board, 0)

    def change_turn(self):
        self.__turn = self.__turn ^ CHANGING_TURN_VALUE

    def is_column_valid(self, column):
        return 0 <= column < WIDTH and self.__board.board[HEIGHT - 1][column] == VALUE_OF_AN_EMPTY_POSITION

    def get_next_free_row(self, column):
        for row in range(HEIGHT):
            if self.__board.board[row][column] == VALUE_OF_AN_EMPTY_POSITION:
                return row
        return NOT_AVAILABLE

    def drop_piece(self, column):
        next_row = self.get_next_free_row(column)
        if next_row != NOT_AVAILABLE:
            self.__board.board[next_row][column] = self.turn + CHANGING_TURN_VALUE
            self.change_turn()
        else:
            print(f"Column {column + 1} is full. Please choose a different column.")

    def is_draw(self):
        return numpy.count_nonzero(self.__board.board) == WIDTH * HEIGHT

    def winning_move(self, column):
        row = self.get_next_free_row(column) - 1
        if row == NOT_AVAILABLE:
            return False

        if (row >= CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1 and self.__board.board[row][column] ==
                self.__board.board[row - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 3][column] ==
                self.__board.board[row - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 2][column] ==
                self.__board.board[row - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1][column]):
            self.__game_over = True
            return True

        for gap in range(CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN):
            top_horizontal = row - gap
            top_vertical = column + gap

            if top_vertical < WIDTH and top_vertical - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1 >= NULL_VALUE:
                if (self.__board.board[row][top_vertical] ==
                        self.__board.board[row][top_vertical - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 3] ==
                        self.__board.board[row][top_vertical - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 2] ==
                        self.__board.board[row][top_vertical - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1]):
                    self.__game_over = True
                    return True
                if top_horizontal >= NULL_VALUE and top_horizontal + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1 < HEIGHT:
                    if (self.__board.board[top_horizontal][top_vertical] ==
                            self.__board.board[top_horizontal + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 3][top_vertical - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 3] ==
                            self.__board.board[top_horizontal + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 2][top_vertical - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 2] ==
                            self.__board.board[top_horizontal + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1][top_vertical - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1]):
                        self.__game_over = True
                        return True

            top_vertical = column - gap

            if (top_horizontal >= NULL_VALUE and top_vertical >= NULL_VALUE and top_horizontal + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1 < HEIGHT and top_vertical + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1 < WIDTH):
                if (self.__board.board[top_horizontal][top_vertical] ==
                        self.__board.board[top_horizontal + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 3][top_vertical + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 3] ==
                        self.__board.board[top_horizontal + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 2][top_vertical + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 2] ==
                        self.__board.board[top_horizontal + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1][top_vertical + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1]):
                    self.__game_over = True
                    return True

        return False
