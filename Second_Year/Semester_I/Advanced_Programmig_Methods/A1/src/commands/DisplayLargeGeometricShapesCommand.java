package commands;

import controller.Controller;

public class DisplayLargeGeometricShapesCommand extends Command {
    private final int MINIMUM_VOLUME = 25;

    public DisplayLargeGeometricShapesCommand(Controller controller) {
        super(controller);
    }

    @Override
    public void execute() {
        for (var shape : controller.getLargeGeometricShapes(MINIMUM_VOLUME))
            System.out.println(shape);
    }
}
