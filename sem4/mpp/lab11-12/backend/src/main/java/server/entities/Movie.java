package common.entities;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.*;

import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.OneToMany;
import java.io.Serializable;
import java.time.LocalDate;
import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;

@Data
@Entity
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@EqualsAndHashCode(callSuper = true)
public class Movie extends BaseEntity<Long> implements Serializable
{
    @JsonProperty("title")
    private String title;

    @JsonProperty("genre")
    private GenreEnum genre;

    @JsonProperty("year")
    private Integer year;

    @OneToMany(mappedBy = "movie", cascade = CascadeType.ALL, fetch = FetchType.EAGER)
    private Set<Rental> rentals = new HashSet<>();

    public Set<Client> getRentingClients()
    {
        rentals = rentals == null ? new HashSet<>() : rentals;
        return rentals.stream()
                .map(Rental::getClient)
                .collect(Collectors.toUnmodifiableSet());
    }

    public void addRenter(Client client, LocalDate startDate)
    {
        Rental rental = new Rental();
        rental.setClient(client);
        rental.setMovie(this);
        rental.setStartDate(startDate);
        rentals.add(rental);
    }
}
