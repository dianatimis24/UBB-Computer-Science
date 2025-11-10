package commands;

import controller.Controller;

public abstract class Command {
    protected final Controller controller;

    public Command(Controller controller) {
        this.controller = controller;
    }

    abstract public void execute();
}
