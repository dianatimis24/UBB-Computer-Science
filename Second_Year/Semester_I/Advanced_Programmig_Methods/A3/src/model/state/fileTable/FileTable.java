package model.state.fileTable;

import exceptions.*;
import model.ADTs.dictionary.IDictionary;
import model.ADTs.dictionary.MyDictionary;

import java.io.BufferedReader;


public class FileTable implements IFileTable {
    IDictionary<String, BufferedReader> files;

    public FileTable() {
        this.files = new MyDictionary<>();
    }

    @Override
    public boolean isDefined(String filename) {
        return this.files.isDefined(filename);
    }

    @Override
    public void insert(String filename, BufferedReader reader) {
        this.files.insert(filename, reader);
    }

    @Override
    public BufferedReader getFile(String filename) throws MyKeyNotFoundException {
        return this.files.getValueForKey(filename);
    }

    @Override
    public void remove(String filename) throws MyKeyNotFoundException {
        this.files.remove(filename);
    }

    @Override
    public String toString() {
        StringBuilder answer = new StringBuilder("FileTable:\n");
        for (String name : this.files.getAllKeys()) {
            answer.append(name).append("\n");
        }
        return answer.toString();
    }
}
