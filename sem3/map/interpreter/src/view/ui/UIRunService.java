package view.ui;

import controller.Controller;
import controller.IController;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.type.IllegalTypeException;
import domain.value.IValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import repository.IRepository;
import repository.Repository;

import java.util.*;
import java.util.stream.Collectors;

public class UIRunService
{
    private static UIRunService instance;
    private int programId;
    private IRepository repository;
    private IController controller;
    private final ObservableList<IValue<?>> out;
    private final ObservableList<Integer> programIds;
    private final ObservableList<SymTableRowModel> symbolTable;
    private final ObservableList<HeapRowModel> heap;
    private final ObservableList<IStatement> stack;
    private final ObservableList<String> fileTable;

    private UIRunService()
    {
        out = FXCollections.observableArrayList();
        programIds = FXCollections.observableArrayList();
        symbolTable = FXCollections.observableArrayList();
        heap = FXCollections.observableArrayList();
        stack = FXCollections.observableArrayList();
        fileTable = FXCollections.observableArrayList();
    }

    private void updateObservables()
    {
        List<ProgramState> programStates = this.repository.getProgramList();


        if(programStates.size() == 0)
        {
            out.clear();
            stack.clear();
            fileTable.clear();
            heap.clear();
            symbolTable.clear();
            programIds.clear();
            return;
        }

        ProgramState currentProgram = this.repository.getProgramList().get(programId);
        this.out.setAll(currentProgram.getOut());
        this.programIds.setAll(
                programStates.stream()
                .map(ProgramState::getId)
                .collect(Collectors.toList())
        );
        this.stack.setAll(currentProgram.getExecutionStack());
        this.fileTable.setAll(
            new ArrayList<>(currentProgram.getFileTable().getDictionary().keySet())
        );
        this.heap.setAll(
            currentProgram.getHeap().getDictionary().entrySet().stream()
                .map(HeapRowModel::new)
                .collect(Collectors.toList())
        );
        this.symbolTable.setAll(
            currentProgram.getSymbolTable().getDictionary().entrySet().stream()
                .map(SymTableRowModel::new)
                .collect(Collectors.toList())
        );
    }

    public boolean executionIsOver() { return this.repository.getProgramList().size() == 0; }

    public static UIRunService buildObject()
    {
        if(instance == null)
        {
            instance = new UIRunService();
        }
        return instance;
    }

    public void setRunProgram(IStatement runStatement)
    {
        try
        {
            ProgramState initProgramState = new ProgramState(runStatement);
            repository = new Repository(initProgramState, "log.txt");
            controller = new Controller(repository, false);
            programId = 0;
            updateObservables();
        } catch (IllegalTypeException e)
        {
            e.printStackTrace();
        }
    }

    public void oneStep()
    {
        List<ProgramState> programStates = repository.getProgramList();
        try
        {
            controller.oneStepAllPrograms();
            if(programStates.size() != 0 && programStates.get(programId) == null) programId = 0;
            updateObservables();
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
    }

    public ObservableList<IValue<?>> getOut() {
        return out;
    }

    public ObservableList<Integer> getProgramIds() {
        return programIds;
    }

    public ObservableList<SymTableRowModel> getSymbolTable() {
        return symbolTable;
    }

    public ObservableList<HeapRowModel> getHeap() {
        return heap;
    }

    public ObservableList<IStatement> getStack() {
        return stack;
    }

    public ObservableList<String> getFileTable() {
        return fileTable;
    }

    public void setProgramId(int programId)
    {
        this.programId = programId;
        updateObservables();
    }
}
