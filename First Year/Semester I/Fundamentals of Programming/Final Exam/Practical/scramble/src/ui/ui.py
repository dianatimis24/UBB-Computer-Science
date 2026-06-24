from src.controller.controller import Controller


class UI:
    def __init__(self):
        self.__controller = Controller()

    def start_game(self):
        print("WELCOME TO SCRAMBLE!\n")
        sentence = self.__controller.choose_sentence()
        output = self.__controller.shuffle(sentence)
        sentence_letters = list(sentence)
        score = len(sentence_letters)
        for letter in sentence_letters:
            if letter == " ":
                score -= 1
        print(f"Sentence: {output} [score is: {score}]")

        old_output = output
        while True:
            while True:
                try:
                    print()
                    command_string = input("Command > ")
                    print()
                    break
                except ValueError as ve:
                    print("Invalid command!", ve)
            command = command_string.split(" ")
            if len(command) > 3:
                if command[0] == "swap" and command[3] == "-":
                    if command[1].isnumeric() and command[2].isnumeric() and command[4].isnumeric() and command[5].isnumeric():
                        word1 = int(command[1]) - 1
                        letter1 = int(command[2]) - 1
                        word2 = int(command[4]) - 1
                        letter2 = int(command[5]) - 1
                        old_output = output
                        try:
                            output = self.__controller.swap(output, word1, letter1, word2, letter2)
                        except ValueError as ve:
                            print(ve)
                            continue
                        score -= 1
                        print(f"Sentence: {output} [score is: {score}]")
                        if output.strip() == sentence.strip():
                            print("YOU WON!")
                            break
                        elif score == 0:
                            print("YOU LOSE!")
                            break
                    else:
                        print("Invalid input for command swap!\n")
                        print(f"Sentence: {output} [score is: {score}]")
            elif command[0] == "undo":
                output = old_output
                print(f"Sentence: {output} [score is: {score}]")
            else:
                print("Invalid command!")
