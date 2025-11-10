package view;

import commands.*;
import controller.Controller;
import model.*;

import java.util.Arrays;

public class View {
    private final Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    public void run() {
        addInitialGeometricalShapes();
        printMenu();

        while (true) {
            String input = IO.readln("\nInsert your command: ");
            String[] commandComponents = input.split(" ");
            switch (commandComponents[0].toLowerCase()) {
                case "add":
                    Command addCommand = new AddGeometricShapeCommand(this.controller, Arrays.copyOfRange(commandComponents, 1, commandComponents.length));
                    addCommand.execute();
                    break;
                case "remove":
                    Command removeCommand = new RemoveGeometricShapeCommand(this.controller, commandComponents[1]);
                    removeCommand.execute();
                    break;
                case "display":
                    if (commandComponents[1].equals("large")) {
                        Command displayCommand = new DisplayLargeGeometricShapesCommand(this.controller);
                        displayCommand.execute();
                    }
                    else if (commandComponents[1].equals("all")) {
                        Command displayCommand = new DisplayAllGeometricShapesCommand(this.controller);
                        displayCommand.execute();
                    }
                    else
                        System.out.println("Invalid type of display!");
                    break;
                case "exit":
                    System.out.println("Goodbye!");
                    return;
                default:
                    System.out.println("Invalid command!");
            }
        }
    }

    private static void printMenu() {
        System.out.println("This is how you should write different types of commands: ");
        System.out.println("Add [geometric_shape] [mandatory_dimension] [optional_dimension, ignored if not necessary]");
        System.out.println("Remove [index]");
        System.out.println("Display all");
        System.out.println("Display large");
        System.out.println("Exit");
    }

    private void addInitialGeometricalShapes() {
        GeometricShape shape1 = new Cube(6);
        GeometricShape shape2 = new Sphere(2);
        GeometricShape shape3 = new Cylinder(3, 4);
        GeometricShape shape4 = new Cylinder(4, 1);
        GeometricShape shape5 = new Cube(2.5F);
        GeometricShape shape6 = new Sphere(1);

        try {
            this.controller.addGeometricShape(shape1);
            this.controller.addGeometricShape(shape2);
            this.controller.addGeometricShape(shape3);
            this.controller.addGeometricShape(shape4);
            this.controller.addGeometricShape(shape5);
            this.controller.addGeometricShape(shape6);
        }
        catch (Exception e) {
            System.out.println("Error: "  + e.getMessage());
        }
    }
}
