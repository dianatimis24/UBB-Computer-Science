package model.expression;

import exceptions.ExpressionException;
import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.statement.IStatement;
import model.type.BoolType;
import model.value.BoolValue;
import model.value.Value;

public class LogicalExpression implements IExpression {
    private final String operation;
    private final IExpression expression1;
    private final IExpression expression2;

    public LogicalExpression(String operation, IExpression expression1, IExpression expression2) {
        this.operation = operation;
        this.expression1 = expression1;
        this.expression2 = expression2;
    }

    @Override
    public Value evaluate(IDictionary<String, Value> symbolTable) throws Exception {
        Value value1, value2;

        try {
            value1 = this.expression1.evaluate(symbolTable);
        } catch (ExpressionException e) {
            throw new MyException(e.getMessage());
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        if (!(value1.getType().equals(new BoolType()))) {
            throw new MyException("First operand is not a boolean.");
        }

        try {
            value2 = this.expression2.evaluate(symbolTable);
        } catch (ExpressionException e) {
            throw new MyException(e.getMessage());
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        if (!(value2.getType().equals(new BoolType()))) {
            throw new MyException("Second operand is not a boolean.");
        }

        BoolValue b1 = (BoolValue) value1;
        BoolValue b2 = (BoolValue) value2;
        boolean n1, n2;
        n1 = Boolean.parseBoolean(b1.toString());
        n2 = Boolean.parseBoolean(b2.toString());
        if (this.operation.equals("&&")) {
            return new BoolValue(n1 && n2);
        } else if (this.operation.equals("||")) {
            return new BoolValue(n1 || n2);
        } else {
            throw new MyException("Invalid logical operator.");
        }
    }

    @Override
    public IExpression deepCopy() {
        return new LogicalExpression(this.operation, this.expression1.deepCopy(), this.expression2.deepCopy());
    }

    @Override
    public String toString() {
        return this.expression1.toString() + " " + this.operation + " " + this.expression2.toString();
    }
}
