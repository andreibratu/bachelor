package client.ui;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Field;
import java.time.LocalDate;
import java.util.*;
import java.util.concurrent.CompletableFuture;
import java.util.stream.Collectors;

import common.entities.GenreEnum;
import common.entities.Movie;
import common.entities.Client;
import common.entities.Rental;
import common.services.EntityService;
import common.services.ReportingService;
import common.services.behaviours.filter.FilterBehaviour;
import common.services.behaviours.filter.FilterStrategy;
import common.services.behaviours.sort.SortStrategy;
import client.ui.menu.Menu;

import static common.services.behaviours.GenericBehaviour.getEntityAttributes;

@SuppressWarnings("InfiniteLoopStatement")
@Component("console")
public class Console
{
    private final EntityService<Movie> movieService;
    private final EntityService<Client> clientService;
    private final EntityService<Rental> rentalService;
    private final ReportingService reportingService;
    private final BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private final Menu menu = new Menu();

    @Autowired
    public Console(
            @Qualifier("restMovieService") EntityService<Movie> movieService,
            @Qualifier("restClientService") EntityService<Client> clientService,
            @Qualifier("restRentalService") EntityService<Rental> rentalService,
            @Qualifier("restReportingService") ReportingService reportingService)
    {
        this.movieService = movieService;
        this.clientService = clientService;
        this.rentalService = rentalService;
        this.reportingService = reportingService;

        initialize_menu();
    }

    public void start()
    {
        while (true)
        {
            System.out.println(menu);
            System.out.println("command: ");
            int command;
            try
            {
                command = Integer.parseInt(reader.readLine());
                menu.getCommand(command).execute();
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }
        }
    }

    private void initialize_menu()
    {
        menu.addCommand("Exit", () -> System.exit(0));

        // Movie CRUD
        menu.addCommand("Add movie", () ->
        {
            Movie inputMovie = inputMovie();

            CompletableFuture.supplyAsync(
                ()-> this.movieService.addEntity(Objects.requireNonNull(inputMovie))
            ).thenAccept(movie -> System.out.println("Added movie: " + movie));
        });
        menu.addCommand("Show all movies", () -> CompletableFuture.supplyAsync(
            () -> this.movieService.getAllEntities(null)
        ).thenAccept(movies -> movies.forEach(System.out::println)));
        menu.addCommand("Update movie", () ->
        {
            Long updateMovieId = this.getID();
            Movie newMovie = this.inputMovie();
            Objects.requireNonNull(newMovie).setId(updateMovieId);

            CompletableFuture.supplyAsync(
                ()-> this.movieService.updateEntity(newMovie)
            ).thenAccept(movie -> System.out.println("Updated movie: " + movie));
        });
        menu.addCommand("Delete movie", () ->
        {
            Long deleteMovieId = this.getID();

            CompletableFuture.supplyAsync(
                () -> this.movieService.deleteEntity(deleteMovieId)
            ).thenAccept(movie -> System.out.println("Updated movie: " + movie));
        });
        menu.addCommand("Filter movies", () ->
            CompletableFuture.supplyAsync(
                ()-> this.movieService.filter(filterEntities(Movie.class))
        ).thenAccept(movies ->  movies.forEach(System.out::println)));
        menu.addCommand("Show clients sorted", () ->
        {
            List<Class<?>> allowedTypes = List.of(Integer.class, Double.class, String.class);
            List<String> clientFields = List.of(Client.class.getDeclaredFields()).stream()
                    .filter(field -> allowedTypes.contains(field.getType()))
                    .map(Field::getName)
                    .collect(Collectors.toList());
            SortStrategy sort = new SortStrategy();
            while (true)
            {
                System.out.println("Choose a field\n");
                clientFields.forEach(System.out::println);
                System.out.println("exit");
                String fieldName = null;
                try
                {
                    fieldName = reader.readLine();
                } catch (IOException e)
                {
                    e.printStackTrace();
                }
                if (Objects.equals(fieldName, "exit")) break;
                if (!clientFields.contains(fieldName)) continue;
                String order;
                do
                {
                    System.out.println("ASC\nDESC");
                    try
                    {
                        order = reader.readLine();
                    } catch (IOException e)
                    {
                        e.printStackTrace();
                        order = null;
                    }
                } while (!Objects.equals(order, "ASC") && !Objects.equals(order, "DESC"));
                sort.add(fieldName, SortStrategy.Direction.valueOf(order));
            }
            CompletableFuture.supplyAsync(
                ()-> this.clientService.getAllEntities(sort)
            ).thenAccept(
                clients -> clients.forEach(System.out::println)
            );
        });

        // Client CRUD
        menu.addCommand("Add client", () ->
        {
            Client inputClient = inputClient();

            CompletableFuture.supplyAsync(
                ()-> this.clientService.addEntity(inputClient)
            ).thenAccept(client -> System.out.println("Added client: " + client));
        });
        menu.addCommand("Show all clients", () ->
            CompletableFuture.supplyAsync(
                ()-> this.clientService.getAllEntities(null)
        ).thenAccept(clients -> clients.forEach(System.out::println)));
        menu.addCommand("Update client", () ->
        {
            Long updateClientId = this.getID();
            Client newClient = this.inputClient();
            Objects.requireNonNull(newClient).setId(updateClientId);

            CompletableFuture.supplyAsync(
                ()-> this.clientService.updateEntity(newClient)
            ).thenAccept(client -> System.out.println("Updated movie: " + client));
        });
        menu.addCommand("Delete Client", () ->
        {
            Long deleteClientId = this.getID();
            CompletableFuture.supplyAsync(
                ()-> this.clientService.deleteEntity(deleteClientId)
            ).thenAccept(client -> System.out.println("Deleted client: " + client));
        });
        menu.addCommand("Filter clients",
            () -> CompletableFuture.supplyAsync(()-> this.clientService.filter(filterEntities(Client.class))
        ).thenAccept(clients -> clients.forEach(System.out::println)));

        // Rental CRUD
        menu.addCommand("Rent movie", () ->
        {
            long clientId = 0;
            long movieId = 0;
            try
            {
                System.out.println("Client Id:");
                clientId = Long.parseLong(reader.readLine());
                System.out.println("Movie Id:");
                movieId = Long.parseLong(reader.readLine());
            } catch (IOException e)
            {
                e.printStackTrace();
            }
            Rental new_rental = new Rental(clientId, movieId);

            CompletableFuture.supplyAsync(
                ()-> this.rentalService.addEntity(new_rental)
            ).thenAccept(rental -> System.out.println("Added rental: " + rental));
        });
        menu.addCommand("Return movie", () ->
        {
            System.out.println("Rental Id:");
            long rentalId = 0;
            try
            {
                rentalId = Long.parseLong(reader.readLine());
            } catch (IOException e)
            {
                e.printStackTrace();
            }
            Rental rental = rentalService.getEntity(rentalId);
            rental.returnMovie(LocalDate.now());

            CompletableFuture.supplyAsync(
                ()-> this.rentalService.updateEntity(rental)
            ).thenAccept(rental_ret -> System.out.println("Updated rental: " + rental_ret));
        });
        menu.addCommand("Show all rentals", () ->
            CompletableFuture.supplyAsync(
                ()-> this.rentalService.getAllEntities(null)
            ).thenAccept(rentals -> rentals.forEach(System.out::println)));

        // Reporting
        menu.addCommand("Report top clients", () ->
        {
            System.out.println("How many?");
            int limit = 0;
            try
            {
                limit = Integer.parseInt(reader.readLine());
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }

            int finalLimit = limit;
            CompletableFuture.supplyAsync(
                ()-> this.reportingService.getTopClients(finalLimit)
            ).thenAccept(clients -> clients.forEach(System.out::println));
        });
        menu.addCommand("Report bad renters", () ->
            CompletableFuture.supplyAsync(this.reportingService::getBadRenters)
        .thenAccept(clients -> clients.forEach(System.out::println)));
        menu.addCommand("Report rentals by genre", () ->
            CompletableFuture.supplyAsync(this.reportingService::getRentalsByGenre)
        .thenAccept(genres -> genres.forEach(System.out::println)));
    }

