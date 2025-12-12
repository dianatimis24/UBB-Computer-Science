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

public class WhileStatement implements IStatement {
    private final IExpression condition;
    private final IStatement statement;

    public WhileStatement(IExpression condition, IStatement statement) {
        this.condition = condition;
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Value value;
        try {
            value = this.condition.evaluate(state.getSymbolTable(), state.getHeap());
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        if (!value.getType().equals(new BoolType())) {
            throw new MyException("While condition should evaluated to a BoolType.");
        }

        BoolValue boolValue = (BoolValue) value;
        if (boolValue.getValue()) {
            state.getExecutionStack().push(this);
            state.getExecutionStack().push(this.statement);
        }
        return null;
    }

    @Override
    public IDictionary<String, Type> typecheck(IDictionary<String, Type> typeEnvironment) throws MyException {
        Type conditionType = this.condition.typecheck(typeEnvironment);
        if (!conditionType.equals(new BoolType())) {
            throw new MyInvalidTypeException("The condition in the WHILE statement is not boolean.");
        }
        this.statement.typecheck(typeEnvironment.deepcopy());
        return typeEnvironment;
    }

    @Override
    public IStatement deepCopy() {
        return new WhileStatement(this.condition.deepCopy(), this.statement.deepCopy());
    }

    @Override
    public String toString() {
        return "While(" + this.condition.toString() + "){" + this.statement.toString() + "};";
    }
}
