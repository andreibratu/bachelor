package domain.statement;

import adt.IDictionary;
import adt.IList;
import domain.expression.Expression;
import domain.state.ProgramState;
import domain.type.IllegalTypeException;
import domain.value.Value;

public class PrintStatement implements IStatement
{
    private Expression expression;

    PrintStatement(Expression expression)
    {
        this.expression = expression;
    }

    public String toString() {
        return "print("+expression.toString()+")";
    }

    @Override
    public ProgramState execute(ProgramState state) throws IllegalTypeException {
        IList<Value> list = state.getOut();
        IDictionary<String, Value> symTable = state.getSymbolTable();
        list.add(this.expression.evaluate(symTable));
        return state;
    }
}
