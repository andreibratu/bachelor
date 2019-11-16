package domain.state.symbol;

import domain.state.heap.DictionaryHeap;
import domain.value.IValue;

import java.util.HashMap;
import java.util.Map;

public class DictionarySymbolTable implements ISymbolTable
{
    private HashMap<String, IValue> dictionary;

    public DictionarySymbolTable()
    {
        this.dictionary = new HashMap<>();
    }

    @Override
    public void createVariable(String variable, IValue value) throws VariableAlreadyDefinedException
    {
        if(dictionary.containsKey(variable)) throw new VariableAlreadyDefinedException(variable);
        dictionary.put(variable, value);
    }

    @Override
    public void updateVariable(String variable, IValue value) throws UndeclaredVariableException
    {
        if (!dictionary.containsKey(variable)) throw new UndeclaredVariableException(variable);
        dictionary.put(variable, value);
    }

    @Override
    public IValue queryVariable(String variable) throws UndeclaredVariableException
    {
        if(!dictionary.containsKey(variable)) throw new UndeclaredVariableException(variable);
        return dictionary.get(variable);
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for(Map.Entry entry : dictionary.entrySet())
        {
            builder.append(entry.getKey().toString()).append(" -> ").append(entry.getValue().toString()).append("\n");
        }
        return builder.toString();
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        DictionarySymbolTable clone = (DictionarySymbolTable) super.clone();
        for(Map.Entry entry : dictionary.entrySet())
        {
            String key = (String) entry.getKey();
            IValue value = (IValue) ((IValue) entry.getValue()).clone();
            clone.dictionary.put(key, value);
        }
        return clone;
    }
}
