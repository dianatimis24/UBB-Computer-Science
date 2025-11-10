package controller;

import exceptions.MyException;
import model.state.ProgramState;

public interface IController {
    void addProgramState(ProgramState programState);
    void displayCurrentProgramState();
    ProgramState executeOneStep(ProgramState state) throws MyException;
    void executeAllSteps() throws MyException;
}
