package domain.statement.control;

import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.state.heap.DictionaryHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.DictSymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.statement.IStatement;
import domain.type.BoolType;
import domain.type.IType;
import domain.type.IllegalTypeException;
import domain.value.IValue;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class IfStatement implements IStatement
{
    private IExpression expression;
    private IStatement thenStatement;
    private IStatement elseStatement;

    IfStatement(IExpression expression, IStatement thenStatement, IStatement elseStatement)
    {
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    public String toString()
    {
        return "IF (" + expression.toString() + ") " +
                "THEN ( " + thenStatement.toString() + " ) " +
                "ELSE ( " + elseStatement.toString() + ")";
    }

    @Override
    public Map<String, IType> typeCheck(Map<String, IType> typeEnv) throws IllegalTypeException
    {
        IType typeExpression = expression.typeCheck(typeEnv);
        IType boolType = new BoolType();
        if(!typeExpression.equals(boolType)) throw new IllegalTypeException(this.toString(), boolType, typeExpression);
        Map<String, IType> copyThen = new HashMap<>(typeEnv);
        Map<String, IType> copyElse = new HashMap<>(typeEnv);
        thenStatement.typeCheck(copyThen);
        elseStatement.typeCheck(copyElse);
        return typeEnv;
    }

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException
    {
        Stack<IStatement> exeStack = state.getExecutionStack();
        DictSymbolTable symTable = state.getSymbolTable();
        DictionaryHeap heap = state.getHeap();
        IValue<?> result = this.expression.evaluate(symTable, heap);
        if(!result.getValue().equals(0))
            exeStack.push(thenStatement);
        else
            exeStack.push(elseStatement);
        return null;
    }

    @Override
    public IStatement clone() throws CloneNotSupportedException {
        IfStatement clone = (IfStatement) super.clone();
        clone.expression = (IExpression) this.expression.clone();
        clone.thenStatement = (IStatement) this.thenStatement.clone();
        clone.elseStatement = (IStatement) this.thenStatement.clone();
        return clone;
    }
}
