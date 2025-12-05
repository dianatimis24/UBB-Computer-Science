package model.statement;

import model.ADTs.dictionary.IDictionary;
import exceptions.MyException;
import model.state.ProgramState;
import model.state.symbolTable.ISymbolTable;
import model.type.Type;
import model.value.Value;

public class VariableDeclarationStatement implements IStatement {
    private final String variableName;
    private final Type variableType;

    public VariableDeclarationStatement(String variableName, Type variableType) {
        this.variableName = variableName;
        this.variableType = variableType;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        ISymbolTable symbolTable = state.getSymbolTable();
        if (symbolTable.isDefined(this.variableName)) {
            throw new MyException("Variable " + this.variableName + " is already declared.");
        }
        symbolTable.insert(this.variableName, this.variableType);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new VariableDeclarationStatement(this.variableName, this.variableType.deepCopy());
    }

    @Override
    public String toString() {
        return this.variableType.toString() + " " + this.variableName;
    }
}
