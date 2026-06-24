package model.expression;

import exceptions.ExpressionException;
import exceptions.MyException;
import exceptions.MyKeyNotFoundException;
import model.state.heap.IHeap;
import model.state.symbolTable.ISymbolTable;
import model.value.ReferenceValue;
import model.value.Value;

import java.beans.Expression;

public class ReadHeapExpression implements IExpression {
    private final IExpression expression;

    public ReadHeapExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public Value evaluate(ISymbolTable symbolTable, IHeap heap) throws MyException {
        Value value;
        try {
            value = this.expression.evaluate(symbolTable, heap);
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        if (!(value instanceof ReferenceValue)) {
            throw new ExpressionException("Expected a ReferenceValue, got a " + value.toString() + ".");
        }

        ReferenceValue referenceValue = (ReferenceValue) value;
        Integer address = referenceValue.getAddress();
        if (!heap.isDefined(address)) {
            throw new ExpressionException("The address " + address + " is not defined in the heap.");
        }
        try {
            return heap.getValueForKey(address);
        } catch (MyKeyNotFoundException e) {
            throw new MyException(e.getMessage());
        }
    }

    @Override
    public IExpression deepCopy() {
        return new ReadHeapExpression(this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "ReadHeapExpression(" + this.expression.toString() + ")";
    }
}
