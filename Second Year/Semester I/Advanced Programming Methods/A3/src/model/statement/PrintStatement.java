package model.statement;

import exceptions.ExpressionException;
import exceptions.MyException;
import model.expression.IExpression;
import model.state.ProgramState;
import model.value.Value;

public class PrintStatement implements IStatement {
    private final IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Value value;
        try {
            value = this.expression.evaluate(state.getSymbolTable());
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        state.getOutput().add(value.toString());
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new PrintStatement(this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "print(" + this.expression.toString() + ")";
    }
}
