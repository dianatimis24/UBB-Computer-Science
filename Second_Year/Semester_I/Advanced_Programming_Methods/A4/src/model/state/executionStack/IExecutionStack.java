package model.state.executionStack;

import exceptions.MyEmptyStackException;
import model.statement.IStatement;

public interface IExecutionStack {
    IStatement pop() throws MyEmptyStackException;
    void push(IStatement statement);
    boolean isEmpty();
    int size();
    String toString();
}
