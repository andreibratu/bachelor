package domain.command;

import domain.Order;
import domain.Pair;
import domain.Product;
import lombok.Getter;
import repository.InventoryRepository;

import java.util.List;

public class ExecuteOrderCommand extends InventoryCommand
{
    @Getter
    private final List<Pair<Product, Integer>> order;

    public ExecuteOrderCommand(
            InventoryRepository repository,
            List<Pair<Product, Integer>> order
    )
    {
        super(repository);
        this.order = order;
    }

    @Override
    public Order call()
    {
        repository.executeOrder(order);
        return null;
    }
}
