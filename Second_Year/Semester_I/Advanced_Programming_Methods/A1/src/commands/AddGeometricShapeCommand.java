package commands;

import controller.Controller;
import model.*;

public class AddGeometricShapeCommand extends Command {
    private final String[] input;

    public AddGeometricShapeCommand(Controller controller, String[] input) {
        super(controller);
        this.input = input;
    }

    @Override
    public void execute() {
        try {
            switch (input[0].toLowerCase()) {
                case "cube" -> {
                    float edge = Float.parseFloat(input[1]);
                    if (edge < 0)
                        throw new IllegalArgumentException("Please enter a valid value for the edge!");
                    else {
                        controller.addGeometricShape(new Cube(edge));
                        System.out.println("Cube added successfully!");
                    }
                }
                case "cylinder" -> {
                    float radius = Float.parseFloat(input[1]);
                    float height = Float.parseFloat(input[2]);
                    if (radius < 0 ||  height < 0)
                        throw new IllegalArgumentException("Please enter valid values for the radius and the height!");
                    else {
                        controller.addGeometricShape(new Cylinder(radius, height));
                        System.out.println("Cylinder added successfully!");
                    }
                }
                case "sphere" -> {
                    float radius = Float.parseFloat(input[1]);
                    if (radius < 0)
                        throw new IllegalArgumentException("Please enter a valid value for the radius!");
                    else {
                        controller.addGeometricShape(new Sphere(radius));
                        System.out.println("Sphere added successfully!");
                    }
                }
                default -> {
                    System.out.println("Unknown geometric shape: " + input[0]);
                }
            }
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
