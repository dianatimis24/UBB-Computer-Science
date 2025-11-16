package controller;

import exceptions.MyEmptyStackException;
import exceptions.MyException;
import model.state.ProgramState;
import model.state.executionStack.IExecutionStack;
import model.statement.IStatement;
import model.value.ReferenceValue;
import model.value.Value;
import repository.IRepository;

import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Controller implements IController {
    private final IRepository repository;
    private boolean displayFlag = false;

    public Controller(IRepository repository, boolean displayFlag) {
        this.repository = repository;
        this.displayFlag = displayFlag;
    }

    public boolean getDisplayFlag() {
        return this.displayFlag;
    }

    public void setDisplayFlag(boolean displayFlag) {
        this.displayFlag = displayFlag;
    }

    @Override
    public void addProgramState(ProgramState programState) {
        this.repository.addProgramState(programState);
    }

    @Override
    public void displayCurrentProgramState() {
        if (this.displayFlag) {
            IO.println(this.repository.getCurrentProgramState().toString());
        }
    }

    public Map<Integer, Value> safeGarbageCollector(List<Integer> symbolTableAddresses, List<Integer> heapAddresses, Map<Integer,Value> heap) {
        return heap.entrySet().stream()
                .filter(elem -> (symbolTableAddresses.contains(elem.getKey()) || heapAddresses.contains(elem.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public List<Integer> getAddressesFromSymbolTable(Collection<Value> symbolTableValues) {
        return symbolTableValues.stream()
                .filter(v -> v instanceof ReferenceValue)
                .map(v -> {ReferenceValue v1 = (ReferenceValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    public List<Integer> getAddressesFromHeap(Collection<Value> heapValues) {
        return heapValues.stream()
                .filter(v -> v instanceof ReferenceValue)
                .map(v -> {ReferenceValue v1 = (ReferenceValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    @Override
    public ProgramState executeOneStep(ProgramState state) throws MyException {
        IExecutionStack executionStack = state.getExecutionStack();
        if (executionStack.isEmpty()) {
            throw new MyException("The execution stack is empty.");
        }

        IStatement currentStatement;
        try {
            currentStatement = executionStack.pop();
        } catch (MyEmptyStackException e) {
            throw new MyException(e.getMessage());
        }
        return currentStatement.execute(state);
    }

    @Override
    public void executeAllSteps() throws MyException {
        ProgramState currentProgramState = repository.getCurrentProgramState();
        displayCurrentProgramState();
        this.repository.logProgramStateExecution(currentProgramState);
        while (!currentProgramState.getExecutionStack().isEmpty()) {
            currentProgramState = executeOneStep(currentProgramState);
            this.repository.logProgramStateExecution(currentProgramState);
            currentProgramState.getHeap().setContent((HashMap<Integer, Value>) safeGarbageCollector(
                    getAddressesFromSymbolTable(currentProgramState.getSymbolTable().getMap().values()),
                    getAddressesFromHeap(currentProgramState.getHeap().getContent().values()),
                    currentProgramState.getHeap().getContent()));

            this.repository.logProgramStateExecution(currentProgramState);
            displayCurrentProgramState();
        }
    }
}
