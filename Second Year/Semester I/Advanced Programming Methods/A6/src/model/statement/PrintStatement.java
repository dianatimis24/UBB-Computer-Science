package model.statement;

import exceptions.ExpressionException;
import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.expression.IExpression;
import model.state.ProgramState;
import model.type.Type;
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
            value = this.expression.evaluate(state.getSymbolTable(), state.getHeap());
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        state.getOutput().add(value.toString());
        return null;
    }

    @Override
    public IDictionary<String, Type> typecheck(IDictionary<String, Type> typeEnvironment) throws MyException {
        this.expression.typecheck(typeEnvironment);
        return typeEnvironment;
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
