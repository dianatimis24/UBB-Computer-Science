package commands;

import controller.Controller;

public class RemoveGeometricShapeCommand extends Command {
    private final String input;

    public RemoveGeometricShapeCommand(Controller controller, String input) {
        super(controller);
        this.input = input;
    }

    @Override
    public void execute() {
        try {
            int index = Integer.parseInt(input);
            controller.removeGeometricShape(index);
            System.out.println("Geometric shape removed successfully!");
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
