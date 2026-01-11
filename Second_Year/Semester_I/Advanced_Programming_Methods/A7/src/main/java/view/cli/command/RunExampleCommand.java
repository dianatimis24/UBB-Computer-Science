package view.cli.command;

import controller.IController;
import exceptions.MyException;
import model.statement.IStatement;

public class RunExampleCommand extends Command {
    private final IController controller;
    private boolean hasBeenExecuted;

    public RunExampleCommand(String key, IStatement stmt, IController controller) {
        super(key, stmt.toString());
        this.controller = controller;
        this.hasBeenExecuted = false;
    }

    @Override
    public void execute() {
        if (hasBeenExecuted) {
            System.out.println("This program has already been executed!");
            return;
        }
        try {
            controller.executeAllPrograms();
            hasBeenExecuted = true;
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }
    }

    public boolean hasBeenExecuted() {
        return hasBeenExecuted;
    }
}
