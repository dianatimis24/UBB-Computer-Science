package model.state;


import exceptions.MyEmptyStackException;
import exceptions.MyException;
import model.state.executionStack.ExecutionStack;
import model.state.executionStack.IExecutionStack;
import model.state.fileTable.FileTable;
import model.state.fileTable.IFileTable;
import model.state.heap.Heap;
import model.state.heap.IHeap;
import model.state.output.IOutput;
import model.state.output.Output;
import model.state.symbolTable.ISymbolTable;
import model.state.symbolTable.SymbolTable;
import model.statement.IStatement;


public class ProgramState {
    private static int availableId = 0;

    private final int id;
    private IExecutionStack executionStack;
    private ISymbolTable symbolTable;
    private IOutput output;
    private IFileTable fileTable;
    private IHeap heap;
    private final IStatement originalStatement;

    public ProgramState(IExecutionStack executionStack, ISymbolTable symbolTable, IOutput output, IFileTable fileTable, IHeap heap, IStatement originalStatement) {
        this.id = ProgramState.getNextId();
        this.executionStack = executionStack;
        this.symbolTable = symbolTable;
        this.output = output;
        this.fileTable = fileTable;
        this.heap = heap;
        this.originalStatement = originalStatement.deepCopy();
        this.executionStack.push(originalStatement);
    }

    private synchronized static int getNextId() {
        ProgramState.availableId++;
        return ProgramState.availableId;
    }

    public int getId() {
        return this.id;
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

    public IStatement getOriginalStatement() {
        return this.originalStatement;
    }

    public void resetToOriginalProgram() {
        this.executionStack = new ExecutionStack();
        this.output = new Output();
        this.symbolTable = new SymbolTable();
        this.fileTable = new FileTable();
        this.heap = new Heap();
        IStatement program = this.originalStatement.deepCopy();
        this.executionStack.push(program);
    }

    public Boolean isNotCompleted() {
        return (!this.executionStack.isEmpty());
    }

    public ProgramState executeStep() throws MyException {
        if (this.executionStack.isEmpty()) {
            throw new MyEmptyStackException();
        }

        IStatement currentStatement = this.executionStack.pop();
        return currentStatement.execute(this);
    }

    @Override
    public String toString() {
        return this.id + ": ProgramState{\n" +
                this.executionStack.toString().strip() + "\n" +
                this.symbolTable.toString().strip() + "\n" +
                this.output.toString().strip() + "\n" +
                this.fileTable.toString().strip() + "\n" +
                this.heap.toString().strip() + "\n}\n";
    }
}
