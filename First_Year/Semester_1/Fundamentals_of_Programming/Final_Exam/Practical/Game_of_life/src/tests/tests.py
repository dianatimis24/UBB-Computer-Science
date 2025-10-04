from src.domain.board import Board
from unittest import TestCase


class Tests(TestCase):
    def test_grid_tick(self):
        board = Board()
        board.board[4][0] = "X"
        board.board[4][1] = "X"
        board.board[4][2] = "X"
        board.board[3][2] = "X"
        board.board[2][1] = "X"
        board.change()
        board.change()
        board.change()
        board.change()
        assert board.board[5][1] == "X"
        assert board.board[5][2] == "X"
        assert board.board[5][3] == "X"
        assert board.board[4][3] == "X"
        assert board.board[3][2] == "X"
        assert board.board[2][1] != "X"

    def test_grid_place(self):
        board = Board()
        l = board.read_patterns("patterns.txt")
        assert "beacon" in l
        assert "blinker" in l
        assert [["X", "X"], ["X", "X"]] in l
        assert [["X", "X"], ["X", " "]] not in l