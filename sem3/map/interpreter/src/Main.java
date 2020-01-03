import domain.expression.ArithmeticExpression;
import domain.expression.ReadHeapExpression;
import domain.expression.ValueExpression;
import domain.expression.VariableExpression;
import domain.operator.ArithmeticOperator;
import domain.statement.IStatement;
import domain.statement.control.CompoundStatement;
import domain.statement.file.CloseRFileStatement;
import domain.statement.file.OpenRFileStatement;
import domain.statement.file.ReadFileStatement;
import domain.statement.fork.ForkStatement;
import domain.statement.heap.HeapAllocationStatement;
import domain.statement.heap.WriteHeapStatement;
import domain.statement.print.PrintStatement;
import domain.statement.variable.VariableAssignmentStatement;
import domain.statement.variable.VariableDeclarationStatement;
import domain.type.IntegerType;
import domain.type.ReferenceType;
import domain.type.StringType;
import domain.value.IValue;
import domain.value.IntegerValue;
import domain.value.ReferenceValue;
import domain.value.StringValue;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TableView;
import javafx.scene.layout.*;
import javafx.stage.Stage;
import view.ui.HeapRowModel;
import view.ui.SymTableRowModel;
import view.ui.UIFactoryService;
import view.ui.UIRunService;

import java.util.Arrays;
import java.util.List;
import java.util.Map;

public class Main extends Application
{
    private static List<IStatement> statements;
    private static UIFactoryService factoryService;
    private static UIRunService runService;

    private void setUpStatementSelectionWindow()
    {
        Stage stage = new Stage();

        ListView<IStatement> statementsView = factoryService.buildListView(FXCollections.observableList(statements));
        Button selectButton = new Button("Select");
        selectButton.setOnAction(actionEvent -> {
            IStatement selected = statementsView.getSelectionModel().getSelectedItem();
            if(selected != null)
            {
                runService.setRunProgram(selected);
                setUpRunWindow();
                stage.close();
            }
        });

        Pane statementSelection = factoryService.buildLayout(
            VBox.class, null, Pos.CENTER,
            statementsView,
            factoryService.buildSpacing(50.0, Priority.ALWAYS, null, null),
            selectButton, factoryService.buildSpacing(null, null, 50.0, Priority.ALWAYS)
        );
        statementSelection.setPadding(new Insets(5, 5, 5, 5));

        Scene scene = new Scene(statementSelection);

        stage.setTitle("Select Statement");
        stage.setWidth(500);
        stage.setHeight(400);
        stage.setScene(scene);
        stage.show();
    }

    private void setUpRunWindow()
    {
        Stage stage = new Stage();

        BorderPane layout = (BorderPane) factoryService.buildLayout(BorderPane.class, 5.0, null);
        Label label = new Label("Out");
        ListView<IValue<?>> out = factoryService.buildListView(runService.getOut());
        Pane labels = factoryService.buildLayout(
            HBox.class, null, Pos.CENTER,
            new Label("Program States"),
            factoryService.buildSpacing(null, null, 50.0, Priority.ALWAYS),
            new Label(String.valueOf(runService.getProgramIds().size()))
        );
        ListView<Integer> programStateIds = factoryService.buildListView(runService.getProgramIds());
        Node spaceBeforeIdButton = factoryService.buildSpacing(150.0, Priority.ALWAYS, null, null);
        layout.setLeft(factoryService.buildLayout(
                VBox.class, null, Pos.CENTER,
                label, out, labels, programStateIds, spaceBeforeIdButton)
        );

        Label exeStackLabel = new Label("Execution Stack");
        ListView<IStatement> exeStack = factoryService.buildListView(runService.getStack());
        Label symTableLabel = new Label("Symbol Table");
        TableView<SymTableRowModel> symbolTable = factoryService.buildTableView(
            runService.getSymbolTable(),
            Map.of("variableName", "Variable", "value", "Value")
        );
        layout.setCenter(factoryService.buildLayout(
            VBox.class, null, Pos.CENTER,
            exeStackLabel, exeStack, symTableLabel, symbolTable)
        );

        Label heapTableLabel = new Label("Heap Table");
        TableView<HeapRowModel> heapTable = factoryService.buildTableView(
            runService.getHeap(),
            Map.of("address", "Address", "value", "Value")
        );
        Label fileTableLabel = new Label("File Table");
        ListView<String> fileTable = factoryService.buildListView(runService.getFileTable());
        layout.setRight(factoryService.buildLayout(
            VBox.class, null, Pos.CENTER,
            heapTableLabel, heapTable, fileTableLabel, fileTable)
        );

        Button oneStepButton = new Button("One Step All");
        oneStepButton.setOnAction(action -> {
            runService.oneStep();
            oneStepButton.setDisable(runService.executionIsOver());
            ((Label)labels.getChildren().get(2)).textProperty().setValue(
                String.valueOf(runService.getProgramIds().size())
            );
        });
        Button chooseStateIdButton = new Button("Inspect");
        chooseStateIdButton.setOnAction(
            action -> runService.setProgramId(programStateIds.getSelectionModel().getSelectedIndex())
        );
        Node spaceBelowStepButton = factoryService.buildSpacing(50.0, Priority.ALWAYS, null, null);
        Node spaceBetweenButtons = factoryService.buildSpacing(null, null, null, Priority.ALWAYS);
        layout.setBottom(factoryService.buildLayout(
                HBox.class, null, Pos.CENTER,
                chooseStateIdButton, spaceBetweenButtons, oneStepButton, spaceBelowStepButton)
        );

        Scene scene = new Scene(layout);
        stage.setScene(scene);

        stage.setTitle("Run Statement");
        stage.setMaximized(true);
        stage.show();
    }

