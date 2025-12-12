package model.expression;

import exceptions.MyKeyNotFoundException;
import exceptions.ExpressionException;
import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.state.heap.IHeap;
import model.state.symbolTable.ISymbolTable;
import model.value.Value;

public class VariableExpression implements IExpression {
    private final String variableName;

    public VariableExpression(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public Value evaluate(ISymbolTable symbolTable, IHeap heap) throws MyException {
        if (!symbolTable.isDefined(this.variableName)) {
            throw new MyException("The variable " + this.variableName + " was not declared before.");
        }

        try {
            return symbolTable.getValueForKey(this.variableName);
        } catch (MyKeyNotFoundException e) {
            throw new MyException(e.getMessage());
        }
    }

    @Override
    public IExpression deepCopy() {
        return new VariableExpression(this.variableName);
    }

    @Override
    public String toString() {
        return this.variableName;
    }
}
