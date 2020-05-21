package server.entities;

import lombok.*;
import server.dtos.RentalDTO;
import server.dtos.Transferable;

import javax.persistence.*;
import java.io.Serializable;
import java.time.LocalDate;

@SuppressWarnings({"JpaDataSourceORMInspection"})
@Entity
@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class Rental implements Serializable, Transferable<Rental>
{
    @Id
    @GeneratedValue
    private Long id;

    @ManyToOne(optional = false, fetch = FetchType.EAGER)
    @JoinColumn(name = "client_id")
    private Client client;

    @ManyToOne(optional = false, fetch = FetchType.EAGER)
    @JoinColumn(name = "movie_id")
    private Movie movie;

    private LocalDate startDate;

    private LocalDate endDate;

    public RentalDTO toDTO()
    {
        RentalDTO dto = new RentalDTO();
        dto.setClientId(client.getId());
        dto.setMovieId(movie.getId());
        dto.setStartDate(startDate);
        dto.setEndDate(endDate);
        return dto;
    }
}
