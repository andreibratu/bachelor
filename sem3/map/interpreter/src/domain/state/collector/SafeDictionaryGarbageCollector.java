package domain.state.collector;

import domain.state.heap.DictionaryHeap;
import domain.state.symbol.DictSymbolTable;
import domain.value.IValue;
import domain.value.ReferenceValue;

import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class SafeDictionaryGarbageCollector implements IGarbageCollector
{
    private final DictSymbolTable symbolTable;
    private final DictionaryHeap heap;

    public SafeDictionaryGarbageCollector(DictSymbolTable symbolTable, DictionaryHeap heap)
    {
        this.symbolTable = symbolTable;
        this.heap = heap;
    }

    @Override
    public void free()
    {
        List<Integer> addresses = this.getAddresses();
        Map<Integer, IValue<?>> result = heap.getContent().entrySet()
                .stream()
                .filter(e->addresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
        this.heap.setContent((HashMap<Integer, IValue<?>>) result);
    }

    private List<Integer> getAddresses()
    {
        Collection<IValue<?>> symTableValues = this.symbolTable.getDictionary().values();
        Collection<IValue<?>> heapValues = this.heap.getContent().values();
        return Stream.concat(
                heapValues.stream()
                    .filter(v -> v instanceof ReferenceValue)
                    .map(v -> ((ReferenceValue) v).getValue()),
                symTableValues.stream()
                    .filter(v-> v instanceof ReferenceValue)
                    .map(v -> ((ReferenceValue) v).getValue()))
            .collect(Collectors.toList());
    }
}
