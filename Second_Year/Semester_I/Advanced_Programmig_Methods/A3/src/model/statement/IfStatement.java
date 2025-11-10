package model.statement;

import exceptions.ExpressionException;
import exceptions.MyException;
import model.expression.IExpression;
import model.state.ProgramState;
import model.type.BoolType;
import model.value.BoolValue;
import model.value.Value;

public class IfStatement implements IStatement {
    private final IExpression condition;
    private final IStatement thenStatement;
    private final IStatement elseStatement;

    public IfStatement(IExpression condition, IStatement thenStatement, IStatement elseStatement) {
        this.condition = condition;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Value value;
        try {
            value = this.condition.evaluate(state.getSymbolTable());
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }

        if (!(value.getType() instanceof BoolType)) {
            throw new MyException("The condition in the if statement is not bool.");
        }

        BoolValue boolValue = (BoolValue) value;
        if (boolValue.getValue())
            state.getExecutionStack().push(this.thenStatement);
        else
            state.getExecutionStack().push(this.elseStatement);
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new  IfStatement(this.condition.deepCopy(), this.thenStatement.deepCopy(), this.elseStatement.deepCopy());
    }

    @Override
    public String toString() {
        return "if(" + this.condition.toString() + ") then {" +
                this.thenStatement.toString() + "} else {" + this.elseStatement.toString() + "}";
    }
}
