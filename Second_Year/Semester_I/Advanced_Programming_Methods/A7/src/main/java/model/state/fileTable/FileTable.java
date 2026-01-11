package model.state.fileTable;

import exceptions.MyKeyNotFoundException;
import model.ADTs.dictionary.IDictionary;
import model.ADTs.dictionary.MySynchronizedDictionary;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;


public class FileTable implements IFileTable {
    private final IDictionary<String, BufferedReader> files = new MySynchronizedDictionary<>();

    @Override
    public synchronized boolean isDefined(String filename) {
        return this.files.isDefined(filename);
    }

    @Override
    public synchronized void insert(String filename, BufferedReader reader) {
        this.files.insert(filename, reader);
    }

    @Override
    public synchronized BufferedReader getFile(String filename) throws MyKeyNotFoundException {
        return this.files.getValueForKey(filename);
    }

    @Override
    public List<BufferedReader> getFiles() {
        return new ArrayList<>(this.files.getAllValues());
    }

    @Override
    public synchronized void remove(String filename) throws MyKeyNotFoundException {
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
