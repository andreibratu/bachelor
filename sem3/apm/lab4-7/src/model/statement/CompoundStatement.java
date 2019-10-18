package model.statement;

import model.program.ProgramState;

import java.util.Stack;

class CompoundStatement implements Statement
{
    private Statement first;
    private Statement second;

    public CompoundStatement(Statement first, Statement second)
    {
        this.first = first;
        this.second = second;
    }

    public String toString() {
        return "(" + first.toString() + ";" + second.toString() + ")";
    }

    @Override
    public ProgramState execute(ProgramState state) {
        Stack<Statement> stack = state.getExecutionStack();
        stack.push(second);
        stack.push(first);
        return state;
    }
}
