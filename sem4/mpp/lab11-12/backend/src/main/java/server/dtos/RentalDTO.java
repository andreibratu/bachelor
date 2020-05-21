package server.dtos;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import server.entities.Rental;

import java.time.LocalDate;


@Data
@AllArgsConstructor
@NoArgsConstructor
public class RentalDTO implements DTO<Rental>
{
    @JsonProperty("id")
    private Long id;

    @JsonProperty("clientID")
    private Long clientId;

    @JsonProperty("movieID")
    private Long movieId;

    @JsonProperty("startDate")
    private LocalDate startDate;

    @JsonProperty("endDate")
    private LocalDate endDate;
}
