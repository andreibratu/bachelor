package server.entities;

import lombok.*;
import server.dtos.RentalDTO;
import server.dtos.Transferable;

import javax.persistence.*;
import java.io.Serializable;
import java.time.LocalDate;

@SuppressWarnings({"JpaDataSourceORMInspection"})
@Data
@Entity
@Builder
@ToString
@NoArgsConstructor
@AllArgsConstructor
@Table(name = "rental")
@IdClass(RentalKey.class)
@EqualsAndHashCode(exclude = {"movie", "client"})
public class Rental implements Serializable, Transferable<Rental>
{
    @Id
    @ManyToOne(optional = false, fetch = FetchType.LAZY)
    @JoinColumn(name = "client_id")
    private Client client;

    @Id
    @ManyToOne(optional = false, fetch = FetchType.LAZY)
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
