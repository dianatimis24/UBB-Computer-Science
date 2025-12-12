package model.expression;

import exceptions.ExpressionException;
import exceptions.MyInvalidTypeException;
import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.state.heap.IHeap;
import model.state.symbolTable.ISymbolTable;
import model.type.BoolType;
import model.type.IntType;
import model.type.Type;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.Value;

public class RelationalExpression implements IExpression {
    private final String operation;
    private final IExpression expression1;
    private final IExpression expression2;

    public RelationalExpression(String operation, IExpression expression1, IExpression expression2) {
        this.operation = operation;
        this.expression1 = expression1;
        this.expression2 = expression2;
    }

    @Override
    public Value evaluate(ISymbolTable symbolTable, IHeap heap) throws MyException {
        Value value1, value2;

        try {
            value1 = this.expression1.evaluate(symbolTable, heap);
        } catch (ExpressionException e) {
            throw new MyException(e.getMessage());
        } catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        if (!(value1.getType().equals(new IntType()))) {
            throw new MyException("First operand is not an integer.");
        }

        try {
            value2 = this.expression2.evaluate(symbolTable, heap);
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
            case "<":
                return new BoolValue(n1 < n2);
            case "<=":
                return new BoolValue(n1 <= n2);
            case ">":
                return new BoolValue(n1 > n2);
            case ">=":
                return new BoolValue(n1 >= n2);
            case "==":
                return new BoolValue(n1 == n2);
            case "!=":
                return new BoolValue(n1 != n2);
            default:
                throw new MyException("Invalid relational operator!");
        }
    }

    @Override
    public Type typecheck(IDictionary<String, Type> typeEnvironment) throws MyException {
        Type type1 = this.expression1.typecheck(typeEnvironment);
        if (!type1.equals(new IntType())) {
            throw new MyInvalidTypeException("First operand is not an integer.");
        }

        Type type2 = this.expression2.typecheck(typeEnvironment);
        if (!type2.equals(new IntType())) {
            throw new MyInvalidTypeException("Second operand is not an integer.");
        }

        return new BoolType();
    }

    @Override
    public IExpression deepCopy() {
        return new RelationalExpression(this.operation, this.expression1.deepCopy(), this.expression2.deepCopy());
    }

    @Override
    public String toString() {
        return this.expression1.toString() + " " + this.operation + " " + this.expression2.toString();
    }
}
