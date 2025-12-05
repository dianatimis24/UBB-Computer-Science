package repository;

import exceptions.MyException;
import model.state.ProgramState;

import java.util.List;

public interface IRepository {
    List<ProgramState> getProgramStates();
    void setProgramStates(List<ProgramState> programStates);
    void logProgramStateExecution(ProgramState programState) throws MyException;
}
