package server.entities;

import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import server.dtos.RentalDTO;
import server.dtos.Transferable;

import javax.persistence.*;
import java.io.Serializable;
import java.time.LocalDate;

@Data
@Entity
@Builder
@NoArgsConstructor
@SuppressWarnings({"JpaDataSourceORMInspection"})
@NamedEntityGraph(
        name="rental-detailed-query",
        attributeNodes = {
                @NamedAttributeNode("id"),
                @NamedAttributeNode(value = "client", subgraph = "client-basic-query"),
                @NamedAttributeNode(value = "movie", subgraph = "movie-basic-query"),
                @NamedAttributeNode("startDate"),
                @NamedAttributeNode("endDate")
        },
        subgraphs = {
                @NamedSubgraph(
                    name = "client-basic",
                    attributeNodes = {
                        @NamedAttributeNode("id"),
                        @NamedAttributeNode("name")
                    }
                ),
                @NamedSubgraph(
                    name = "movie-basic",
                    attributeNodes = {
                        @NamedAttributeNode("id"),
                        @NamedAttributeNode("title")
                    }
                )
        }
)
@NamedEntityGraph(
        name="rental-basic-query",
        attributeNodes = {
                @NamedAttributeNode("id"),
                @NamedAttributeNode(value = "client", subgraph = "client-id-query"),
                @NamedAttributeNode(value = "movie", subgraph = "movie-id-query")
        },
        subgraphs = {
                @NamedSubgraph(
                        name = "client-id-query",
                        attributeNodes = {
                                @NamedAttributeNode("id"),
                        }
                ),
                @NamedSubgraph(
                        name = "movie-id-query",
                        attributeNodes = {
                                @NamedAttributeNode("id")
                        }
                )
        }
)
public class Rental implements Serializable, Transferable<Rental>
{
    @Id
    @GeneratedValue
    private Long id;

    @ManyToOne(optional = false, fetch = FetchType.LAZY)
    @JoinColumn(name = "client_id")
    private Client client;

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
