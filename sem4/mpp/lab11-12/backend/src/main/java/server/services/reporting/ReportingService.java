package server.services.reporting;

import server.entities.Client;
import server.entities.GenreEnum;
import javafx.util.Pair;

import java.util.List;

public interface ReportingService
{
    /**
     * Fetch top `limit` clients by number of rentals.
     * @return List of pairs containing client and number of rentals.
     */
    List<Pair<Client, Integer>> getTopClients(int limit);

    /**
     * Get clients who had at least one rental for more than 30 days.
     * @return List of bad renters.
     */
    List<Client> getBadRenters();

    /**
     * See how many rentals were made for each genre.
     * @return List of pairs consisting of genre and count.
     */
    List<Pair<GenreEnum, Integer>> getRentalsByGenre();
}
