package common.entities;

import lombok.*;

import javax.persistence.*;
import java.io.Serializable;
import java.time.LocalDate;

@Entity
@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor
@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
public class Rental extends BaseEntity<Long> implements Serializable
{
    @Id
    @ManyToOne(optional = false, fetch = FetchType.EAGER)
    @JoinColumn(name = "client_id")
    private Client client;

    @Id
    @ManyToOne(optional = false, fetch = FetchType.EAGER)
    @JoinColumn(name = "movie_id")
    private Movie movie;

    private LocalDate startDate;

    private LocalDate endDate;

    public void returnMovie(LocalDate date)
    {
        this.endDate = date;
    }
}
