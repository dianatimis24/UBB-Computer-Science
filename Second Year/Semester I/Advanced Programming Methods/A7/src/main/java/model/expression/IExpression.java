package model.expression;

import exceptions.MyException;
import model.ADTs.dictionary.IDictionary;
import model.state.heap.IHeap;
import model.state.symbolTable.ISymbolTable;
import model.type.Type;
import model.value.Value;

public interface IExpression {
    Value evaluate(ISymbolTable symbolTable, IHeap heap) throws MyException;
    Type typecheck(IDictionary<String, Type> typeEnvironment) throws MyException;
    IExpression deepCopy();
}
