from src.domain.board import Board, WIDTH, HEIGHT
import math
import copy

CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN = 4
HUMAN_IDENTIFICATION_VALUE = 1
AI_IDENTIFICATION_VALUE = 2
MAXIMUM_VALUE = 100000
VALUE_OF_AN_EMPTY_POSITION = 0
NOT_AVAILABLE = 0
INITIALIZATION_VALUE_ZERO = 0
EMPTY_LIST = 0
NULL_VALUE = 0
FIRST_POSITION = 0
SECOND_POSITION = 1
COMPUTER_PLAYER = True
HUMAN_PLAYER = False
COLUMN_ARRAY_INITIALIZATION_LIST = [3, 4, 2, 1, 5, 0, 6]
HIGH_SCORE = 1000
PARTIAL_SCORE_1 = 100
PARTIAL_SCORE_2 = 1
REDUCED_SCORE = 500
MAXIMUM_COUNTER = 4
PARTIAL_COUNTER_1 = 3
PARTIAL_COUNTER_2 = 2
NULL_COUNTER = 0


class AI:
    def __init__(self, depth):
        self.__depth = depth
        self.__columns_array = COLUMN_ARRAY_INITIALIZATION_LIST

    def set_depth(self, depth):
        self.__depth = depth

    def winning_move(self, board: Board, player):
        for row in range(HEIGHT):
            for column in range(WIDTH - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1):
                if (board.board[row][column] ==
                        board.board[row][column + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 3] ==
                        board.board[row][column + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 2] ==
                        board.board[row][column + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1] == player):
                    return True

        for row in range(HEIGHT - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1):
            for column in range(WIDTH):
                if (board.board[row][column] ==
                        board.board[row + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 3][column] ==
                        board.board[row + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 2][column] ==
                        board.board[row + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1][column] == player):
                    return True

            for column in range(WIDTH - 1, 2, -1):
                if (board.board[row][column] ==
                        board.board[row + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 3][column - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 3] ==
                        board.board[row + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 2][column - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 2] ==
                        board.board[row + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1][column - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1] ==
                        player):
                    return True

            for column in range(WIDTH - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1):
                if (board.board[row][column] ==
                        board.board[row + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 3][column + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 3] ==
                        board.board[row + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 2][column + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 2] ==
                        board.board[row + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1][column + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1] ==
                        player):
                    return True

        return False

    def get_tokens_score(self, tokens):
        score = INITIALIZATION_VALUE_ZERO

        counter = tokens.count(AI_IDENTIFICATION_VALUE)
        opponent_cnt = tokens.count(HUMAN_IDENTIFICATION_VALUE)

        if counter == MAXIMUM_COUNTER:
            score += HIGH_SCORE
        elif opponent_cnt == NULL_COUNTER:
            if counter == PARTIAL_COUNTER_1:
                score += PARTIAL_SCORE_1
            elif counter == PARTIAL_COUNTER_2:
                score += PARTIAL_SCORE_2
        if opponent_cnt == PARTIAL_COUNTER_1 and counter == NULL_COUNTER:
            score -= REDUCED_SCORE

        return score

    def get_board_score(self, board: Board):
        score = INITIALIZATION_VALUE_ZERO

        for column in self.__columns_array:
            column_array = [i for i in list(board.board[:, column])]
            for row in range(HEIGHT - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1):
                tokens = column_array[row:row + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN]
                score += self.get_tokens_score(tokens)

        for row in range(HEIGHT):
            row_array = [i for i in list(board.board[row, :])]
            for column in range(WIDTH - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1):
                tokens = row_array[column:column + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN]
                score += self.get_tokens_score(tokens)

        for row in range(HEIGHT - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1):
            for column in range(WIDTH - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1):
                tokens = [board.board[row + i][column + i] for i in range(CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN)]
                score += self.get_tokens_score(tokens)

        for row in range(HEIGHT - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1):
            for column in range(WIDTH - CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN + 1):
                tokens = [board.board[row + CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN - 1 - i][column + i] for i in range(CONSECUTIVE_POSITIONS_IN_ORDER_TO_WIN)]
                score += self.get_tokens_score(tokens)

        return score

    def get_next_free_row(self, board, col):
        for row in range(HEIGHT):
            if board.board[row][col] == VALUE_OF_AN_EMPTY_POSITION:
                return row
        return NOT_AVAILABLE

    def is_location_valid(self, board: Board, col: int):
        return board.board[HEIGHT - 1][col] == VALUE_OF_AN_EMPTY_POSITION

    def get_valid_columns(self, board: Board):
        return [int(col) for col in self.__columns_array if self.is_location_valid(board, col)]

    def drop_piece(self, board: Board, column: int, player: int):
        board.board[self.get_next_free_row(board, column)][column] = player

    def terminal(self, board: Board):
        return (self.winning_move(board, AI_IDENTIFICATION_VALUE) or
                self.winning_move(board, HUMAN_IDENTIFICATION_VALUE) or
                len(self.get_valid_columns(board)) == EMPTY_LIST)

    def minimax_algorithm(self, board: Board, depth, current_best_score_maximizing_player, current_best_score_minimizing_player, maximizingPlayer):
        valid_columns = self.get_valid_columns(board)

        terminal = self.terminal(board)

        if depth == NULL_VALUE or terminal:
            if terminal:
                if self.winning_move(board, AI_IDENTIFICATION_VALUE):
                    return None, MAXIMUM_VALUE
                elif self.winning_move(board, HUMAN_IDENTIFICATION_VALUE):
                    return None, -MAXIMUM_VALUE
                else:
                    return None, NULL_VALUE
            else:
                return None, self.get_board_score(board)

        if maximizingPlayer:
            value = -math.inf
            column = valid_columns[FIRST_POSITION]

            if depth == self.__depth:
                for current_column in valid_columns:
                    new_board = copy.deepcopy(board)
                    self.drop_piece(new_board, current_column, AI_IDENTIFICATION_VALUE)
                    if self.winning_move(new_board, AI_IDENTIFICATION_VALUE):
                        return current_column, None

            for current_column in valid_columns:
                new_board = copy.deepcopy(board)
                self.drop_piece(new_board, current_column, AI_IDENTIFICATION_VALUE)
                new_score = self.minimax_algorithm(new_board, depth - 1, current_best_score_maximizing_player, current_best_score_minimizing_player, HUMAN_PLAYER)[SECOND_POSITION]

                if new_score > value:
                    value = new_score
                    column = current_column

                current_best_score_maximizing_player = max(current_best_score_maximizing_player, value)
                if current_best_score_maximizing_player >= current_best_score_minimizing_player:
                    break
            return column, value

        else:
            value = math.inf
            column = valid_columns[FIRST_POSITION]
            for current_column in valid_columns:
                new_board = copy.deepcopy(board)
                self.drop_piece(new_board, current_column, HUMAN_IDENTIFICATION_VALUE)
                new_score = self.minimax_algorithm(new_board, depth - 1, current_best_score_maximizing_player, current_best_score_minimizing_player, COMPUTER_PLAYER)[SECOND_POSITION]
                if new_score < value:
                    value = new_score
                    column = current_column
                current_best_score_minimizing_player = min(current_best_score_minimizing_player, value)
                if current_best_score_maximizing_player >= current_best_score_minimizing_player:
                    break
            return column, value
