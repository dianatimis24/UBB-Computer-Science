package model.statement;

import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.ADTs.stack.IStack;
import model.ADTs.stack.MyStack;
import model.state.ProgramState;
import model.state.executionStack.IExecutionStack;
import model.type.Type;

public class CompoundStatement implements IStatement {
    private final IStatement firstStatement;
    private final IStatement secondStatement;

    public CompoundStatement(IStatement firstStatement, IStatement secondStatement) {
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        IExecutionStack executionStack = state.getExecutionStack();
        executionStack.push(this.secondStatement);
        executionStack.push(this.firstStatement);
        return null;
    }

    @Override
    public IDictionary<String, Type> typecheck(IDictionary<String, Type> typeEnvironment) throws MyException {
        return this.secondStatement.typecheck(this.firstStatement.typecheck(typeEnvironment));
    }

    @Override
    public IStatement deepCopy() {
        return new CompoundStatement(this.firstStatement.deepCopy(), this.secondStatement.deepCopy());
    }

    @Override
    public String toString() {
        return "(" + this.firstStatement.toString() + ";" + this.secondStatement.toString() + ")";
    }
}
