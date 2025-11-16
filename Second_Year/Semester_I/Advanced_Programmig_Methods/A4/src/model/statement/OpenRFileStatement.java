package model.statement;

import exceptions.ExpressionException;
import exceptions.MyException;
import exceptions.MyFileAlreadyOpenedException;
import model.expression.IExpression;
import model.state.ProgramState;
import model.type.StringType;
import model.value.StringValue;
import model.value.Value;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenRFileStatement implements IStatement {
    private final IExpression expression;

    public OpenRFileStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Value value;
        try {
            value = this.expression.evaluate(state.getSymbolTable(), state.getHeap());
        }
        catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        if (!value.getType().equals(new StringType())) {
            throw new MyException("The expression has to be a string value.");
        }
        StringValue stringValue = (StringValue) value;
        String filename = stringValue.getValue();
        if (state.getFileTable().isDefined(filename)) {
            throw new MyFileAlreadyOpenedException("File " + filename + " already open for reading.");
        }

        try {
            BufferedReader reader = new BufferedReader(new FileReader(stringValue.getValue()));
            state.getFileTable().insert(filename, reader);
        } catch (FileNotFoundException e) {
            throw new MyException("File not found: " + e.getMessage());
        }
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new OpenRFileStatement(this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "openRFile(" + this.expression.toString() + ")";
    }
}
