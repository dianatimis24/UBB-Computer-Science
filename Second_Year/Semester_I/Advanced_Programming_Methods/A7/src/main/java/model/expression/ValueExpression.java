package model.expression;

import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.state.heap.IHeap;
import model.state.symbolTable.ISymbolTable;
import model.type.Type;
import model.value.Value;

public class ValueExpression implements IExpression {
    private final Value value;

    public ValueExpression(Value value) {
        this.value = value;
    }

    @Override
    public Value evaluate(ISymbolTable symbolTable, IHeap heap) throws MyException {
        return this.value;
    }

    @Override
    public Type typecheck(IDictionary<String, Type> typeEnvironment) throws MyException {
        return this.value.getType();
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
