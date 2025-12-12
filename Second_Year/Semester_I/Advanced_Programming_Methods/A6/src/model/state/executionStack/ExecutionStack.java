package model.state.executionStack;

import exceptions.MyEmptyStackException;
import exceptions.MyException;
import model.ADTs.stack.IStack;
import model.ADTs.stack.MyStack;
import model.statement.IStatement;

public class ExecutionStack implements IExecutionStack {
    private final IStack<IStatement> stack;

    public ExecutionStack() {
        this.stack = new MyStack<>();
    }

    @Override
    public IStatement pop() throws MyEmptyStackException {
        return this.stack.pop();
    }

    @Override
    public void push(IStatement statement) {
        this.stack.push(statement);
    }

    @Override
    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public int size() {
        return this.stack.size();
    }

    @Override
    public String toString() {
        StringBuilder answer = new StringBuilder("Execution stack:\n");
        IStack<IStatement> tmpStack = new MyStack<>();
        try {
            while (!this.stack.isEmpty()) {
                tmpStack.push(this.stack.pop());
                answer.append(tmpStack.top().toString()).append('\n');
            }
            while (!tmpStack.isEmpty()) {
                this.stack.push(tmpStack.pop());
            }
        } catch (MyException exception) {
            throw new RuntimeException(exception.getMessage());
        }
        return answer.toString();
    }
}
