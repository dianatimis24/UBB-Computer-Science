package model.state;

import model.ADTs.dictionary.IDictionary;
import model.ADTs.list.IList;
import model.ADTs.stack.IStack;
import model.statement.IStatement;
import model.value.Value;

public class ProgramState {
    private final IStack<IStatement> executionStack;
    private final IDictionary<String, Value> symbolTable;
    private final IList<Value> output;
    private final IStatement originalStatement;

    public ProgramState(IStack<IStatement> executionStack, IDictionary<String, Value> symbolTable, IList<Value> output, IStatement originalStatement) {
        this.executionStack = executionStack;
        this.symbolTable = symbolTable;
        this.output = output;
        this.originalStatement = originalStatement.deepCopy();
        this.executionStack.push(originalStatement);
    }

    public IStack<IStatement> getExecutionStack() {
        return this.executionStack;
    }

    public IDictionary<String, Value> getSymbolTable() {
        return this.symbolTable;
    }

    public IList<Value> getOutput() {
        return this.output;
    }

    @Override
    public String toString() {
        return "ProgramState{\n" + "ExecutionStack=" + this.executionStack.toList() +
                ",\nSymbolTable=" + this.symbolTable + ",\nOutput=" + this.output +
                ",\nOriginalProgram=" + this.originalStatement + "\n}";
    }
}
