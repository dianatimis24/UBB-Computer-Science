package model.statement;

import exceptions.MyException;
import exceptions.MyFileOperationException;
import exceptions.MyKeyNotFoundException;
import model.expression.IExpression;
import model.state.ProgramState;
import model.type.StringType;
import model.value.StringValue;
import model.value.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseFileStatement implements IStatement {
    private final IExpression expression;

    public CloseFileStatement(IExpression expression) {
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

        BufferedReader reader;
        try {
            reader = state.getFileTable().getFile(filename);
        } catch (MyKeyNotFoundException e) {
            throw new MyException(e.getMessage());
        }
        if (reader == null) {
            throw new MyException("The file " + filename + " does not exist.");
        }
        try {
            reader.close();
        } catch(IOException e) {
            throw new MyFileOperationException("Error closing file: " + e.getMessage());
        }
        try {
            state.getFileTable().remove(filename);
        } catch (MyKeyNotFoundException e) {
            throw new MyFileOperationException("File " + filename + " cannot be closed");
        }
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new CloseFileStatement(this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "closeRFile(" + this.expression.toString() + ")";
    }
}
