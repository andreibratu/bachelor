package view;

import controller.InvalidVegetableException;
import controller.VegetableController;
import model.Vegetable;
import repository.RepositoryFullException;

import java.util.Scanner;

public class ConsoleView
{
    private Scanner input;
    private VegetableController controller;

    public ConsoleView()
    {
        input = new Scanner(System.in);
        controller = new VegetableController();
    }

    private void printVegetables(Vegetable[] vegetables)
    {
        if(vegetables.length == 0)
        {
            System.out.println("No vegetables!");
            return;
        }
        int idx = 0;
        for(Vegetable v : vegetables)
        {
            System.out.println(Integer.toString(idx)+ ". " + v.toString());
            idx += 1;
        }
    }

    public void loop()
    {
        String menu = "=====Options:\n1. List all\n2. Add vegetable\n3. Remove vegetable\n4. Filter\n5. Exit\n=====\n";
        boolean ok = true;
        while(ok)
        {
            System.out.print(menu);
            System.out.print("Your option: ");
            int option = this.input.nextInt();
            float weight;
            switch(option)
            {
                case 1:
                    this.printVegetables(controller.getAllVegetables());
                    break;
                case 2:
                    System.out.print("Input vegetable type: ");
                    String type = this.input.next();
                    this.input.nextLine();
                    System.out.print("Input weight: ");
                    weight = Float.parseFloat(this.input.next());
                    this.input.nextLine();
                    try
                    {
                        this.controller.addVegetable(type, weight);
                    }
                    catch(InvalidVegetableException e)
                    {
                        System.out.println("Invalid vegetable type!\n");
                    }
                    catch(RepositoryFullException e)
                    {
                        System.out.println("How did we get here?\n");
                    }
                    break;
                case 3:
                    System.out.print("Please input index: ");
                    int idx = this.input.nextInt();
                    try
                    {
                        this.controller.removeVegetable(idx);
                        this.printVegetables(this.controller.getAllVegetables());
                    }
                    catch(IndexOutOfBoundsException e)
                    {
                        System.out.println("Invalid index!");
                    }
                    break;
                case 4:
                    System.out.print("Please input filter value: ");
                    weight = this.input.nextFloat();
                    this.printVegetables(this.controller.filterByWeight(weight));
                    break;
                case 5:
                    ok = false;
                    break;
                default:
            }
        }
    }
}
