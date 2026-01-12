package view.gui;

import controller.IController;
import exceptions.MyEmptyStackException;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import model.state.ProgramState;
import model.state.executionStack.ExecutionStack;
import model.state.executionStack.IExecutionStack;
import model.state.fileTable.IFileTable;
import model.state.heap.IHeap;
import model.state.output.IOutput;
import model.state.output.Output;
import model.state.symbolTable.ISymbolTable;
import model.state.symbolTable.SymbolTable;
import model.statement.IStatement;
import model.value.Value;

import java.io.BufferedReader;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class MainWindowController {
    private IController controller;
    private ProgramState selectedProgram;

    @FXML
    private ListView<String> executionStackListView;

    @FXML
    private ListView<String> fileTableListView;

    @FXML
    private ListView<String> outputListView;

    @FXML
    private ListView<Integer> programStateIdentifiersListView;

    @FXML
    private TableView<Map.Entry<Integer, Value>> heapTableView;

    @FXML
    private TableColumn<Map.Entry<Integer, Value>, String> heapAddressColumn;

    @FXML
    private TableColumn<Map.Entry<Integer, Value>, String> heapValueColumn;

    @FXML
    private TableView<Map.Entry<String, Value>> symbolTableView;

    @FXML
    private TableColumn<Map.Entry<String, Value>, String> symbolTableVariableNameColumn;

    @FXML
    private TableColumn<Map.Entry<String, Value>, String> symbolTableValueColumn;

    @FXML
    private TextField numberOfProgramStatesTextField;

    @FXML
    private Button runOneStepButton;

    public void setController(IController controller) {
        this.controller = controller;
        populateAll();
    }

    @FXML
    private void initialize() {
        this.heapAddressColumn
                .setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getKey().toString()));
        this.heapValueColumn
                .setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getValue().toString()));

        this.symbolTableVariableNameColumn
                .setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getKey()));
        this.symbolTableValueColumn
                .setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getValue().toString()));

        this.programStateIdentifiersListView.getSelectionModel().selectedItemProperty().addListener(
                (observable, oldValue, newValue) -> {
                    if (newValue != null) {
                        this.selectedProgram = this.controller.getRepository().getProgramStates().stream()
                                .filter(p -> p.getId() == newValue)
                                .findFirst()
                                .orElse(null);
                        populateExecutionStack();
                        populateSymbolTable();
                    }
                });
    }

    private void populateAll() {
        populateHeapTable();
        populateOutput();
        populateFileTable();
        populateProgramStateIdentifiers();
        populateNumberOfProgramStates();

        if (this.selectedProgram == null && !this.controller.getRepository().getProgramStates().isEmpty()) {
            this.selectedProgram = this.controller.getRepository().getProgramStates().getFirst();
            this.programStateIdentifiersListView.getSelectionModel().select(0);
        }

        if (this.selectedProgram != null) {
            populateExecutionStack();
            populateSymbolTable();
        }
    }

    private void populateNumberOfProgramStates() {
        this.numberOfProgramStatesTextField.setText(String.valueOf(this.controller.getRepository().getProgramStates().size()));
    }

    private void populateHeapTable() {
        IHeap heap = this.controller.getRepository().getProgramStates().getFirst().getHeap();
        ObservableList<Map.Entry<Integer, Value>> heapEntries = FXCollections.observableArrayList(heap.getContent().entrySet());
        this.heapTableView.setItems(heapEntries);
    }

    private void populateOutput() {
        ObservableList<String> output = FXCollections.observableArrayList();
        if (!this.controller.getRepository().getProgramStates().isEmpty()) {
            IOutput outputManager = this.controller.getRepository().getProgramStates().getFirst().getOutput();
            output.addAll(outputManager.getAll());
        }
        this.outputListView.setItems(output);
    }

    private void populateFileTable() {
        ObservableList<String> files = FXCollections.observableArrayList();
        if (!this.controller.getRepository().getProgramStates().isEmpty()) {
            IFileTable fileTable = this.controller.getRepository().getProgramStates().getFirst().getFileTable();
            files.addAll(fileTable.getFiles().stream()
                    .filter(br -> br != null)
                    .map(Object::toString)
                    .collect(Collectors.toList()));
        }
        this.fileTableListView.setItems(files);
    }

    private void populateProgramStateIdentifiers() {
        ObservableList<Integer> identifiers = FXCollections.observableArrayList();
        identifiers.addAll(this.controller.getRepository().getProgramStates().stream()
                .map(ProgramState::getId)
                .collect(Collectors.toList()));
        this.programStateIdentifiersListView.setItems(identifiers);
    }

    private void populateExecutionStack() {
        ObservableList<String> executionStack = FXCollections.observableArrayList();
        if (this.selectedProgram != null) {
            List<String> stackElements = new ArrayList<>();
            IExecutionStack stack = this.selectedProgram.getExecutionStack();
            IExecutionStack temporaryStack = new ExecutionStack();

            try {
                while (!stack.isEmpty()) {
                    IStatement statement = stack.pop();
                    stackElements.add(statement.toString());
                    temporaryStack.push(statement);
                }

                while (!temporaryStack.isEmpty()) {
                    stack.push(temporaryStack.pop());
                }
            } catch (MyEmptyStackException e) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error");
                alert.setHeaderText(null);
                alert.setContentText("Error accessing the stack: " + e.getMessage());
                alert.showAndWait();
            }

            executionStack.addAll(stackElements);
        }
        this.executionStackListView.setItems(executionStack);
    }

    private void populateSymbolTable() {
        ObservableList<Map.Entry<String, Value>> symbolTableEntries = FXCollections.observableArrayList();
        if (this.selectedProgram != null) {
            ISymbolTable symbolTable = this.selectedProgram.getSymbolTable();
            symbolTableEntries.addAll(symbolTable.getMap().entrySet());
        }
        this.symbolTableView.setItems(symbolTableEntries);
    }

    @FXML
    void runOneStep(ActionEvent event) {
        if (this.controller == null) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText("No program selected!");
            alert.showAndWait();
            return;
        }

        List<ProgramState> programStates = this.controller.removeCompletedProgramStates(this.controller.getRepository().getProgramStates());
        if (programStates.isEmpty()) {
            this.runOneStepButton.setDisable(true);
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Information");
            alert.setHeaderText(null);
            alert.setContentText("Nothing left to execute!");
            alert.showAndWait();
            return;
        }

        try {
            this.controller.executeOneStepForAllPrograms(programStates);
            populateAll();
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }

}
