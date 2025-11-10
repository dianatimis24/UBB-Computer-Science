package view;

import controller.Controller;
import controller.IController;
import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.ADTs.dictionary.MyDictionary;
import model.ADTs.list.IList;
import model.ADTs.list.MyList;
import model.ADTs.stack.IStack;
import model.ADTs.stack.MyStack;
import model.expression.ArithmeticExpression;
import model.expression.ValueExpression;
import model.expression.VariableExpression;
import model.state.ProgramState;
import model.statement.*;
import model.type.*;
import model.value.*;
import repository.IRepository;
import repository.Repository;

import java.util.InputMismatchException;
import java.util.Scanner;

public class View {
    private final IController controller;

    public View(IController controller) {
        this.controller = controller;
    }

    public void start() {
        Scanner scanner = new Scanner(System.in);
        IStatement selectedProgram = null;

        while (selectedProgram == null) {
            displayMenu();
            try {
                int choice = scanner.nextInt();
                if (choice == 0) {
                    System.out.println("Goodbye!");
                    break;
                }
                switch (choice) {
                    case 1:
                        selectedProgram = createExample1();
                        executeSelectedProgram(selectedProgram);
                        selectedProgram = null;
                        break;
                    case 2:
                        selectedProgram = createExample2();
                        executeSelectedProgram(selectedProgram);
                        selectedProgram = null;
                        break;
                    case 3:
                        selectedProgram = createExample3();
                        executeSelectedProgram(selectedProgram);
                        selectedProgram = null;
                        break;
                    default:
                        System.out.println("Invalid choice!");
                }
            } catch (InputMismatchException e) {
                System.out.println("Please enter a valid number!");
                scanner.nextLine();
            }
        }

        scanner.close();
    }

    private void executeSelectedProgram(IStatement selectedProgram) {
        IStack<IStatement> stack = new MyStack<>();
        IDictionary<String, Value> symbolTable = new MyDictionary<>();
        IList<Value> output = new MyList<>();

        ProgramState programState = new ProgramState(stack, symbolTable, output, selectedProgram);
        this.controller.addProgramState(programState);

        try {
            this.controller.executeAllSteps();
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }
    }

    private void displayMenu() {
        System.out.println("1. int v; v=2; Print(v)");
        System.out.println("2. int a; int b; a=2+3*5; b=a+1; Print(b)");
        System.out.println("3. bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)");
        System.out.println("0. exit");
        System.out.println("\nSelect the program to execute: (1-3)");
    }

    private static IStatement createExample1() {
        // int v; v=2; Print(v)
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(
                        new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));
    }

    private static IStatement createExample2() {
        // int a; int b; a=2+3*5; b=a+1; Print(b)
        return new CompoundStatement(
                new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(
                        new VariableDeclarationStatement("b", new IntType()),
                        new CompoundStatement(
                                new AssignmentStatement("a", new ArithmeticExpression('+', new ValueExpression(new IntValue(2)),
                                        new ArithmeticExpression('*', new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                                new CompoundStatement(
                                        new AssignmentStatement("b", new ArithmeticExpression('+', new VariableExpression("a"), new ValueExpression(new IntValue(1)))),
                                        new PrintStatement(new VariableExpression("b"))))));
    }

    private static IStatement createExample3() {
        // bool a; int v; a = true; (If a Then v=2 Else v=3); Print(v)
        return new CompoundStatement(
                new VariableDeclarationStatement("a", new BoolType()),
                new CompoundStatement(
                        new VariableDeclarationStatement("v", new IntType()),
                        new CompoundStatement(
                                new AssignmentStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompoundStatement(
                                        new IfStatement(new VariableExpression("a"),
                                                new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                                                new AssignmentStatement("v", new ValueExpression(new IntValue(3)))),
                                        new PrintStatement(new VariableExpression("v"))))));
    }
}
