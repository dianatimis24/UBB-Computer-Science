package model.state.fileTable;

import exceptions.MyException;
import exceptions.MyKeyNotFoundException;

import java.io.BufferedReader;

public interface IFileTable {
    boolean isDefined(String filename);
    void insert(String filename, BufferedReader reader);
    BufferedReader getFile(String filename) throws MyKeyNotFoundException;
    void remove(String filename) throws MyKeyNotFoundException;
    String toString();
}
