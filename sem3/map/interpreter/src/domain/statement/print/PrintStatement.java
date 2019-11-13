package domain.statement.print;

import adt.dictionary.IDictionary;
import adt.list.IList;
import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.statement.IStatement;
import exception.type.IllegalTypeException;
import domain.value.IValue;
import exception.variable.UndeclaredVariableException;

public class PrintStatement implements IStatement
{
    private IExpression expression;

    public PrintStatement(IExpression expression)
    {
        this.expression = expression;
    }

    public String toString() {
        return "print("+ expression.toString()+")";
    }

    @Override
    public ProgramState execute(ProgramState state) throws IllegalTypeException, UndeclaredVariableException
    {
        IList<IValue> list = state.getOut();
        IDictionary<String, IValue> symTable = state.getSymbolTable();
        list.add(this.expression.evaluate(symTable));
        return state;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        PrintStatement clone = (PrintStatement) super.clone();
        clone.expression = (IExpression) this.expression.clone();
        return clone;
    }
}
