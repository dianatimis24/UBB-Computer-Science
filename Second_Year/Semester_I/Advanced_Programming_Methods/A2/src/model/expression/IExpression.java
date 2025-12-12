package model.expression;

import model.ADTs.dictionary.IDictionary;
import exceptions.ExpressionException;
import exceptions.MyException;
import model.value.Value;

public interface IExpression {
    Value evaluate(IDictionary<String, Value> symbolTable) throws Exception;
    IExpression deepCopy();
}
