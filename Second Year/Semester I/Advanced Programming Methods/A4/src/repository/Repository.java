package repository;

import exceptions.MyException;
import model.state.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Repository implements IRepository {
    private final List<ProgramState> programStates;
    private String logFilePath;

    public Repository(ProgramState programState) {
        this.programStates = new ArrayList<>();
        this.programStates.add(programState);
    }

    public Repository(String logFilePath) {
        this.programStates = new ArrayList<>();
        this.logFilePath = logFilePath;
    }

    public Repository(ProgramState programState, String logFilePath) {
        this.programStates = new ArrayList<>();
        this.programStates.add(programState);
        this.logFilePath = logFilePath;
    }

    public void setLogFilePath() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the log file path: ");
        this.logFilePath = scanner.nextLine();
        scanner.close();
    }

    @Override
    public void addProgramState(ProgramState programState) {
        this.programStates.add(programState);
    }

    @Override
    public ProgramState getCurrentProgramState() {
        return programStates.getLast();
    }

    @Override
    public void logProgramStateExecution(ProgramState programState) throws MyException {
        if (this.logFilePath == null) {
            setLogFilePath();
        }
        PrintWriter logFile;
        try {
            logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)));
        } catch (IOException e) {
            throw new MyException("Error opening the log file.");
        }
        logFile.println(programState.toString());
        logFile.close();
    }


}
