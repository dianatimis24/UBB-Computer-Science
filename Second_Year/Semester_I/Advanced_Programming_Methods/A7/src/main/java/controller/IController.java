package controller;

import exceptions.MyException;
import model.state.ProgramState;
import repository.IRepository;

import java.util.List;

public interface IController {
    List<ProgramState> removeCompletedProgramStates(List<ProgramState> programStates);
    void executeOneStepForAllPrograms(List<ProgramState> programStates) throws MyException;
    void executeAllPrograms() throws MyException;
    void setDisplayFlag(boolean status);
    void displayProgramState(ProgramState state);
    IRepository getRepository();
}
