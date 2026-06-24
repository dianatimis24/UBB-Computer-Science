package model.statement;

import exceptions.MyException;
import exceptions.MyInvalidTypeException;
import model.ADTs.dictionary.IDictionary;
import model.expression.IExpression;
import model.state.ProgramState;
import model.type.BoolType;
import model.type.Type;
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
            value = this.condition.evaluate(state.getSymbolTable(), state.getHeap());
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
        return null;
    }

    @Override
    public IDictionary<String, Type> typecheck(IDictionary<String, Type> typeEnvironment) throws MyException {
        Type conditionType = this.condition.typecheck(typeEnvironment);
        if (!conditionType.equals(new BoolType())) {
            throw new MyInvalidTypeException("The condition in the IF statement is not boolean.");
        }
        this.thenStatement.typecheck(typeEnvironment.deepcopy());
        this.elseStatement.typecheck(typeEnvironment.deepcopy());
        return typeEnvironment;
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
