package model.state;


import model.state.executionStack.IExecutionStack;
import model.state.fileTable.IFileTable;
import model.state.heap.IHeap;
import model.state.output.IOutput;
import model.state.symbolTable.ISymbolTable;
import model.statement.IStatement;


public class ProgramState {
    private final IExecutionStack executionStack;
    private final ISymbolTable symbolTable;
    private final IOutput output;
    private final IFileTable fileTable;
    private final IHeap heap;
    private final IStatement originalStatement;

    public ProgramState(IExecutionStack executionStack, ISymbolTable symbolTable, IOutput output, IFileTable fileTable, IHeap heap, IStatement originalStatement) {
        this.executionStack = executionStack;
        this.symbolTable = symbolTable;
        this.output = output;
        this.fileTable = fileTable;
        this.heap = heap;
        this.originalStatement = originalStatement.deepCopy();
        this.executionStack.push(originalStatement);
    }

    public IExecutionStack getExecutionStack() {
        return this.executionStack;
    }

    public ISymbolTable getSymbolTable() {
        return this.symbolTable;
    }

    public IOutput getOutput() {
        return this.output;
    }

    public IFileTable getFileTable() {
        return this.fileTable;
    }

    public IHeap getHeap() {
        return this.heap;
    }

    @Override
    public String toString() {
        return this.executionStack.toString().strip() + "\n" +
                this.symbolTable.toString().strip() + "\n" +
                this.output.toString().strip() + "\n" +
                this.fileTable.toString().strip() + "\n" +
                this.heap.toString().strip() + "\n" +
                "OriginalProgram: " + this.originalStatement.toString() + "\n";
    }
}
