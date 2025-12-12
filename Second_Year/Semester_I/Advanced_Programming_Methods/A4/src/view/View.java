package view;

import controller.Controller;
import controller.IController;
import model.expression.*;
import model.state.ProgramState;
import model.state.executionStack.ExecutionStack;
import model.state.executionStack.IExecutionStack;
import model.state.fileTable.FileTable;
import model.state.fileTable.IFileTable;
import model.state.heap.Heap;
import model.state.heap.IHeap;
import model.state.output.IOutput;
import model.state.output.Output;
import model.state.symbolTable.ISymbolTable;
import model.state.symbolTable.SymbolTable;
import model.statement.*;
import model.type.*;
import model.value.*;
import repository.IRepository;
import repository.Repository;
import view.command.ExitCommand;
import view.command.RunExampleCommand;

public class View {
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

    private static IStatement createExample4() {
        /*
        string varf; varf = "test.in"; openRFile(varf); int varc; readFile(varf,
        varc); Print(varc); readFile(varf, varc); Print(varc); closeRFile(varf);
         */
        return new CompoundStatement(
                new VariableDeclarationStatement("varf", new StringType()),
                new CompoundStatement(new AssignmentStatement("varf", new ValueExpression(new StringValue("test.in"))),
                        new CompoundStatement(new OpenRFileStatement(new VariableExpression("varf")),
                                new CompoundStatement(new VariableDeclarationStatement("varc", new IntType()),
                                        new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                                        new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                                                        new CloseFileStatement(new VariableExpression("varf"))))))))));
    }

    private static IStatement createExample5() {
        // Ref int v;new(v,20);Ref Ref int a; new(a,v);print(v);print(a)
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(
                        new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(
                                        new NewStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(
                                                new PrintStatement(new VariableExpression("v")),
                                                new PrintStatement(new VariableExpression("a")))))));
    }

    private static IStatement createExample6() {
        // Ref int v;new(v,20);Ref Ref int a; new(a,v);print(rH(v));print(rH(rH(a))+5)
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(
                        new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(
                                        new NewStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(
                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                                new PrintStatement(new ArithmeticExpression('+',
                                                        new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a"))),
                                                        new ValueExpression(new IntValue(5)))))))));
    }

    private static IStatement createExample7() {
        // Ref int v;new(v,20);print(rH(v)); wH(v,30);print(rH(v)+5);
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(
                        new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                new CompoundStatement(
                                        new WriteHeapStatement("v", new ValueExpression(new IntValue(30))),
                                        new PrintStatement(new ArithmeticExpression('+',
                                                new ReadHeapExpression(new VariableExpression("v")),
                                                new ValueExpression(new IntValue(5))))))));
    }

    private static IStatement createExample8() {
        // Ref int v;new(v,20);Ref Ref int a; new(a,v); new(v,30);print(rH(rH(a)))
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(
                        new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a",
                                        new ReferenceType(new ReferenceType(new IntType()))),
                                new CompoundStatement(
                                        new NewStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(
                                                new NewStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(new ReadHeapExpression(new ReadHeapExpression( new VariableExpression("a")))))))));
    }

    private static IStatement createExample9() {
        // int v; v=4; (while (v>0) print(v);v=v-1);print(v)
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(
                        new AssignmentStatement("v", new ValueExpression(new IntValue(4))),
                        new CompoundStatement(
                                new WhileStatement(
                                        new RelationalExpression(">",
                                                new VariableExpression("v"),
                                                new ValueExpression(new IntValue(0))),
                                        new CompoundStatement(
                                                new PrintStatement(new VariableExpression("v")),
                                                new AssignmentStatement("v",
                                                        new ArithmeticExpression('-',
                                                                new VariableExpression("v"),
                                                                new ValueExpression(new IntValue(1)))))),
                                new PrintStatement(new VariableExpression("v")))));
    }

    private static IStatement createExample10() {
        // Ref int v;new(v,20);Ref int a; new(a, 40); new(v,30);print(rH(rH(a)))
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(
                        new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a",
                                        new ReferenceType(new IntType())),
                                new CompoundStatement(
                                        new NewStatement("a", new ValueExpression(new IntValue(40))),
                                        new CompoundStatement(
                                                new NewStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(new ReadHeapExpression(new ReadHeapExpression( new VariableExpression("a")))))))));
    }

    private static ProgramState createProgramState(IStatement originalProgram) {
        IExecutionStack executionStack = new ExecutionStack();
        ISymbolTable symbolTable = new SymbolTable();
        IOutput output = new Output();
        IFileTable fileTable = new FileTable();
        IHeap heap = new Heap();

        return new ProgramState(executionStack, symbolTable, output, fileTable, heap, originalProgram);
    }

    private static IController createController(IStatement statement, String logFilePath) {
        ProgramState programState = createProgramState(statement);
        IRepository repository = new Repository(programState, logFilePath);

        return new Controller(repository, false);
    }

    public static void main() {
        TextMenu menu = new TextMenu();

        menu.addCommand(new RunExampleCommand("1", createExample1(), createController(createExample1(), "log1.txt")));
        menu.addCommand(new RunExampleCommand("2", createExample2(), createController(createExample2(), "log2.txt")));
        menu.addCommand(new RunExampleCommand("3", createExample3(), createController(createExample3(), "log3.txt")));
        menu.addCommand(new RunExampleCommand("4", createExample4(), createController(createExample4(), "log4.txt")));
        menu.addCommand(new RunExampleCommand("5", createExample5(), createController(createExample5(), "log5.txt")));
        menu.addCommand(new RunExampleCommand("6", createExample6(), createController(createExample6(), "log6.txt")));
        menu.addCommand(new RunExampleCommand("7", createExample7(), createController(createExample7(), "log7.txt")));
        menu.addCommand(new RunExampleCommand("8", createExample8(), createController(createExample8(), "log8.txt")));
        menu.addCommand(new RunExampleCommand("9", createExample9(), createController(createExample9(), "log9.txt")));
        menu.addCommand(new RunExampleCommand("10", createExample10(), createController(createExample10(), "log10.txt")));
        menu.addCommand(new ExitCommand("0", "Exit"));

        menu.show();
    }
}