    @Override
    public void start(Stage stage)
    {
        setUpStatementSelectionWindow();
    }

    public static void main(String[] args)
    {
        IStatement ex1 = new CompoundStatement(
                new CompoundStatement(
                        new VariableDeclarationStatement("a", new IntegerType()),
                        new VariableDeclarationStatement("b", new IntegerType())
                ),
                new PrintStatement(new VariableExpression("a"))
        );

        IStatement ex2 = new CompoundStatement(
                new VariableDeclarationStatement("a", new IntegerType()),
                new CompoundStatement(
                        new VariableDeclarationStatement("b", new IntegerType()),
                        new CompoundStatement(
                                new VariableAssignmentStatement(
                                        "a",
                                        new ArithmeticExpression(
                                                new ValueExpression(new IntegerValue(2)),
                                                new ArithmeticExpression(
                                                        new ValueExpression(new IntegerValue(3)),
                                                        new ValueExpression(new IntegerValue(5)),
                                                        ArithmeticOperator.STAR),
                                                ArithmeticOperator.PLUS)),
                                new CompoundStatement(
                                        new VariableAssignmentStatement(
                                                "b",
                                                new ArithmeticExpression(
                                                        new VariableExpression("a"),
                                                        new ValueExpression(new IntegerValue(1)),
                                                        ArithmeticOperator.PLUS)),
                                        new PrintStatement(new VariableExpression("b"))
                                ))
                )
        );

        IStatement ex3 = new CompoundStatement(
                new VariableDeclarationStatement("foo", new StringType()),
                new CompoundStatement(
                        new VariableAssignmentStatement("foo", new ValueExpression(new StringValue("test.txt"))),
                        new CompoundStatement(
                                new OpenRFileStatement(new VariableExpression("foo")),
                                new CompoundStatement(
                                        new VariableDeclarationStatement("a", new IntegerType()),
                                        new CompoundStatement(
                                                new ReadFileStatement(new VariableExpression("foo"), "a"),
                                                new CompoundStatement(
                                                        new PrintStatement(new VariableExpression("a")),
                                                        new CloseRFileStatement(new VariableExpression("foo"))))))));

        IStatement ex4 = new CompoundStatement(
                new VariableDeclarationStatement("v", new ReferenceValue(new IntegerType())),
                new CompoundStatement(
                        new HeapAllocationStatement("v", new ValueExpression(new IntegerValue(20))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new ReferenceValue(new ReferenceType(new IntegerType()))),
                                new CompoundStatement(
                                        new HeapAllocationStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(
                                                new HeapAllocationStatement("v", new ValueExpression(new IntegerValue(50))),
                                                new PrintStatement(new ReadHeapExpression(
                                                        new ReadHeapExpression(new VariableExpression("a"))))
                                        )
                                )
                        )
                )
        );

        IStatement ex5 = new CompoundStatement(
            new VariableDeclarationStatement("v", new IntegerType()),
            new CompoundStatement(
                new VariableDeclarationStatement("a", new ReferenceType(new IntegerType())),
                new CompoundStatement(
                    new VariableAssignmentStatement("v", new ValueExpression(new IntegerValue(10))),
                    new CompoundStatement(
                        new HeapAllocationStatement("a", new ValueExpression(new IntegerValue(22))),
                        new CompoundStatement (
                            new ForkStatement(
                                new CompoundStatement(
                                    new WriteHeapStatement("a", new ValueExpression(new IntegerValue(30))),
                                    new CompoundStatement(
                                        new VariableAssignmentStatement("v", new ValueExpression(new IntegerValue(32))),
                                        new CompoundStatement(
                                            new PrintStatement(new VariableExpression("v")),
                                            new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
                                        )
                                    )
                                )
                            ),
                            new CompoundStatement(
                                new PrintStatement(new VariableExpression("v")),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
                            )
                        )
                    )
                )
            )
        );

        statements = Arrays.asList(ex1, ex2, ex3, ex4, ex5);
        factoryService = UIFactoryService.buildObject();
        runService = UIRunService.buildObject();

        launch(args);
    }
}