    private Movie inputMovie()
    {
        try
        {
            System.out.println("Input title:");
            String title = reader.readLine();

            System.out.println("Genres:");
            Arrays.stream(GenreEnum.values()).forEach(System.out::println);
            System.out.println("Input genre:");
            String genre_input = reader.readLine();
            GenreEnum genre = GenreEnum.valueOf(genre_input.toUpperCase());

            System.out.println("Input year:");
            int year = Integer.parseInt(reader.readLine());

            return new Movie(title, genre, year);
        } catch (IOException | IllegalArgumentException ex)
        {
            ex.printStackTrace();
        }
        return null;
    }

    private Client inputClient()
    {
        try
        {
            System.out.println("Input name:");
            String name = reader.readLine();
            System.out.println("Input address:");
            String address = reader.readLine();
            return new Client(name, address);
        }
        catch (IOException ex)
        {
            ex.printStackTrace();
        }
        return null;
    }

    private Long getID()
    {
        try
        {
            System.out.println("Input ID: ");
            return Long.parseLong(reader.readLine());
        } catch (IOException ex)
        {
            ex.printStackTrace();
        }
        return null;
    }

    private FilterStrategy filterEntities(Class<?> cls)
    {
        FilterStrategy strategy = null;
        Map<String, Class<?>> attributes = getEntityAttributes(cls);
        try
        {
            System.out.println("Attributes available:");
            attributes.keySet().forEach(System.out::println);
            System.out.println("Choose attribute: ");
            String attribute = reader.readLine();

            Class<?> attrClass = attributes.get(attribute);
            if (attrClass == null) throw new IllegalArgumentException("Invalid attribute!");

            System.out.println("Available filters");
            FilterBehaviour.getFilters(attrClass).forEach(System.out::println);
            String filterInput = reader.readLine();

            System.out.println("Comparison value:");
            Object compValueInput = attrClass.cast(reader.readLine());

            strategy = new FilterStrategy(attribute, filterInput, compValueInput);
        } catch (IOException ex)
        {
            ex.printStackTrace();
        }
        return strategy;
    }
}
