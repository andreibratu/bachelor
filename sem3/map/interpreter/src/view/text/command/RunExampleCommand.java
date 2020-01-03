package view.text.command;

import controller.IController;

public class RunExampleCommand extends Command
{
    private final IController controller;

    public RunExampleCommand(String key, String description, IController controller)
    {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute()
    {
        try
        {
            this.controller.allSteps();
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }
    }
}