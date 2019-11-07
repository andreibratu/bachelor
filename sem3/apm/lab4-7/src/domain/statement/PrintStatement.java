package domain.statement;

import adt.dictionary.IDictionary;
import adt.list.IList;
import domain.expression.Expression;
import domain.state.ProgramState;
import exception.type.IllegalTypeException;
import domain.value.Value;
import exception.variable.UndeclaredVariableException;

public class PrintStatement implements IStatement
{
    private Expression expression;

    public PrintStatement(Expression expression)
    {
        this.expression = expression;
    }

    public String toString() {
        return "print("+expression.toString()+")";
    }

    @Override
    public ProgramState execute(ProgramState state) throws IllegalTypeException, UndeclaredVariableException
    {
        IList<Value> list = state.getOut();
        IDictionary<String, Value> symTable = state.getSymbolTable();
        list.add(this.expression.evaluate(symTable));
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new PrintStatement(expression.deepCopy());
    }
}
