package model.statement;


import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.state.ProgramState;
import model.type.Type;

public interface IStatement {
    ProgramState execute(ProgramState state) throws MyException;
    IDictionary<String, Type> typecheck(IDictionary<String, Type> typeEnvironment) throws MyException;
    IStatement deepCopy();
}
