package model.statement;

import model.ADTs.dictionary.IDictionary;
import exceptions.MyKeyNotFoundException;
import exceptions.ExpressionException;
import exceptions.MyException;
import model.expression.IExpression;
import model.state.ProgramState;
import model.state.symbolTable.ISymbolTable;
import model.value.Value;

public class AssignmentStatement implements IStatement {
    private final String variableName;
    private final IExpression expression;

    public AssignmentStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        ISymbolTable symbolTable = state.getSymbolTable();
        if (!symbolTable.isDefined(this.variableName)) {
            throw new MyException("The variable " + this.variableName + " was not declared before.");
        }

        Value value;
        try {
            value = this.expression.evaluate(symbolTable, state.getHeap());
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        try {
            if (value.getType().equals(symbolTable.getValueForKey(this.variableName).getType()))
                symbolTable.update(this.variableName, value);
            else {
                throw new MyException("The declared type of the variable " + this.variableName + " and the type of the expression are different.");
            }
        } catch (MyKeyNotFoundException e) {
            throw new MyException(e.getMessage());
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new AssignmentStatement(this.variableName, this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return this.variableName + " = " + this.expression.toString();
    }
}
