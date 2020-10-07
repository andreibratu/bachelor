package domain.command;

import domain.Order;
import domain.Pair;
import domain.Product;
import repository.InventoryRepository;

import java.util.List;

public class AddInventoryCommand extends InventoryCommand
{
    List<Pair<Product, Integer>> inventory;

    public AddInventoryCommand(
            InventoryRepository repository,
            List<Pair<Product, Integer>> inventory
    )
    {
        super(repository);
        this.inventory = inventory;
    }

    @Override
    public Order call()
    {
        inventory.forEach(pair -> {
            Product product = pair.getKey();
            Integer quantity = pair.getValue();
            repository.addProduct(product, quantity);
        });
        return null;
    }
}
