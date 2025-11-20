class Repository:
    def __init__(self):
        self.__file_name = "C:\\Users\\user\\PycharmProjects\\scramble\\sentences"
        self.__all_sentences = []
        self.__load_data()

    def get_all(self):
        return self.__all_sentences

    def __load_data(self):
        with open(self.__file_name) as file:
            for line in file:
                line = line.strip()
                try:
                    self.add(line)
                except ValueError:
                    continue

    def add(self, sentence):
        if sentence in self.get_all():
            raise ValueError("This sentence already exists!")
        self.__all_sentences.append(sentence)
        with open(self.__file_name) as file:
            file.write(sentence + "\n")