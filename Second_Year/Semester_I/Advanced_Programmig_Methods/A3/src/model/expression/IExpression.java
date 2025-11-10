package model.expression;

import model.ADTs.dictionary.IDictionary;
import exceptions.ExpressionException;
import exceptions.MyException;
import model.state.symbolTable.ISymbolTable;
import model.value.Value;

public interface IExpression {
    Value evaluate(ISymbolTable symbolTable) throws MyException;
    IExpression deepCopy();
}
