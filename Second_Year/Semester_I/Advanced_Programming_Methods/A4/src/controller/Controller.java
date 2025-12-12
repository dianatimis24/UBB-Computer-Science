package controller;

import exceptions.MyEmptyStackException;
import exceptions.MyException;
import model.state.ProgramState;
import model.state.executionStack.IExecutionStack;
import model.statement.IStatement;
import model.value.ReferenceValue;
import model.value.Value;
import repository.IRepository;

import java.util.*;
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

    public Set<Integer> getAddressesFromSymbolTable(Collection<Value> symbolTableValues) {
        return symbolTableValues.stream()
                .filter(v -> v instanceof ReferenceValue)
                .map(v -> {ReferenceValue v1 = (ReferenceValue) v; return v1.getAddress();})
                .collect(Collectors.toSet());
    }

    public Set<Integer> computeReachableAddressesInTheHeap(Set<Integer> roots, Map<Integer, Value> heap) {
        Set<Integer> reachableAddresses = new HashSet<>(roots);
        Stack<Integer> reachableAddressesStack = new Stack<>();
        reachableAddressesStack.addAll(roots);

        while (!reachableAddressesStack.isEmpty()) {
            int address = reachableAddressesStack.pop();
            Value v = heap.get(address);
            if (v instanceof ReferenceValue referenceValue) {
                int nextAddress = referenceValue.getAddress();
                if (!reachableAddresses.contains(nextAddress)) {
                    reachableAddresses.add(nextAddress);
                    reachableAddressesStack.push(nextAddress);
                }
            }
        }

        return reachableAddresses;
    }

    public Map<Integer, Value> safeGarbageCollector(Collection<Value> symbolTableValues, Map<Integer, Value> heap) {
        Set<Integer> roots = getAddressesFromSymbolTable(symbolTableValues);
        Set<Integer> reachable = computeReachableAddressesInTheHeap(roots, heap);
        return heap.entrySet().stream()
                .filter(elem -> reachable.contains(elem.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
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
                    currentProgramState.getSymbolTable().getMap().values(),
                    currentProgramState.getHeap().getContent()));

            this.repository.logProgramStateExecution(currentProgramState);
            displayCurrentProgramState();
        }
    }
}
