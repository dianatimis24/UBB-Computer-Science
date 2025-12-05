package model.statement;

import exceptions.MyException;
import model.state.ProgramState;
import model.state.executionStack.ExecutionStack;
import model.state.executionStack.IExecutionStack;

public class ForkStatement implements IStatement {
    private final IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        return new ProgramState(
                new ExecutionStack(),
                state.getSymbolTable().deepCopy(),
                state.getOutput(),
                state.getFileTable(),
                state.getHeap(),
                this.statement);
    }

    @Override
    public IStatement deepCopy() {
        return new ForkStatement(this.statement.deepCopy());
    }

    @Override
    public String toString() {
        return "fork(" + this.statement.toString() + ")";
    }
}
