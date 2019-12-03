package domain.state.symbol;

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

    public DictionarySymbolTable(DictionarySymbolTable table)
    {
        this.dictionary = new HashMap<>();
        for(Map.Entry entry : table.dictionary.entrySet())
        {
            String key = (String) entry.getKey();
            IValue value = null;
            try {
                value = (IValue) ((IValue) entry.getValue()).clone();
            } catch (CloneNotSupportedException e) {
                e.printStackTrace();
            }
            dictionary.put(key, value);
        }
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
    public String toString()
    {
        StringBuilder builder = new StringBuilder();
        builder.append("SYMBOLS\n");
        for(Map.Entry entry : dictionary.entrySet())
        {
            builder.append(entry.getKey().toString()).append(" -> ").append(entry.getValue().toString()).append("\n");
        }
        return builder.toString();
    }

    public HashMap getContent()
    {
        HashMap<String, IValue> clone = new HashMap<>();
        for(Map.Entry entry : dictionary.entrySet())
        {
            String key = (String) entry.getKey();
            IValue value = null;
            try
            {
                value = (IValue) ((IValue) entry.getValue()).clone();
            } catch (CloneNotSupportedException e)
            {
                e.printStackTrace();
            }
            clone.put(key, value);
        }
        return clone;
    }
}
