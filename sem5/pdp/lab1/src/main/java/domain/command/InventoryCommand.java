package domain.command;

import domain.Order;
import repository.InventoryRepository;

import java.util.concurrent.Callable;

public abstract class InventoryCommand implements Callable<Order>
{
    InventoryRepository repository;

    public InventoryCommand(InventoryRepository repository)
    {
        this.repository = repository;
    }

    public abstract Order call();
}