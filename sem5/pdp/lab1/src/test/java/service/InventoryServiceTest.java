package service;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import repository.AtomicValueInventoryRepository;
import repository.InventoryRepository;
import service.inventory.InventoryService;
import domain.command.AddInventoryCommand;
import domain.command.BuildReportCommand;
import domain.command.ExecuteOrderCommand;
import domain.command.InventoryCommand;

import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;

public class InventoryServiceTest
{
    private AtomicValueInventoryRepository repository;

    @Before
    public void setUp()
    {
        repository = new AtomicValueInventoryRepository();
    }

    @Test
    public void assertScheduleStartsWithInventoryFill()
    {
        List<Function<InventoryRepository, InventoryCommand>> schedule = InventoryService.buildSchedule();
        Assert.assertTrue(schedule.get(0).apply(repository) instanceof AddInventoryCommand);
    }

    @Test
    public void assertAllOrdersNonZeroLength()
    {
        List<InventoryCommand> commands = InventoryService.buildSchedule().stream()
                .map(fnc -> fnc.apply(repository))
                .collect(Collectors.toList());
        commands.forEach(cmd -> {
            if (cmd instanceof ExecuteOrderCommand)
            {
                Assert.assertTrue(((ExecuteOrderCommand) cmd).getOrder().size() != 0);
            }
        });
    }

    @Test
    public void assertScheduleEndsReportCommand()
    {
        List<Function<InventoryRepository, InventoryCommand>> schedule = InventoryService.buildSchedule();
        Assert.assertTrue(schedule.get(schedule.size()-1).apply(repository) instanceof BuildReportCommand);
    }
}
