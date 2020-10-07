package domain.command;

import domain.Order;
import repository.InventoryRepository;

public class BuildReportCommand extends InventoryCommand
{
    public BuildReportCommand(InventoryRepository repository)
    {
        super(repository);
    }

    @Override
    public Order call()
    {
        return repository.buildReport();
    }
}
