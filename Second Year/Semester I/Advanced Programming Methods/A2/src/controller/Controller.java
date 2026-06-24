package controller;

import exceptions.MyEmptyStackException;
import exceptions.MyException;
import model.ADTs.stack.IStack;
import model.ADTs.stack.MyStack;
import model.state.ProgramState;
import model.statement.IStatement;
import repository.IRepository;

public class Controller implements IController {
    private final IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    @Override
    public void addProgramState(ProgramState programState) {
        this.repository.addProgramState(programState);
    }

    @Override
    public void displayCurrentProgramState() {
        IO.println(this.repository.getCurrentProgramState());
    }

    @Override
    public ProgramState executeOneStep(ProgramState state) throws MyException {
        IStack<IStatement> executionStack = state.getExecutionStack();
        if (executionStack.isEmpty()) {
            throw new MyException("Execution stack is empty.");
        }

        IStatement currentStatement;
        try {
            currentStatement = executionStack.pop();
        } catch (MyEmptyStackException e) {
            throw new MyException(e.getMessage());
        }
        return currentStatement.execute(state);
    }

    @Override
    public void executeAllSteps() throws MyException {
        ProgramState programState = repository.getCurrentProgramState();
        System.out.println(programState);
        while (!programState.getExecutionStack().isEmpty()) {
            programState = executeOneStep(programState);
            System.out.println(programState);
        }
    }
}
