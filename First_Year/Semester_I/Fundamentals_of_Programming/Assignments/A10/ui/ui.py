from src.services.game import Game
from src.services.ai import AI
import sys
import math

HUMAN_AGAINST_COMPUTER_OPTION = 1
HUMAN_AGAINST_HUMAN_OPTION = 2
EXIT_THE_MENU = 0
EASY_DIFFICULTY_OPTION = 1
MEDIUM_DIFFICULTY_OPTION = 2
HARD_DIFFICULTY_OPTION = 3
EASY_DIFFICULTY_DEPTH = 2
MEDIUM_DIFFICULTY_DEPTH = 4
HARD_DIFFICULTY_DEPTH = 6
CHANGING_TURN_VALUE = 1
FIRST_POSITION = 0
COMPUTER_PLAYER = True
WHITE_CIRCLE_TOKEN = "\U000026aa"
RED_CIRCLE_TOKEN = "\U0001f534"
YELLOW_CIRCLE_TOKEN = "\U0001f7e1"


class UI:
    def __init__(self):
        self.__game = Game()
        self.__depth = HARD_DIFFICULTY_DEPTH
        self.__ai = AI(HARD_DIFFICULTY_DEPTH)
        self.__tokens = [WHITE_CIRCLE_TOKEN, RED_CIRCLE_TOKEN, YELLOW_CIRCLE_TOKEN]

    def print_board(self):
        board = self.__game.get_board()
        for current_row in board:
            for current_column in current_row:
                print(self.__tokens[current_column], end=" ")
            print()

    def human_turn(self):
        given_column = int(input("Player " + str(self.__game.turn + 1) + ".\nMake your selection (1 - 7): ")) - 1
        if self.__game.is_column_valid(given_column):
            self.__game.drop_piece(given_column)
            self.print_board()
            if self.__game.winning_move(given_column):
                print("Player " + str((self.__game.turn ^ CHANGING_TURN_VALUE) + 1) + " won!")
                self.__game.game_over = True
            elif self.__game.is_draw():
                print("It's a draw!")
                self.__game.game_over = True
        else:
            print("Invalid column!")
            self.human_turn()

    def computer_turn(self):
        print("Computer's turn")
        computer_column = self.__ai.minimax_algorithm(self.__game.board, self.__depth, -math.inf, math.inf, COMPUTER_PLAYER)[FIRST_POSITION]
        self.__game.drop_piece(computer_column)
        self.print_board()
        if self.__game.winning_move(computer_column):
            print("Computer won!")
            self.__game.game_over = True
        elif self.__game.is_draw():
            print("It's a draw!")
            self.__game.game_over = True

    def play_against_computer(self):
        while not self.__game.game_over:
            self.human_turn()
            if not self.__game.game_over:
                self.computer_turn()

    def play_against_a_friend(self):
        while not self.__game.game_over:
            self.human_turn()
            if not self.__game.game_over:
                self.human_turn()

    def print_main_menu(self):
        print("Welcome to Connect Four!")
        print("1. Play against the computer.")
        print("2. Play against a friend.")
        print("0. Exit.")

    def print_difficulty_menu(self):
        print("Select a difficulty level:")
        print("1. Easy")
        print("2. Medium")
        print("3. Hard")

    def start_the_program(self):
        self.print_main_menu()
        try:
            game_option = int(input("Choose an option: "))

            if game_option == HUMAN_AGAINST_COMPUTER_OPTION:
                print("You chose to play against the computer!")
                self.print_difficulty_menu()
                difficulty_level = int(input("Choose a valid difficulty level: "))

                if difficulty_level == EASY_DIFFICULTY_OPTION:
                    self.__depth = EASY_DIFFICULTY_DEPTH
                elif difficulty_level == MEDIUM_DIFFICULTY_OPTION:
                    self.__depth = MEDIUM_DIFFICULTY_DEPTH
                elif difficulty_level == HARD_DIFFICULTY_OPTION:
                    self.__depth = HARD_DIFFICULTY_DEPTH

                self.play_against_computer()

            elif game_option == HUMAN_AGAINST_HUMAN_OPTION:
                print("You chose to play against a friend!")
                self.play_against_a_friend()

            elif game_option == EXIT_THE_MENU:
                print("Goodbye!")
                sys.exit()

            else:
                print("Invalid game option! Please try again!")
                self.start_the_program()

        except ValueError:
            print("Invalid option! Please try again!")
            self.start_the_program()
