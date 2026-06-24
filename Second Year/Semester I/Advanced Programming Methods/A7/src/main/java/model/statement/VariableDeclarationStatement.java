package model.statement;

import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.state.ProgramState;
import model.state.symbolTable.ISymbolTable;
import model.type.Type;

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
    public IDictionary<String, Type> typecheck(IDictionary<String, Type> typeEnvironment) throws MyException {
        typeEnvironment.insert(this.variableName, this.variableType);
        return typeEnvironment;
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
