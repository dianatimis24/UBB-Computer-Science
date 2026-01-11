package model.state.fileTable;

import exceptions.MyKeyNotFoundException;

import java.io.BufferedReader;
import java.util.List;

public interface IFileTable {
    boolean isDefined(String filename);
    void insert(String filename, BufferedReader reader);
    BufferedReader getFile(String filename) throws MyKeyNotFoundException;
    List<BufferedReader> getFiles();
    void remove(String filename) throws MyKeyNotFoundException;
    String toString();
}
