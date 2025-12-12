package model.statement;

import exceptions.MyException;
import model.expression.IExpression;
import model.state.ProgramState;
import model.type.BoolType;
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
    public IStatement deepCopy() {
        return new WhileStatement(this.condition.deepCopy(), this.statement.deepCopy());
    }

    @Override
    public String toString() {
        return "While(" + this.condition.toString() + "){" + this.statement.toString() + "};";
    }
}
