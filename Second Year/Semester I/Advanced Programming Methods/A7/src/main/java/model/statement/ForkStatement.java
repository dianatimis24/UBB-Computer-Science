package model.statement;

import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.state.ProgramState;
import model.state.executionStack.ExecutionStack;
import model.type.Type;

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
    public IDictionary<String, Type> typecheck(IDictionary<String, Type> typeEnvironment) throws MyException {
        this.statement.typecheck(typeEnvironment.deepcopy());
        return typeEnvironment;
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
