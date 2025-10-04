from src.domain.board import Board
from copy import deepcopy


class UI:
    def __init__(self):
        self.__board = Board()

    def read_command(self):
        command = input("Insert your command: ")
        command = command.split(" ", 1)

        if command[0] == "exit":
            return False
        if command[0] == "tick":
            if len(command) == 1:
                self.tick("1")
                return True
            else:
                self.tick(command[1])
                return True
        elif command[0] == "place":
            self.place(command[1])
            return True
        elif command[0] == "save":
            try:
                self.save(command[1])
                return True
            except IndexError:
                print("Invalid format of command!")
                return True
        elif command[0] == "load":
            try:
                self.load(command[1])
                return True
            except IndexError:
                print("Invalid format of command!")
                return True
        else:
            print("Wrong command!")
            return True

    def tick(self, param):
        if param.isnumeric():
            iterations = int(param)
            for i in range(iterations):
                self.__board.change()
        else:
            print("The parameter is not an integer!")

    def save(self, file_name):
        self.__board.write_file(file_name)

    def load(self, file_name):
        self.__board.read_file(file_name)

    def place(self, params):
        old_board = deepcopy(self.__board.board)
        patterns = self.__board.read_patterns("patterns.txt")
        prms = params.split()
        if len(prms) != 2:
            print("Invalid format of command!")
            return
        if len(prms[1]) != 3:
            print("Invalid format of command!")
            return
        if prms[1][1] != ",":
            print("Invalid format of command!")
            return
        if prms[1][0].isnumeric() and prms[1][2].isnumeric():
            x = int(prms[1][0])
            y = int(prms[1][2])
            if x > 7 or y > 7:
                print("Outside the board!")
                return
            if prms[0] in patterns:
                for i in range(len(patterns)):
                    if patterns[i] == prms[0]:
                        for j in range(len(patterns[i + 1])):
                            for k in range(len(patterns[i + 1][j])):
                                if patterns[i + 1][j][k] == "X":
                                    if x + j > 7 or y + k > 7:
                                        print("Outside the board!!")
                                        self.__board.board = old_board
                                        return
                                    if self.__board.board[x + j][y + k] == "X":
                                        print("Life cells can not overlap!")
                                        self.__board.board = old_board
                                        return
                                    else:
                                        self.__board.board[x + j][y + k] = patterns[i + 1][j][k]
                                if patterns[i + 1][j][k] == "+":
                                    if x + j > 7 or y + k > 7:
                                        print("Outside the board!!")
                                        self.__board.board = old_board
                                        return
                                    if self.__board.board[x + j][y + k] == "X":
                                        print("Life cells can not overlap!")
                                        self.__board.board = old_board
                                        return
                                    self.__board.board[x + j][y + k] = " "
            else:
                print("No such pattern!")
        else:
            print("Parameters are not integers!")

    def run_ui(self):
        print(self.__board)
        cmd = self.read_command()
        while cmd:
            print(self.__board)
            cmd = self.read_command()
