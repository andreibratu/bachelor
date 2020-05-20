package common.entities;

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
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode(callSuper = true)
public class Client extends BaseEntity<Long> implements Serializable
{
    private String name;

    private String address;

    @OneToMany(mappedBy = "client", cascade = CascadeType.ALL, fetch = FetchType.EAGER)
    private Set<Rental> rentals = new HashSet<>();

    public Set<Movie> getRentedMovies()
    {
        rentals = rentals == null ? new HashSet<>() : rentals;
        return rentals.stream()
                .map(Rental::getMovie)
                .collect(Collectors.toUnmodifiableSet());
    }

    public void rentMovie(Movie movie, LocalDate startDate)
    {
        Rental rental = new Rental();
        rental.setClient(this);
        rental.setMovie(movie);
        rental.setStartDate(startDate);
        rentals.add(rental);
    }
}
