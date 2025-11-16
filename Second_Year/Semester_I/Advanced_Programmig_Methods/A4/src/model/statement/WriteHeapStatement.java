package model.statement;

import exceptions.MyException;
import model.expression.IExpression;
import model.state.ProgramState;
import model.state.heap.IHeap;
import model.state.symbolTable.ISymbolTable;
import model.type.ReferenceType;
import model.value.ReferenceValue;
import model.value.Value;

public class WriteHeapStatement implements IStatement {
    private final String variableName;
    private final IExpression expression;

    public WriteHeapStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        ISymbolTable symbolTable = state.getSymbolTable();
        IHeap heap = state.getHeap();
        if (!symbolTable.isDefined(this.variableName)) {
            throw new MyException("The variable " + this.variableName + " was not declared before.");
        }

        Value variableValue;
        try {
            variableValue = symbolTable.getValueForKey(this.variableName);
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        if (!(variableValue instanceof ReferenceValue)) {
            throw new MyException("The variable " + this.variableName + " is not of ReferenceType.");
        }

        ReferenceValue referenceValue = (ReferenceValue) variableValue;
        Integer address = referenceValue.getAddress();
        if (!heap.isDefined(address)) {
            throw new MyException("The address " + address + " is not allocated in the heap.");
        }

        Value value;
        try {
            value = this.expression.evaluate(symbolTable, heap);
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }

        if (!value.getType().equals(((ReferenceType) referenceValue.getType()).getInner())) {
            throw new MyException("The type of expression and the type of variable do not match.");
        }
        heap.update(address, value);
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new WriteHeapStatement(this.variableName, this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "writeHeap(" + this.variableName + ", " + this.expression.toString() + ")";
    }
}
