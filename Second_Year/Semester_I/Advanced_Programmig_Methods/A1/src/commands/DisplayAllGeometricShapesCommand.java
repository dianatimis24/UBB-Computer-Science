package commands;

import controller.Controller;

public class DisplayAllGeometricShapesCommand extends Command {
    public DisplayAllGeometricShapesCommand(Controller controller) {
        super(controller);
    }
    @Override
    public void execute() {
        for (var shape : controller.getAll())
            System.out.println(shape);
    }
}
