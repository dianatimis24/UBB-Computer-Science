package model.statement;

import exceptions.MyException;
import model.expression.IExpression;
import model.state.ProgramState;
import model.state.heap.IHeap;
import model.state.symbolTable.ISymbolTable;
import model.type.ReferenceType;
import model.type.Type;
import model.value.ReferenceValue;
import model.value.Value;

public class NewStatement implements IStatement {
    private final String variableName;
    private final IExpression expression;

    public NewStatement(String variableName, IExpression expression) {
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

        Type type;
        try {
            type = symbolTable.getValueForKey(this.variableName).getType();
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        if (!(type instanceof ReferenceType)) {
            throw new MyException("The variable " + this.variableName + " is not of type ReferenceType.");
        }

        Value value;
        try {
            value = this.expression.evaluate(symbolTable, heap);
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        if (!value.getType().equals(((ReferenceType) type).getInner())) {
         throw new MyException("Type mismatch: expected " + ((ReferenceType) type).getInner().toString()
                 + " but got " + value.getType().toString() + ".");
        }

        int newAddress = heap.insert(value);
        state.getSymbolTable().update(this.variableName, new ReferenceValue(newAddress, value.getType()));
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new NewStatement(this.variableName, this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "new(" + this.variableName + ", " + this.expression.toString() + ")";
    }
}
