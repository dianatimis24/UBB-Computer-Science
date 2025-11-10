package repository;

import exceptions.MyException;
import model.state.ProgramState;

public interface IRepository {
    void addProgramState(ProgramState programState);
    ProgramState getCurrentProgramState();
}
