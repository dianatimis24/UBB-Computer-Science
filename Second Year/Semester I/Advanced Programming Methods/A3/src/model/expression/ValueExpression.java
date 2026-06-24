package model.expression;

import exceptions.ExpressionException;
import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.state.symbolTable.ISymbolTable;
import model.value.Value;

public class ValueExpression implements IExpression {
    private final Value value;

    public ValueExpression(Value value) {
        this.value = value;
    }

    @Override
    public Value evaluate(ISymbolTable symbolTable) throws MyException {
        return this.value;
    }

    @Override
    public IExpression deepCopy() {
        return new ValueExpression(this.value.deepCopy());
    }

    @Override
    public String toString() {
        return this.value.toString();
    }
}
