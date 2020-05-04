package common.entities;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.*;

import javax.persistence.Entity;
import java.io.Serializable;
import java.time.LocalDate;

@Data
@Entity
@NoArgsConstructor
@AllArgsConstructor
@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public class Rental extends BaseEntity<Long> implements Serializable
{
    @JsonProperty("clientID")
    private Long clientID;

    @JsonProperty("movieID")
    private Long movieID;

    @JsonProperty("startDate")
    private LocalDate startDate;

    @JsonProperty("endDate")
    private LocalDate endDate;

    public Rental(Long clientID, Long movieID)
    {
        this.clientID = clientID;
        this.movieID = movieID;
        this.startDate = LocalDate.now();
        this.endDate = null;
    }

    public void returnMovie(LocalDate date)
    {
        this.endDate = date;
    }
}
