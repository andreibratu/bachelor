package view.ui;

import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.control.ListView;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.*;
import org.jetbrains.annotations.Nullable;

import java.util.Map;

public class UIFactoryService
{
    private static UIFactoryService singleton;

    private UIFactoryService() { }

    public static UIFactoryService buildObject()
    {
        if(singleton == null)
        {
            singleton = new UIFactoryService();
        }
        return singleton;
    }

    public Pane buildLayout(Class<?> layoutClass, Double padding, @Nullable Pos alignment, @Nullable Node ...nodes)
    {
        Pane layout = null;
        try
        {
            layout = (Pane) layoutClass.getDeclaredConstructor().newInstance();
            if(alignment != null)
            {
                if(layoutClass.toString().contains("VBox"))
                {
                    ((VBox) layout).setAlignment(alignment);
                }
                else if(layoutClass.toString().contains("HBox"))
                {
                    ((HBox) layout).setAlignment(alignment);
                }
                // Don't set property on Pane subclasses that don't have it
                else throw new RuntimeException();
            }
            if(nodes != null) layout.getChildren().setAll(nodes);
            if(padding != null) layout.setPadding(new Insets(padding, padding, padding, padding));
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        return layout;
    }

    public Node buildSpacing(@Nullable Double vSize, Priority vPriority, @Nullable Double hSize, Priority hPriority)
    {
        Region region = new Region();
        if(vSize != null) region.setPrefHeight(vSize);
        if(vPriority != null) VBox.setVgrow(region, vPriority);
        if(hSize != null) region.setPrefWidth(hSize);
        if(hPriority != null) HBox.setHgrow(region, hPriority);
        return region;
    }

    public <U> TableView<U> buildTableView(ObservableList<U> observable, Map<String, String> columnToProperty)
    {
        TableView<U> tableView = new TableView<>();
        columnToProperty.forEach((key, value) -> {
            TableColumn<U, String> column = new TableColumn<>(value);
            column.setCellValueFactory(new PropertyValueFactory<>(key));
            tableView.getColumns().add(column);
        });
        tableView.setItems(observable);
        return tableView;
    }

    public <U> ListView<U> buildListView(ObservableList<U> observable)
    {
        ListView<U> listView = new ListView<>();
        listView.setItems(observable);
        return listView;
    }
}
