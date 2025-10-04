from texttable import Texttable
from copy import deepcopy


class Board:
    def __init__(self):
        self.__board = [[" ", " ", " ", " ", " ", " ", " ", " "] for i in range(8)]

    @property
    def board(self):
        return self.__board

    @board.setter
    def board(self, board):
        self.__board = board

    def __str__(self):
        table = Texttable()
        table.add_rows(self.__board, [])
        return table.draw()

    def change(self):
        board = deepcopy(self.__board)
        for i in range(8):
            for j in range(8):
                alive_counter = 0
                dead_counter = 0
                if i - 1 >= 0 and j - 1 >= 0:
                    if board[i - 1][j - 1] == "X":
                        alive_counter += 1
                    else:
                        dead_counter += 1
                if i - 1 >= 0:
                    if board[i - 1][j] == "X":
                        alive_counter += 1
                    else:
                        dead_counter += 1
                if j - 1 >= 0:
                    if board[i][j - 1] == "X":
                        alive_counter += 1
                    else:
                        dead_counter += 1
                if i + 1 < 8 and j + 1 < 8:
                    if board[i + 1][j + 1] == "X":
                        alive_counter += 1
                    else:
                        dead_counter += 1
                if i + 1 < 8:
                    if board[i + 1][j] == "X":
                        alive_counter += 1
                    else:
                        dead_counter += 1
                if j + 1 < 8:
                    if board[i][j + 1] == "X":
                        alive_counter += 1
                    else:
                        dead_counter += 1
                if i - 1 >= 0 and j + 1 < 8:
                    if board[i - 1][j + 1] == "X":
                        alive_counter += 1
                    else:
                        dead_counter += 1
                if i + 1 < 8 and j - 1 >= 0:
                    if board[i + 1][j - 1] == "X":
                        alive_counter += 1
                    else:
                        dead_counter += 1

                if board[i][j] == "X":
                    if alive_counter < 2 or alive_counter > 3:
                        self.__board[i][j] = " "
                else:
                    if alive_counter == 3:
                        self.__board[i][j] = "X"

    def read_file(self, file_name):
        with open(file_name, "r") as file:
            lines = file.readlines()
            i = 0
            for character in lines:
                for j in range(8):
                    if character[j] == "+":
                        self.__board[i][j] = " "
                    elif character[j] == "X":
                        self.__board[i][j] = "X"
                i += 1

    def write_file(self, file_name):
        with open(file_name, "w") as file:
            for line in self.__board:
                for element in line:
                    if element == " ":
                        file.write("+")
                    elif element == "X":
                        file.write("X")
                file.write("\n")

    def read_patterns(self, file_name):
        patterns = []
        with open(file_name, "r") as file:
            lines = file.readlines()
            new_lines = []
            for line in lines:
                new_line = line.strip()
                new_lines.append(new_line)
            lines = new_lines

            for i in range(len(lines)):
                if lines[i] == "block":
                    block_data = []
                    line = [lines[i + 1][0], lines[i + 1][1]]
                    block_data.append(line)
                    line = [lines[i + 2][0], lines[i + 2][1]]
                    block_data.append(line)
                    patterns.append("block")
                    patterns.append(block_data)
                if lines[i] == "tub":
                    tub_data = []
                    line = [lines[i + 1][0], lines[i + 1][1], lines[i + 1][2]]
                    tub_data.append(line)
                    line = [lines[i + 2][0], lines[i + 2][1], lines[i + 2][2]]
                    tub_data.append(line)
                    line = [lines[i + 3][0], lines[i + 3][1], lines[i + 3][2]]
                    tub_data.append(line)
                    patterns.append("tub")
                    patterns.append(tub_data)
                if lines[i] == "blinker":
                    blinker_data = []
                    line = [lines[i + 1][0], lines[i + 1][1], lines[i + 1][2]]
                    blinker_data.append(line)
                    line = [lines[i + 2][0], lines[i + 2][1], lines[i + 2][2]]
                    blinker_data.append(line)
                    line = [lines[i + 3][0], lines[i + 3][1], lines[i + 3][2]]
                    blinker_data.append(line)
                    patterns.append("blinker")
                    patterns.append(blinker_data)
                if lines[i] == "beacon":
                    beacon_data = []
                    line = [lines[i + 1][0], lines[i + 1][1], lines[i + 1][2], lines[i + 1][3]]
                    beacon_data.append(line)
                    line = [lines[i + 2][0], lines[i + 2][1], lines[i + 2][2], lines[i + 2][3]]
                    beacon_data.append(line)
                    line = [lines[i + 3][0], lines[i + 3][1], lines[i + 3][2], lines[i + 3][3]]
                    beacon_data.append(line)
                    line = [lines[i + 4][0], lines[i + 4][1], lines[i + 4][2], lines[i + 4][3]]
                    beacon_data.append(line)
                    patterns.append("beacon")
                    patterns.append(beacon_data)
                if lines[i] == "spaceship":
                    spaceship_data = []
                    line = [lines[i + 1][0], lines[i + 1][1], lines[i + 1][2], lines[i + 1][3]]
                    spaceship_data.append(line)
                    line = [lines[i + 2][0], lines[i + 2][1], lines[i + 2][2], lines[i + 2][3]]
                    spaceship_data.append(line)
                    line = [lines[i + 3][0], lines[i + 3][1], lines[i + 3][2], lines[i + 3][3]]
                    spaceship_data.append(line)
                    line = [lines[i + 4][0], lines[i + 4][1], lines[i + 4][2], lines[i + 4][3]]
                    spaceship_data.append(line)
                    patterns.append("spaceship")
                    patterns.append(spaceship_data)
        return patterns
