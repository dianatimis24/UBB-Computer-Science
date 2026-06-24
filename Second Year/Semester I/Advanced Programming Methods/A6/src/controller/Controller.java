package controller;

import exceptions.MyException;
import model.state.ProgramState;
import model.state.heap.IHeap;
import model.value.Value;
import repository.IRepository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller implements IController {
    private final IRepository repository;
    private boolean displayFlag = false;
    private ExecutorService executor;
    private final GarbageCollector garbageCollector = new GarbageCollector();

    public Controller(IRepository repository, boolean displayFlag) {
        this.repository = repository;
        this.displayFlag = displayFlag;
    }

    public boolean getDisplayFlag() {
        return this.displayFlag;
    }

    @Override
    public List<ProgramState> removeCompletedProgramStates(List<ProgramState> programStates) {
        return programStates.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    @Override
    public void executeOneStepForAllPrograms(List<ProgramState> programStates) throws MyException {
        programStates.forEach(this.repository::logProgramStateExecution);

        // get list of callables
        List<Callable<ProgramState>> callablesList = programStates.stream()
                .map(program -> (Callable<ProgramState>)(program::executeStep))
                .collect(Collectors.toList());

        // execute callables -> get list of threads
        List<ProgramState> threadsProgramStates = null;
        try {
            threadsProgramStates = this.executor.invokeAll(callablesList).stream()
                    .map(future -> {
                        try {
                            return future.get();
                        } catch (InterruptedException | ExecutionException e) {
                            throw new MyException("Concurrent thread execution error: " + e.getMessage());
                        }
                    })
                    .filter(program -> program != null) // result of fork statement
                    .collect(Collectors.toList());
        } catch (InterruptedException e) {
            throw new MyException("Concurrent thread execution error.");
        }

        programStates.addAll(threadsProgramStates);

        programStates.forEach(this.repository::logProgramStateExecution);
        programStates.forEach(this::displayProgramState);

        this.repository.setProgramStates(programStates);
    }

    @Override
    public void executeAllPrograms() throws MyException {
        this.executor = Executors.newFixedThreadPool(2);
        List<ProgramState> programStates = this.removeCompletedProgramStates(this.repository.getProgramStates());
        while (!programStates.isEmpty()) {
            this.garbageCollector(programStates);
            this.executeOneStepForAllPrograms(programStates);
            programStates = this.removeCompletedProgramStates(this.repository.getProgramStates());
        }
        this.executor.shutdownNow();
        this.repository.setProgramStates(programStates);
    }

    public void garbageCollector(List<ProgramState> programStates) {
        IHeap heap = programStates.getFirst().getHeap();
        Map<Integer, Value> garbageFreeHeapContent = this.garbageCollector.garbageCollector(
                this.garbageCollector.getReachableAddresses(programStates.stream().map(ProgramState::getSymbolTable).collect(Collectors.toList()), heap),
                heap.getContent()
        );

        heap.setContent((HashMap<Integer, Value>) garbageFreeHeapContent);
    }

    @Override
    public void setDisplayFlag(boolean displayFlag) {
        this.displayFlag = displayFlag;
    }

    @Override
    public void displayProgramState(ProgramState state) {
        if (this.displayFlag) System.out.println(state.toString());
    }
}
