package repository;

import exceptions.MyException;
import exceptions.MyIndexOutOfBoundsException;
import model.state.ProgramState;

import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {
    private final List<ProgramState> programStates;

    public Repository() {
        this.programStates = new ArrayList<>();
    }

    public Repository(ProgramState programState) {
        this.programStates = new ArrayList<>();
        this.programStates.add(programState);
    }

    @Override
    public void addProgramState(ProgramState programState) {
        this.programStates.add(programState);
    }

    @Override
    public ProgramState getCurrentProgramState() {
        return programStates.getLast();
    }
}
