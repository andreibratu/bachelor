package domain.statement.heap;

import domain.state.heap.DictionaryHeap;
import domain.state.heap.IHeap;
import domain.state.symbol.DictionarySymbolTable;
import domain.state.symbol.ISymbolTable;
import org.junit.Before;

public class HeapAllocationStatementTest
{
    private ISymbolTable mockSymbolTable;
    private IHeap mockHeap;

    @Before
    public void setUp()
    {
        this.mockSymbolTable = new DictionarySymbolTable();
        this.mockHeap = new DictionaryHeap();
    }
}
