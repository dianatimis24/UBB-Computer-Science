package model.expression;

import exceptions.ExpressionException;
import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.type.IntType;
import model.value.IntValue;
import model.value.Value;

public class ArithmeticExpression implements IExpression {
    private final char operation;
    private final IExpression expression1;
    private final IExpression expression2;

    public ArithmeticExpression(char operation, IExpression expression1, IExpression expression2) {
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
        if (!(value1.getType().equals(new IntType()))) {
            throw new MyException("First operand is not an integer.");
        }

        try {
            value2 = this.expression2.evaluate(symbolTable);
        } catch (ExpressionException e) {
            throw new MyException(e.getMessage());
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        if (!(value2.getType().equals(new IntType()))) {
            throw new MyException("Second operand is not an integer.");
        }

        IntValue i1 = (IntValue) value1;
        IntValue i2 = (IntValue) value2;
        int n1, n2;
        n1 = i1.getValue();
        n2 = i2.getValue();
        switch (this.operation) {
            case '+':
                return new IntValue(n1 + n2);
            case '-':
                return new IntValue(n1 - n2);
            case '*':
                return new IntValue(n1 * n2);
            case '/':
                if (n2 == 0)
                    throw new ExpressionException("Division by zero.");
                return new IntValue(n1 / n2);
            default:
                throw new MyException("Invalid arithmetic operator.");
        }
    }

    @Override
    public IExpression deepCopy() {
        return new ArithmeticExpression(this.operation, this.expression1.deepCopy(), this.expression2.deepCopy());
    }

    @Override
    public String toString() {
        return this.expression1.toString() + " " + this.operation + " " + this.expression2.toString();
    }
}
