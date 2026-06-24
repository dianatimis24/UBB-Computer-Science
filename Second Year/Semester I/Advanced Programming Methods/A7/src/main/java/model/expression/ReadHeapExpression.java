package model.expression;

import exceptions.ExpressionException;
import exceptions.MyException;
import exceptions.MyInvalidTypeException;
import exceptions.MyKeyNotFoundException;
import model.ADTs.dictionary.IDictionary;
import model.state.heap.IHeap;
import model.state.symbolTable.ISymbolTable;
import model.type.ReferenceType;
import model.type.Type;
import model.value.ReferenceValue;
import model.value.Value;

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
    public Type typecheck(IDictionary<String, Type> typeEnvironment) throws MyException {
        Type type = this.expression.typecheck(typeEnvironment);
        if (!(type instanceof ReferenceType referenceType)) {
            throw new MyInvalidTypeException("The expression is not a ReferenceType.");
        }
        return referenceType.getInner();
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
