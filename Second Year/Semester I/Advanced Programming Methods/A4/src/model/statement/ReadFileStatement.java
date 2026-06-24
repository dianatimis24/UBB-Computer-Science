package model.statement;

import exceptions.MyException;
import exceptions.MyInvalidFileFormatException;
import exceptions.MyKeyNotFoundException;
import model.expression.IExpression;
import model.state.ProgramState;
import model.state.symbolTable.ISymbolTable;
import model.type.StringType;
import model.value.IntValue;
import model.value.StringValue;
import model.value.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement {
    private final IExpression expression;
    private final String variableName;

    public ReadFileStatement(IExpression expression, String variableName) {
        this.expression = expression;
        this.variableName = variableName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        ISymbolTable symbolTable = state.getSymbolTable();
        if (!symbolTable.isDefined(this.variableName)) {
            throw new MyException("The variable " + this.variableName + " was not declared before.");
        }

        Value value;
        try {
            value = symbolTable.getValueForKey(this.variableName);
        } catch (MyKeyNotFoundException e) {
            throw new MyException("Variable " + this.variableName + " is not of type int.");
        }

        Value fileValue;
        try {
            fileValue = this.expression.evaluate(state.getSymbolTable(), state.getHeap());
        }
        catch (MyException e) {
            throw new MyException(e.getMessage());
        }
        if (!fileValue.getType().equals(new StringType())) {
            throw new MyException("The expression has to be a string value.");
        }
        StringValue stringValue = (StringValue) fileValue;
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
            String line = reader.readLine();
            IntValue val;
            if (line == null) {
                val = new IntValue(0);
            } else {
                try {
                    val = new IntValue(Integer.parseInt(line));
                } catch (NumberFormatException e) {
                    throw new MyInvalidFileFormatException();
                }
            }

            try {
                symbolTable.update(this.variableName, val);
            } catch (MyKeyNotFoundException e) {
                throw new MyException(e.getMessage());
            }
        } catch(IOException e) {
            throw new MyException("Error reading from file: " + e.getMessage());
        }
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new ReadFileStatement(this.expression.deepCopy(), variableName);
    }

    @Override
    public String toString() {
        return "readFile(" + this.expression.toString() + ", " + this.variableName + ")";
    }
}
